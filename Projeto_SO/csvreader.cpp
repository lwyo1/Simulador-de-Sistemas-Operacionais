#include "csvreader.h"
#include <fstream>
#include <sstream>

using namespace std;

vector<Processo> lerCSV(const string& caminho){

    vector<Processo> processos; //Vetor que armazena os processos
    ifstream arquivo(caminho); //Abre o arquivo para leitura

    if(!arquivo.is_open()){
        throw runtime_error("Não foi possível abrir o arquivo.");
    }

    string linha; //Armazena cada linha do csv
    getline(arquivo, linha); // pula o cabeçalho

    int id = 1;
    while (getline(arquivo, linha)) {
        if (linha.empty()) continue; // ignora linhas vazias

        stringstream ss(linha); //Coloca a linha dentro de um stringstream para poder quebrar pelas vírgulas.
        string campo; //Variável temporária que guarda cada campo extraído da linha.
        Processo p; //Cria um processo vazio que vai ser preenchido com os dados da linha atual.

        try{
            p.id = id++;
            getline(ss, campo, ','); p.tempoChegada     = stoi(campo);
            getline(ss, campo, ','); p.tempoExecucao    = stoi(campo);
            getline(ss, campo, ','); p.prioridade       = stoi(campo);
            getline(ss, campo, ','); p.memoriaNecessaria = stoi(campo);
            //Lê até a próxima vírgula, guarda em campo como string, e stoi converte para inteiro.
        }catch(...){
            throw runtime_error("Formato do CSV inválido na linha " + to_string(id - 1));
        }


        processos.push_back(p);
    }

    if (processos.empty()) {
        throw runtime_error("Nenhum processo encontrado no CSV.");
    }

    return processos;

}//Função que le o CSV