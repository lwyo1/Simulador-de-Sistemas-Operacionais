#include "memory.h"
#include <cmath>

using namespace std;

GerenciadorMemoria::GerenciadorMemoria(int memoriaFisicaMB, int tamanhoPaginaKB, int memoriaVirtualMB) {
    tamanhoPagina = tamanhoPaginaKB;
    pageFaults = 0;
    totalPaginasExpulsas = 0;
    framesMaxUsados = 0;

    // calcula total de frames
    int memoriaFisicaKB = memoriaFisicaMB * 1024;
    framesTotal = memoriaFisicaKB / tamanhoPaginaKB;
    framesLivres = framesTotal;

    // inicializa todos os frames como livres
    frames.resize(framesTotal);
    /*
    auto — o compilador descobre o tipo sozinho, no caso como o vetor é vector<Frame>, ele entende que f é um Frame.
    & — acessa o frame original do vetor, não uma cópia. Se não tivesse o &:

    Equivalente a
    for (int i = 0; i < frames.size(); i++) {
        Frame& f = frames[i];
        ...
    }
    */
    for (auto& f : frames) {
        f.livre = true;
        f.paginaCarregada = -1;
        f.idProcesso = -1;
    }

    tamanhoMemoriaVirtual = memoriaVirtualMB;
    memoriaVirtualUsada = 0;
}

int GerenciadorMemoria::contarFramesLivres() {
    int count = 0;
    for (auto& f : frames) {
        if (f.livre) count++;
    }
    return count;
}

void GerenciadorMemoria::criarTabelaPaginas(Processo& p){
    // quantas páginas o processo precisa
    int memoriaProcessoKB = p.memoriaNecessaria * 1024;
    int paginasNecessarias = ceil((float)memoriaProcessoKB / tamanhoPagina); //Arredonda para cima

    TabelaPaginas tabela; //Struct de tabela
    tabela.idProcesso = p.id;
    tabela.frames.resize(paginasNecessarias, -1); // -1 = página não carregada

    tabelaPaginas.push_back(tabela); //adiciona a tabela criada no vetor de tabelas.
}

TabelaPaginas* GerenciadorMemoria::buscarTabela(int idProcesso) {
    for (auto& t : tabelaPaginas) {
        if (t.idProcesso == idProcesso) return &t;
    }
    return nullptr; // não encontrou
}

//FIFO — remove o frame mais antigo
int GerenciadorMemoria::substituirFIFO() {
    // pega o frame mais antigo (primeiro que entrou) e remove da fila
    int frame = filaFIFO.front();
    filaFIFO.pop();
    return frame;
}

//LRU — remove o frame usado há mais tempo
int GerenciadorMemoria::substituirLRU(int tempoAtual) {
    int frameMaisAntigo = -1;
    int menorTempo = INT_MAX;

    for (int i = 0; i < framesTotal; i++) {
        if (!frames[i].livre) {
            if (frames[i].ultimoAcesso < menorTempo) {
                menorTempo = frames[i].ultimoAcesso;
                frameMaisAntigo = i;
            }
        }
    }
    return frameMaisAntigo;
}

//Ótimo — remove o frame cuja página será usada mais longe no futuro
int GerenciadorMemoria::substituirOtimo(int tempoAtual, vector<int>& acessosFuturos) {
    int frameEscolhido = -1; //Vai guardar o índice do frame que será substituído. Começa em -1 pois ainda não escolheu nenhum.
    int maiorDistancia = -1; //Vai guardar a maior distância encontrada até agora. Começa em -1 pois ainda não comparou nada.

    for (int i = 0; i < framesTotal; i++) {
        if (!frames[i].livre) { //Só analisa frames ocupados — frame livre não precisa ser substituído.
            int pagina = frames[i].paginaCarregada; //Pega qual página está nesse frame no momento.

            // procura próximo acesso dessa página no futuro
            int distancia = INT_MAX;
            for (int j = tempoAtual; j < acessosFuturos.size(); j++) { //Percorre a sequência futura de acessos a partir do tempo atual.
                if (acessosFuturos[j] == pagina) {//Achou a próxima vez que essa página será usada. Salva a posição e para de procurar.
                    distancia = j;
                    break;
                }
            }

            // escolhe o frame com maior distância de uso futuro
            if (distancia > maiorDistancia) {
                maiorDistancia = distancia;
                frameEscolhido = i;
            }//Se essa página for usada mais longe no futuro que todas as anteriores, ela é a melhor candidata para substituição.
        }
    }
    return frameEscolhido; //Retorna o índice do frame cuja página será usada mais longe no futuro — ou nunca mais (INT_MAX).
}

