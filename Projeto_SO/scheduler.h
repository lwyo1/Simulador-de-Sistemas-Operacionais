#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include "memory.h"
#include <vector>
#include <queue>

using namespace std;

class Scheduler {
public:
    vector<Processo> processos;
    vector<Processo> finalizados;
    GerenciadorMemoria* memoria;

    int tempoAtual;
    int quantum;
    int politica; // 0 = FIFO, 1 = LRU, 2 = Ótimo

    // construtor
    Scheduler(vector<Processo>& processos, GerenciadorMemoria* memoria, int quantum, int politica);

    // algoritmos
    void executarRoundRobin();
    void executarSJF();
    void executarPrioridade();

    // métricas
    float calcularTempoMedioEspera();
    float calcularTempoMedioResposta();
};


#endif // SCHEDULER_H
