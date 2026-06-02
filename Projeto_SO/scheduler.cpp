#include "scheduler.h"
#include <queue>
#include <algorithm>



Scheduler::Scheduler(vector<Processo>& procs, GerenciadorMemoria* mem, int q, int pol) {
    processos = procs;
    memoria = mem;
    quantum = q;
    politica = pol;
    tempoAtual = 0;

    // inicializa campos de controle de cada processo
    for (auto& p : processos) {
        p.tempoRestante = p.tempoExecucao;
        p.tempoInicio = -1;
        p.tempoFim = -1;
        p.tempoEspera = 0;
        p.tempoResposta = -1;
        p.iniciou = false;
    }
}

void Scheduler::executarRoundRobin() {
    queue<Processo*> fila;
    int concluidos = 0;

    //enquanto ainda tiverem processos sendo executados
    while (concluidos < (int)processos.size()) {

        // adiciona processos que chegaram até o tempoAtual
        for (auto& p : processos) {
            if (p.tempoChegada == tempoAtual && !p.iniciou) {
                vector<int> acessosFuturos;
                memoria->carregarProcesso(p, politica, tempoAtual, acessosFuturos);
                p.iniciou = true; // marca aqui para não readicionar na fila
                fila.push(&p);
            }
        }

        if (fila.empty()) {
            tempoAtual++;
            continue;
        }

        // pega o próximo processo da fila
        Processo* p = fila.front();
        fila.pop();

        // registra tempo de resposta na primeira execução real
        if (p->tempoInicio == -1) {
            p->tempoInicio = tempoAtual;
            p->tempoResposta = tempoAtual - p->tempoChegada;
        }

        // executa por quantum ou pelo tempo restante
        int executar = min(quantum, p->tempoRestante);

        // avança tempo unidade por unidade para detectar chegadas durante execução
        for (int i = 0; i < executar; i++) {
            tempoAtual++;
            p->tempoRestante--;

            // verifica novos processos que chegaram durante a execução
            for (auto& proc : processos) {
                if (proc.tempoChegada == tempoAtual && !proc.iniciou) {
                    vector<int> acessosFuturos;
                    memoria->carregarProcesso(proc, politica, tempoAtual, acessosFuturos);
                    proc.iniciou = true;
                    fila.push(&proc);
                }
            }
        }

        // verifica se terminou
        if (p->tempoRestante == 0) {
            p->tempoFim = tempoAtual;
            p->tempoEspera = p->tempoFim - p->tempoChegada - p->tempoExecucao;
            memoria->liberarProcesso(p->id);
            finalizados.push_back(*p);
            concluidos++;
        } else {
            // não terminou, volta para o fim da fila
            fila.push(p);
        }
    }
}


void Scheduler::executarSJF() {
    vector<Processo*> prontos; //Vetor de ponteiros para processos que já chegaram e estão prontos para executar.
    int concluidos = 0;

    //Continua simulando enquanto ainda tiver processo para terminar.
    while (concluidos < processos.size()) {

        // adiciona processos que chegaram até o tempoAtual
        for (auto& p : processos) {
            if (p.tempoChegada == tempoAtual && !p.iniciou && find(prontos.begin(), prontos.end(), &p) == prontos.end()) {//Percorre todos os processos e adiciona na fila de prontos os que chegaram agora.
                                                                                                                          //O !p.iniciou evita readicionar processos que já estão rodando. O find evita duplicatas no vetor.
                //Carrega o processo na memória e adiciona no vetor de prontos.
                vector<int> acessosFuturos;
                memoria->carregarProcesso(p, politica, tempoAtual, acessosFuturos);
                prontos.push_back(&p);
            }
        }

        //Se nenhum processo chegou ainda, avança o tempo e volta para o início do while.
        if (prontos.empty()) {
            tempoAtual++;
            continue;
        }

        // ordena pelo menor tempo restante
        sort(prontos.begin(), prontos.end(), [](Processo* a, Processo* b) {
            return a->tempoRestante < b->tempoRestante;
        });

        // pega o processo com menor tempo restante
        Processo* p = prontos.front();

        // Se é a primeira vez que esse processo executa, registra quando começou e calcula o tempo de resposta.
        if (!p->iniciou) {
            p->tempoInicio = tempoAtual;
            p->tempoResposta = tempoAtual - p->tempoChegada;
            p->iniciou = true;
        }

        // executa 1 unidade de tempo (preemptivo)
        p->tempoRestante--;
        tempoAtual++;

        // verifica se terminou
        //Se o processo terminou, registra o tempo final, calcula quanto ficou esperando, libera a memória, move para finalizados e remove da fila de prontos.
        if (p->tempoRestante == 0) {
            p->tempoFim = tempoAtual;
            p->tempoEspera = p->tempoFim - p->tempoChegada - p->tempoExecucao;
            memoria->liberarProcesso(p->id);
            finalizados.push_back(*p);
            prontos.erase(prontos.begin());
            concluidos++;
        }
    }
}


//Praticamente igual ao SJF, só muda o sort
void Scheduler::executarPrioridade() {
    vector<Processo*> prontos;
    int concluidos = 0;

    while (concluidos < processos.size()) {

        // adiciona processos que chegaram até o tempoAtual
        for (auto& p : processos) {
            if (p.tempoChegada == tempoAtual && !p.iniciou &&
                find(prontos.begin(), prontos.end(), &p) == prontos.end()) {
                vector<int> acessosFuturos;
                memoria->carregarProcesso(p, politica, tempoAtual, acessosFuturos);
                prontos.push_back(&p);
            }
        }

        if (prontos.empty()) {
            tempoAtual++;
            continue;
        }

        // ordena pela maior prioridade (menor número = maior prioridade)
        sort(prontos.begin(), prontos.end(), [](Processo* a, Processo* b) {
            return a->prioridade < b->prioridade;
        });

        Processo* p = prontos.front();

        if (!p->iniciou) {
            p->tempoInicio = tempoAtual;
            p->tempoResposta = tempoAtual - p->tempoChegada;
            p->iniciou = true;
        }

        // executa 1 unidade de tempo (preemptivo)
        p->tempoRestante--;
        tempoAtual++;

        if (p->tempoRestante == 0) {
            p->tempoFim = tempoAtual;
            p->tempoEspera = p->tempoFim - p->tempoChegada - p->tempoExecucao;
            memoria->liberarProcesso(p->id);
            finalizados.push_back(*p);
            prontos.erase(prontos.begin());
            concluidos++;
        }
    }
}

float Scheduler::calcularTempoMedioEspera() {
    float total = 0;
    for (auto& p : finalizados) {
        total += p.tempoEspera;
    }
    return total / finalizados.size();
}

float Scheduler::calcularTempoMedioResposta() {
    float total = 0;
    for (auto& p : finalizados) {
        total += p.tempoResposta;
    }
    return total / finalizados.size();
}