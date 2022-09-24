#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "Logger.h"
#include "utils.h"

using namespace std;

// block size in KB
extern int PAGE_ROW_COUNT;
extern string PAGE_TEMP_DIR;
extern string OUTPUT_DIR;
extern Logger logger;
extern uint MIN_SUP;