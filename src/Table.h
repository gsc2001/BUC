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
    uint rowCount;
    vector<string> columns;

    Table() = default;


    explicit Table(const string &tableName);

    Table(const string &tableName, const vector<string> &cols);

    void load(const string &fileName);

    [[nodiscard]] shared_ptr<TableReader> getReader() const {
        return make_shared<TableReader>(this->tableName, this->rowCount);
    }

    [[nodiscard]] size_t dim() const { return this->columns.size(); }

    [[nodiscard]] unordered_map<string, int> getElems(int dim) const;

    void addRow(const vector<string> &row);

};


#endif //BUC_TABLE_H
