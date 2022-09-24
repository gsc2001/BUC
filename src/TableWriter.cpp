//
// Created by gsc2001 on 9/11/22.
//

#include "TableWriter.h"

TableWriter::TableWriter(const string &tableName) {
    this->tableName = tableName;
    this->counter = 0;
    auto fileName = this->tableName + "_0";
    this->pageCounter = 1;
    this->page = make_unique<Page>(fileName);
}

void TableWriter::writeRow(const vector<string> &row) {
    this->page->data.emplace_back(row);
    this->counter++;
    if (this->counter == PAGE_ROW_COUNT) {
        this->page->dump();
        auto fileName = this->tableName + "_" + to_string(this->pageCounter);
        this->page = make_unique<Page>(fileName);
        this->pageCounter++;
        this->counter = 0;
    }
}