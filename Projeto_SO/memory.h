#ifndef MEMORY_H
#define MEMORY_H

#include "process.h"
#include <vector>

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

class GerenciadorMemoria {
public:
    int framesTotal;
    int framesLivres;
    int pageFaults;
    int tamanhoPagina; // em KB

    vector<Frame> frames;
    vector<TabelaPaginas> tabelaPaginas;

    //construtor
    GerenciadorMemoria(int memoriaFisicaMB, int tamanhoPaginaKB);

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
};


#endif // MEMORY_H
