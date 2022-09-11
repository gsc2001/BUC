#pragma once

#include <functional>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

template<typename T>
vector<T> splitString(string s, char delim, function<T(string)> apply) {
//    logger.log("splitString");
    stringstream ss(s);
    string word;
    vector<T> split;

    while (!ss.eof()) {
        getline(ss, word, delim);
        split.push_back(apply(word));
    }
    return split;
}


string cleanStr(string str);