//
// Created by gsc2001 on 9/11/22.
//

#include "Page.h"

Page::Page(const string &pageName) {
    this->pageName = pageName;
    this->data.clear();
}

void Page::dump() {
    ofstream fout(PAGE_TEMP_DIR + this->pageName, ios::out);

    for (auto &row: data) {
        for (auto &data_point: row) {
            fout << data_point << ",";
        }
        fout << "\n";
    }
    fout.close();
    logger.log("Dumped page: " + this->pageName);
}

void Page::load() {
    ifstream fin(PAGE_TEMP_DIR + this->pageName, ios::in);
    string line;
    vector<string> row;
    while (getline(fin, line)) {
        row = splitString<string>(line, ',', &cleanStr);
        this->data.emplace_back(row);
    }
    fin.close();
    logger.log("Loaded page: " + this->pageName);
}
