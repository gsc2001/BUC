//
// Created by gsc2001 on 9/11/22.
//

#ifndef BUC_PAGE_H
#define BUC_PAGE_H

#include "global.h"

using namespace std;


class Page {
public:
    vector<vector<string>> data;
    string pageName;

    explicit Page(const string &pageName);

    void dump();

    void load();
};


#endif //BUC_PAGE_H
