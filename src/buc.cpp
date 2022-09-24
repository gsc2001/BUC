#include "buc.h"


pair<string, string> getNamesPrefix(const Table &table, int dim) {
    string newTableName = table.tableName, newCuboidName = table.cuboidName;
    auto dimCoveredTillNow = 0;
    if (table.cuboidName == "ALL") {
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

    auto[newTableName, newCuboidName] = getNamesPrefix(table, dim);

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
//    if (table.rowCount == 1) {
//        // TODO: write ancestors. Won't call this here, would shift to bucInMemory
//        writeAncestors(table, outputTable);
//        return;
//    }

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
                    auto[_, cuboidNamePrefix] = getNamesPrefix(table, d);
                    row = vector<string>{cuboidNamePrefix + elem.first, to_string(elem.second)};
                    outputTable.addRow(row);
                }
            }
        }
    }
    // TODO: cleanup (by deleting all pages created by partitioned tables
    table.deletePages();
}

unordered_map<string, int> getElems(const vector<vector<string>> &data, int dim) {
    unordered_map<string, int> elems;
    for (const auto &i: data) {
        elems[i[dim]]++;
    }
    return elems;
}

vector<vector<string>> partition(vector<vector<string>> &data, int dim, const unordered_map<string, int> &elems) {

    // this will be copied
    unordered_map<string, int> countingDataMap(elems);

    int prev = 0, temp;
    for (auto &elem: countingDataMap) {
        temp = elem.second;
        elem.second += prev;
        prev = temp;
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

void bucInMemory(vector<vector<string>> &&data, int dim) {
    if (data.size() == 1) {
        // TODO: writeAncestors
    }


    for (int d = 0; d < data[0].size(); d++) {
        auto elems = getElems(data, d);
        auto partitionedData = partition(data, d, elems);
        for (auto& attribute: elems) {
            if (attribute.second > MIN_SUP) {
                if
            }
        }
    }

}


void writeAncestors() {
    // TODO: Implement writeAncestors
}
