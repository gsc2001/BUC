//
// Created by gsc2001 on 9/11/22.
//

#include "Table.h"

Table::Table(const string &tableName, const string &cuboidName, const int rootDim) {
    this->tableName = tableName;
    this->rowCount = 0;
    this->columns.clear();
    this->cuboidName = cuboidName;
    this->rootDim = rootDim;
    this->writer = make_unique<TableWriter>(this->tableName);
}

Table::Table(const string &tableName, const string &cuboidName, const vector<string> &cols, const int rootDim) {
    this->tableName = tableName;
    this->rowCount = 0;
    this->columns = cols;
    this->cuboidName = cuboidName;
    this->rootDim = rootDim;
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
    this->writer->dumpBuffer();

    fin.close();
    logger.log("Loaded table rows: " + to_string(this->rowCount));
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
    logger.log("Writing row: " + to_string(this->rowCount + 1) + " TableName: " + this->tableName);
    assert(row.size() == this->dim());
    this->rowCount++;
    this->writer->writeRow(row);
}

void Table::deletePages() const {
    logger.log("Deleting Pages of Table: " + this->tableName);
    for (auto page_idx = 0; page_idx < this->writer->pageCounter; page_idx++) {
        auto fileName = PAGE_TEMP_DIR + this->tableName + "_" + to_string(page_idx);
        if (remove(fileName.c_str()))
            logger.log("DeletePage: Error");
    }
}




