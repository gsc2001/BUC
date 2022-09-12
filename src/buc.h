#pragma once

#include <string>

#include "global.h"
#include "Table.h"

using namespace std;

void buc(const Table &table, Table &outputTable);

unordered_map<string, Table>
partition(const Table &table, int dim, const unordered_map<string, int> &elems);
