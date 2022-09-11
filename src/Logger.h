//
// Created by gsc2001 on 9/11/22.
//

#ifndef BUC_LOGGER_H
#define BUC_LOGGER_H

#include <fstream>
#include <string>

using namespace std;


class Logger {
private:
    ofstream fout;
    string logFileName;
public:
    explicit Logger(string logFileName);

    void log(string toLog);

};


#endif //BUC_LOGGER_H
