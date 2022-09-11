//
// Created by gsc2001 on 9/11/22.
//

#include "Logger.h"

Logger::Logger(string logFileName) {
    this->logFileName = logFileName;
    this->fout.open(this->logFileName);
}

void Logger::log(string toLog) {
    fout << toLog << endl;
}