bool GerenciadorMemoria::carregarProcesso(Processo& p, int politica, int tempoAtual, vector<int>& acessosFuturos){

    // evita carregar o mesmo processo duas vezes
    if (buscarTabela(p.id) != nullptr) return true;

    //Cria a tabela de páginas do processo
    criarTabelaPaginas(p);

    //busca a tabela criada
    TabelaPaginas* tabela = buscarTabela(p.id);

    //para cada pagina tenta alocar um frame livre
    for(int i= 0; i < tabela->frames.size(); i++){

        //procura um frame livre
        bool alocou = false;
        for(int j = 0; j < framesTotal; j++){
            if(frames[j].livre){
                //aloca o frame
                frames[j].livre = false;
                frames[j].idProcesso = p.id;
                frames[j].paginaCarregada = i;
                frames[j].ultimoAcesso = tempoAtual;
                //atualiza a tabela de paginas
                tabela->frames[i] = j;

                framesLivres--;
                alocou = true;
                filaFIFO.push(j); // ← registra a ordem de entrada

                int framesUsados = framesTotal - framesLivres;
                if(framesUsados > framesMaxUsados) {
                    framesMaxUsados = framesUsados;
                }

                break;
            }
        }

        //nao alocou frame livre = page fault
        if(!alocou){
            pageFaults++;
            //Vamos utilizar as tecnicas de liberaçao de frames
            int frameLiberar;
            if(politica == 0){
                frameLiberar = substituirFIFO();
            }else if(politica == 1){
                frameLiberar = substituirLRU(tempoAtual);

            } else {
                frameLiberar = substituirOtimo(tempoAtual, acessosFuturos);
            }


            // página expulsa vai para memória virtual
            PaginaVirtual pv;
            pv.idProcesso = frames[frameLiberar].idProcesso;
            pv.indicePagina = frames[frameLiberar].paginaCarregada;
            memoriaVirtual.push_back(pv);
            memoriaVirtualUsada += tamanhoPagina;

            totalPaginasExpulsas++;

            // remove a página antiga da tabela do processo que estava usando esse frame
            for(auto& t : tabelaPaginas){
                for(auto& f : t.frames){
                    if(f == frameLiberar){
                        f = -1; // marca como não carregada
                        break;
                    }
                }
            }

            // aloca o frame para o novo processo
            frames[frameLiberar].livre = false;
            frames[frameLiberar].idProcesso = p.id;
            frames[frameLiberar].paginaCarregada = i;
            frames[frameLiberar].ultimoAcesso = tempoAtual;

            // atualiza a tabela do processo atual
            tabela->frames[i] = frameLiberar;

            filaFIFO.push(frameLiberar); // ← novo frame entra no fim da fila
        }


    }

    return true;

}

void GerenciadorMemoria::liberarProcesso(int idProcesso) {
    // libera todos os frames do processo
    for (auto& f : frames) {
        if (f.idProcesso == idProcesso) {
            f.livre = true;
            f.idProcesso = -1;
            f.paginaCarregada = -1;
            framesLivres++;
        }
    }

    // remove a tabela de páginas do processo
    for (int i = 0; i < tabelaPaginas.size(); i++) {
        if (tabelaPaginas[i].idProcesso == idProcesso) {
            tabelaPaginas.erase(tabelaPaginas.begin() + i);
            break;
        }
    }
}

