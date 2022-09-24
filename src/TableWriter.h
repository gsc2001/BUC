//
// Created by gsc2001 on 9/11/22.
//

#ifndef BUC_TABLEWRITER_H
#define BUC_TABLEWRITER_H

#include<memory>

#include "global.h"
#include "Page.h"

using namespace std;

class TableWriter {
public:
    string tableName;
    uint counter, pageCounter;
    unique_ptr<Page> page;

    explicit TableWriter(const string &tableName);

    void writeRow(const vector<string> &row);

    void dumpBuffer() {
        this->page->dump();
        this->pageCounter++;
        this->counter = 0;
    }
};


#endif //BUC_TABLEWRITER_H
