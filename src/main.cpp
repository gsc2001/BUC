#include <iostream>

#include "global.h"
#include "Table.h"
#include "buc.h"

int PAGE_ROW_COUNT = 1000;
string PAGE_TEMP_DIR = "../data/temp/";

// TODO: finalize on this
uint MIN_SUP = 2;
Logger logger("BUC.log");

int main() {
    string fileName;
    cout << "Enter file name: \n";
    cin >> fileName;
    auto masterTable = Table("ALL", "ALL", 0);
    masterTable.load(fileName);
    vector<string> cols{"Cuboid Name", "Count"};
    auto outputTable = Table("Output", "NA", cols, 0);
    buc(masterTable, outputTable);
    outputTable.dumpEverything();


    return 0;
}
