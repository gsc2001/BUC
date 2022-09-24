//
// Created by gsc2001 on 9/11/22.
//

#ifndef BUC_TABLE_H
#define BUC_TABLE_H

#include <unordered_map>
#include <memory>

#include "global.h"
#include "TableWriter.h"
#include "TableReader.h"


using namespace std;


class Table {
private:


    unique_ptr<TableWriter> writer;
public:
    string tableName;
    string cuboidName;
    uint rowCount;
    int rootDim;
    vector<string> columns;

    Table() = default;

    Table(const string &tableName, const string &cuboidName, const int rootDim);

    Table(const string &tableName, const string &cuboidName, const vector<string> &cols, const int rootDim);

    void load(const string &fileName);

    [[nodiscard]] shared_ptr<TableReader> getReader() const {
        return make_shared<TableReader>(this->tableName, this->rowCount);
    }

    [[nodiscard]] size_t dim() const { return this->columns.size(); }

    [[nodiscard]] unordered_map<string, int> getElems(int dim) const;

    void addRow(const vector<string> &row);

    void dumpEverything() {
        this->writer->dumpBuffer();
    }

    void deletePages() const;

};


#endif //BUC_TABLE_H
