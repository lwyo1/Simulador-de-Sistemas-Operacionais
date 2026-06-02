#ifndef CSVREADER_H
#define CSVREADER_H

#include <vector>
#include <string>

struct Processo {
    int id;
    int tempoChegada;
    int tempoExecucao;
    int prioridade;
    int memoriaNeccessaria;
};

std::vector<Processo> lerCSV(const std::string& caminho);

#endif // CSVREADER_H
