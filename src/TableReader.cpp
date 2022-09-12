//
// Created by gsc2001 on 9/11/22.
//

#include "TableReader.h"

TableReader::TableReader(const string &tableName, uint maxRows) {
    this->tableName = tableName;
    this->pageCounter = 0;
    this->counter = 0;
    this->maxRows = maxRows;
    auto fileName = this->tableName + "_" + to_string(this->pageCounter);
    this->page = make_unique<Page>(fileName);
    this->page->load();
}

vector<string> TableReader::readRow() {
    assert(this->counter + PAGE_ROW_COUNT * this->pageCounter < this->maxRows);
    if (this->counter == this->page->data.size()) {
        this->counter = 0;
        this->pageCounter++;
        auto fileName = this->tableName + "_" + to_string(this->pageCounter);
        this->page = make_unique<Page>(fileName);
        this->page->load();
    }

    auto &row = this->page->data[this->counter];
    this->counter++;

    return row;
}