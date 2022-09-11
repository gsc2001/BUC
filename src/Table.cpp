//
// Created by gsc2001 on 9/11/22.
//

#include "Table.h"

Table::Table(const string &tableName) {
    this->tableName = tableName;
    this->rowCount = 0;
    this->columns.clear();
    this->writer = make_unique<TableWriter>(this->tableName);
}

Table::Table(const string &tableName, const vector<string> &cols) {
    this->tableName = tableName;
    this->rowCount = 0;
    this->columns = cols;
    this->writer = make_unique<TableWriter>(this->tableName);
}


void Table::load(const string &fileName) {
    ifstream fin(fileName, ios::in);
    string line;
    getline(fin, line);
    this->columns = splitString<string>(line, ',', &cleanStr);
    vector<string> row;

    while (getline(fin, line)) {
        row = splitString<string>(line, ',', &cleanStr);
        this->writer->writeRow(row);
        this->rowCount++;
    }

    fin.close();
}

unordered_map<string, int> Table::getElems(int dim) const {
    auto reader = this->getReader();
    unordered_map<string, int> elemSet;

    for (int rowIdx = 0; rowIdx < this->rowCount; rowIdx++) {
        elemSet[reader->readRow()[dim]]++;
    }

    return elemSet;
}

void Table::addRow(const vector<string> &row) {
    assert(row.size() == this->dim());
    this->rowCount++;
    this->writer->writeRow(row);
    logger.log("Writing row: " + to_string(this->rowCount));
}



