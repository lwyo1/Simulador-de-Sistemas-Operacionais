#include "report.h"
#include <sstream>

using namespace std;

Report::Report(vector<Processo>& procs, vector<Intervalo>& ldt, float tmEspera, float tmResposta, int pf, int pnv, int memVirtualUsada, int memVirtualTotal) {
    finalizados = procs;
    linhaDoTempo = ldt;
    tempoMedioEspera = tmEspera;
    tempoMedioResposta = tmResposta;
    pageFaults = pf;
    paginasNaVirtual = pnv;
    memoriaVirtualUsada = memVirtualUsada;
    tamanhoMemoriaVirtual = memVirtualTotal;
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
    ss << "Total de Page Faults:     " << pageFaults << "\n";
    ss << "Páginas expulsas para Virtual: " << paginasNaVirtual << "\n";
    ss << "Memória Virtual utilizada: " << memoriaVirtualUsada << " KB\n";
    ss << "Memória Virtual total:     " << tamanhoMemoriaVirtual * 1024 << " KB\n";
    ss << "Uso da Memória Virtual:    "
       << (tamanhoMemoriaVirtual > 0 ? (float)memoriaVirtualUsada / (tamanhoMemoriaVirtual * 1024) * 100 : 0)
       << "%\n";

    ss << "\nLINHA DO TEMPO:\n";
    for (auto& i : linhaDoTempo) {
        ss << "P" << i.idProcesso << "[" << i.inicio << "-" << i.fim << "] ";
    }
    ss << "\n";

    return ss.str();
}