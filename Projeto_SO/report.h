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

    Report(vector<Processo>& procs, vector<Intervalo>& ldt,float tmEspera, float tmResposta, int pf, int paginasNaVirtual);

    string gerarRelatorio();
};

#endif // REPORT_H
