#include "buc.h"


unordered_map<string, Table>
partition(const Table &table, int dim, const string &path, const unordered_map<string, int> &elems) {
    unordered_map<string, Table> tables;
    string newPath = path;
    if (path != "") newPath += ".";
    int cnt = 0;

    vector<string> cols(table.columns.begin() + dim, table.columns.end());

    for (auto &elem: elems) {
        cnt++;
    }
    auto reader = table.getReader();
    for (int i = 0; i < table.rowCount; i++) {
        auto row = reader->readRow();
        vector<string> usefulRow(row.begin() + dim, row.end());
        tables[row[dim]].addRow(usefulRow);
    }
    return tables;
}


void buc(const Table &table, const string &path) {
    logger.log("BUC on path: " + path);
    if (table.rowCount == 1) {
        // TODO: write ancestors

        return;
    }

    vector<vector<int>> freq(table.dim());

    // TODO: output anything here ?

    for (int d = 0; d < table.dim(); d++) {
        unordered_map<string, int> elems = table.getElems(d);
        auto partitionedTables = partition(table, d, path, elems);

        // go over cardinality
        for (auto &elem: elems) {
            // check min support
            if (elem.second >= MIN_SUP) {
                buc(partitionedTables[elem.first], path);
            }
        }
    }

    // TODO: cleanup (by deleting all pages created by partitioned tables

}