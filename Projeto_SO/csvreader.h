#ifndef CSVREADER_H
#define CSVREADER_H

#include "process.h"
#include <vector>
#include <string>

using namespace std;

vector<Processo> lerCSV(const string& caminho);

#endif // CSVREADER_H
