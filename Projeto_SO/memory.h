#ifndef MEMORY_H
#define MEMORY_H

#include "process.h"
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct Frame {
    int paginaCarregada; // -1 = livre
    int idProcesso;      // qual processo está usando
    int ultimoAcesso;
    bool livre;
};

struct TabelaPaginas {
    int idProcesso;
    vector<int> frames; // índice = página, valor = frame alocado
};

struct PaginaVirtual {
    int idProcesso;
    int indicePagina;
};

class GerenciadorMemoria {
public:
    int framesTotal;
    int framesLivres;
    int framesMaxUsados;
    int pageFaults;
    int tamanhoPagina; // em KB
    int totalPaginasExpulsas; // conta todas as expulsões, não só as atuais


    vector<Frame> frames;
    vector<TabelaPaginas> tabelaPaginas;

    //construtor
    GerenciadorMemoria(int memoriaFisicaMB, int tamanhoPaginaKB, int memoriaVirtualMB);

    //Frames
    int contarFramesLivres();

    //tabela paginas
    void criarTabelaPaginas(Processo& p);
    TabelaPaginas* buscarTabela(int idProcesso);


    //carregar / liberar
    bool carregarProcesso(Processo& p, int politica, int tempoAtual, vector<int>& acessosFuturos);
    void liberarProcesso(int idProcesso);

    // políticas de substituição
    int substituirFIFO();
    int substituirLRU(int tempoAtual);
    int substituirOtimo(int paginaAtual, vector<int>& acessosFuturos);

    //armazena os processos na fila
    queue<int> filaFIFO;

    //memoria virtual
    vector<PaginaVirtual> memoriaVirtual; // páginas expulsas da física
    int tamanhoMemoriaVirtual; // em MB
    int memoriaVirtualUsada;   // em KB
};


#endif // MEMORY_H
