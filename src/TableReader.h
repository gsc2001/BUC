//
// Created by gsc2001 on 9/11/22.
//

#ifndef BUC_TABLEREADER_H
#define BUC_TABLEREADER_H

#include<memory>
#include "global.h"
#include "Page.h"
#include <cassert>

class TableReader {
public:
    string tableName;
    uint pageCounter, counter, maxRows;
    unique_ptr<Page> page;

    explicit TableReader(const string &tableName, uint maxRows);

    vector<string> readRow();
};


#endif //BUC_TABLEREADER_H
