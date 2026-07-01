#include "report.h"
#include <sstream>

using namespace std;

Report::Report(vector<Processo>& procs, vector<Intervalo>& ldt,float tmEspera, float tmResposta, int pf, int paginasNaVirtual) {
    finalizados = procs;
    linhaDoTempo = ldt;
    tempoMedioEspera = tmEspera;
    tempoMedioResposta = tmResposta;
    pageFaults = pf;
    paginasNaVirtual = paginasNaVirtual;
}

string Report::gerarRelatorio() {
    ostringstream ss;

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
    ss << "Páginas expulsas para Virtual: " << paginasNaVirtual << "\n";

    ss << "\nLINHA DO TEMPO:\n";
    for (auto& i : linhaDoTempo) {
        ss << "P" << i.idProcesso << "[" << i.inicio << "-" << i.fim << "] ";
    }
    ss << "\n";

    return ss.str();
}