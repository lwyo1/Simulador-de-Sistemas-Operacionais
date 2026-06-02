#include "report.h"
#include <sstream>

Report::Report(std::vector<Processo>& procs, float tmEspera, float tmResposta, int pf) {
    finalizados = procs;
    tempoMedioEspera = tmEspera;
    tempoMedioResposta = tmResposta;
    pageFaults = pf;
}

std::string Report::gerarRelatorio() {
    std::ostringstream ss;

    ss << "=== RELATÓRIO FINAL ===\n\n";

    ss << "PROCESSOS:\n";
    ss << "ID | Chegada | Execução | Prioridade | Início | Fim | Espera | Resposta\n";
    ss << "-----------------------------------------------------------------------\n";

    for (auto& p : finalizados) {
        ss << p.id          << " | "
           << p.tempoChegada  << " | "
           << p.tempoExecucao << " | "
           << p.prioridade    << " | "
           << p.tempoInicio   << " | "
           << p.tempoFim      << " | "
           << p.tempoEspera   << " | "
           << p.tempoResposta << "\n";
    }

    ss << "\nMÉTRICAS:\n";
    ss << "Tempo Médio de Espera:    " << tempoMedioEspera   << "\n";
    ss << "Tempo Médio de Resposta:  " << tempoMedioResposta << "\n";
    ss << "Total de Page Faults:     " << pageFaults         << "\n";

    return ss.str();
}