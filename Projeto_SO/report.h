#ifndef REPORT_H
#define REPORT_H

#include "process.h"
#include "scheduler.h"
#include <vector>
#include <string>

using namespace std;

class Report {
public:
    vector<Processo> finalizados;
    vector<Intervalo> linhaDoTempo;
    float tempoMedioEspera;
    float tempoMedioResposta;
    int pageFaults;
    int paginasNaVirtual;
    int memoriaVirtualUsada;
    int tamanhoMemoriaVirtual;

    Report(vector<Processo>& finalizados, vector<Intervalo>& linhaDoTempo,
           float tmEspera, float tmResposta, int pageFaults,
           int paginasNaVirtual, int memoriaVirtualUsada, int tamanhoMemoriaVirtual);

    string gerarRelatorio();
};

#endif // REPORT_H
