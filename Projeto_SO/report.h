#ifndef REPORT_H
#define REPORT_H

#include "process.h"
#include <vector>
#include <string>

class Report {
public:
    std::vector<Processo> finalizados;
    float tempoMedioEspera;
    float tempoMedioResposta;
    int pageFaults;

    Report(std::vector<Processo>& finalizados, float tmEspera, float tmResposta, int pageFaults);

    std::string gerarRelatorio();
};

#endif // REPORT_H
