#include "buc.h"


pair<string, string> getNamesPrefix(const string &tableName, const string &cuboidName, int dim) {
    string newTableName = tableName, newCuboidName = cuboidName;
    auto dimCoveredTillNow = 0;
    if (cuboidName == "ALL") {
        newTableName = "", newCuboidName = "";
    } else {
        newTableName += ".", newCuboidName += ";";
    }

    while (dimCoveredTillNow < dim) {
        newTableName += "*.";
        newCuboidName += "*;";
        dimCoveredTillNow++;
    }

    return {newTableName, newCuboidName};

}


unordered_map<string, Table>
partition(const Table &table, int dim, const unordered_map<string, int> &elems) {
    unordered_map<string, Table> tables;
    int cnt = 0;

    vector<string> cols(table.columns.begin() + dim + 1, table.columns.end());

    auto [newTableName, newCuboidName] = getNamesPrefix(table.tableName, table.cuboidName, dim);

    for (auto &elem: elems) {
        tables[elem.first] = Table(newTableName + to_string(cnt), newCuboidName + elem.first, cols, dim + 1);
        cnt++;
    }
    auto reader = table.getReader();
    for (int i = 0; i < table.rowCount; i++) {
        auto row = reader->readRow();
        vector<string> usefulRow(row.begin() + dim + 1, row.end());
        tables[row[dim]].addRow(usefulRow);
    }

    for (auto &elem: tables) elem.second.dumpEverything();
    return tables;
}


void buc(const Table &table, Table &outputTable) {
    logger.log("BUC on path: " + table.tableName);

    // can fit in memory in now :)
    if (table.rowCount <= PAGE_ROW_COUNT) {
        vector<vector<string>> data(table.rowCount);
        auto reader = table.getReader();
        for (int i = 0; i < table.rowCount; i++) {
            data[i] = reader->readRow();
        }
        bucInMemory(std::move(data), 0, table.cuboidName, outputTable);
        return;
    }

    vector<string> row{table.cuboidName, to_string(table.rowCount)};
    outputTable.addRow(row);


    for (int d = 0; d < table.dim(); d++) {
        unordered_map<string, int> elems = table.getElems(d);
        unordered_map<string, Table> partitionedTables;
        if (d < table.dim() - 1) {
            partitionedTables = partition(table, d, elems);
        }


        // go over cardinality
        for (auto &elem: elems) {

            // check min support
            if (elem.second >= MIN_SUP) {
                if (d < table.dim() - 1) {
                    buc(partitionedTables[elem.first], outputTable);
                } else {
                    auto [_, cuboidNamePrefix] = getNamesPrefix(table.tableName, table.cuboidName, d);
                    row = vector<string>{cuboidNamePrefix + elem.first, to_string(elem.second)};
                    outputTable.addRow(row);
                }
            }
        }
    }
    table.deletePages();
}

unordered_map<string, int> getElems(const vector<vector<string>> &data, int dim) {
    unordered_map<string, int> elems;
    for (const auto &i: data) {
        elems[i[dim]]++;
    }
    return elems;
}

vector<vector<string>> partition(vector<vector<string>> &&data, int dim, const unordered_map<string, int> &elems) {

    // this will be copied
    unordered_map<string, int> countingDataMap(elems);

    int prev = 0;
    for (auto &elem: countingDataMap) {
        elem.second += prev;
        prev = elem.second;
    }

    vector<vector<string>> partitionedData(data.size());
    string tempStr;

    for (auto &i: data) {
        tempStr = i[dim];
        partitionedData[countingDataMap[tempStr] - 1] = i;
        countingDataMap[tempStr]--;
    }
    return partitionedData;
}

void bucInMemory(vector<vector<string>> &&data, int dim, const string &cuboidName, Table &outputTable) {
    logger.log("BUC in Memory on path: " + cuboidName);

    //sanity check
    assert(data.size() <= PAGE_ROW_COUNT);

    if (data.size() == 1) {
        writeAncestors(data, dim, cuboidName, outputTable);
        return;
    }

    vector<string> row{cuboidName, to_string(data.size())};
    outputTable.addRow(row);

    uint nDims = data[0].size();
    for (int d = dim; d < nDims; d++) {
        auto elems = getElems(data, d);
        data = partition(std::move(data), d, elems);
        uint count_till_now = 0;
        for (auto &attribute: elems) {
            if (attribute.second >= MIN_SUP) {
                vector<vector<string>> sub_data(data.begin() + count_till_now,
                                                data.begin() + count_till_now + attribute.second);

                count_till_now += attribute.second;
                auto [_, newCuboidName] = getNamesPrefix("", cuboidName, d - dim);
                bucInMemory(std::move(sub_data), d + 1, newCuboidName + attribute.first, outputTable);
            }
        }
    }
}


void writeAncestors(const vector<vector<string>> &data, int dim, const string &cuboidName, Table &outputTable) {
    logger.log("BUC Write Ancestors on path: " + cuboidName);

    // sanity check
    assert(data.size() == 1);

    vector<string> row{cuboidName, to_string(data.size())};
    outputTable.addRow(row);
    uint nDims = data[0].size();
    for (int d = dim + 1; d < nDims; d++) {
        auto [_, newCuboidName] = getNamesPrefix("", cuboidName, d - dim);
        writeAncestors(data, d, newCuboidName + data[0][d], outputTable);
    }
}
