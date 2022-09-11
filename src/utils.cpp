#include "utils.h"

string cleanStr(string word) {
    word.erase(std::remove_if(word.begin(), word.end(), ::isspace), word.end());
    return word;
}
