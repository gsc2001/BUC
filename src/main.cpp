#include <iostream>
#include <chrono>

using namespace std::chrono;

#include "global.h"
#include "Table.h"
#include "buc.h"

uint PAGE_ROW_COUNT;
uint BLOCK_SIZE;
string PAGE_TEMP_DIR = "../data/temp/";
string OUTPUT_DIR = "../data/results/";

uint MIN_SUP;
Logger logger("BUC.log");

int main() {
    initialize();
    string fileName;
    cin >> fileName;
    cin >> BLOCK_SIZE;
    cin >> MIN_SUP;
    auto masterTable = Table("ALL", "ALL", 0);
    Table::calculatePageSize(fileName);
    masterTable.load(fileName);
    vector<string> cols{"Cuboid Name", "Count"};
    auto outputTable = Table("Output", "NA", cols, 0);
    auto start = high_resolution_clock::now();
    buc(masterTable, outputTable);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    outputTable.dumpEverything();
    outputTable.exportTable();
    clear_folder(PAGE_TEMP_DIR);

    cout << duration.count() << endl;

    return 0;
}
