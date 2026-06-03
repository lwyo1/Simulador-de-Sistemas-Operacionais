#ifndef PROCESS_H
#define PROCESS_H

struct Processo {
    int id;
    int tempoChegada;
    int tempoExecucao;
    int prioridade;
    int memoriaNecessaria;

    // campos de controle do scheduler
    int tempoRestante;    // quanto ainda falta executar
    int tempoInicio;      // quando começou a executar
    int tempoFim;         // quando terminou
    int tempoEspera;      // quanto ficou esperando
    int tempoResposta;    // tempo até primeira execução
    bool iniciou;         // já executou pelo menos uma vez?
};

struct Intervalo {
    int inicio;
    int fim;
    int idProcesso;
};

#endif // PROCESS_H
