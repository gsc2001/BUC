#include "utils.h"
#include "global.h"

string cleanStr(string word) {
    word.erase(std::remove_if(word.begin(), word.end(), ::isspace), word.end());
    return word;
}

void initialize() {
    clear_folder(PAGE_TEMP_DIR);
    clear_folder(OUTPUT_DIR);
}

void clear_folder(string folder_name) {
    string cmd = "rm -r " + folder_name;
    system(cmd.c_str());
    cmd = "mkdir -p " + folder_name;
    system(cmd.c_str());
}