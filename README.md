# Especificação de Projeto: Simulador de Sistemas Operacionais

## Gerenciamento de Processos e Memória

**Coordenação de Engenharia de Computação**
**Semestre Letivo - 2026**

---

# 1. Introdução

Este projeto consiste no desenvolvimento de um simulador de Sistemas Operacionais integrado, focado em dois pilares fundamentais:

* Escalonamento de processos;
* Gerência de memória virtual.

O objetivo é consolidar os conceitos teóricos através da implementação prática em linguagem de baixo/médio nível (C/C++).

---

# 2. Requisitos do Sistema

## 2.1 Entrada de Dados

O simulador deverá processar um arquivo de entrada no formato CSV contendo a lista de processos com os seguintes campos:

* Tempo de Chegada;
* Tempo de Execução (CPU Burst);
* Prioridade;
* Memória Necessária (em MB).

---

## 2.2 Interface Gráfica (GUI)

Diferente de simuladores via terminal, este projeto exige uma interface gráfica funcional que permita:

* Seleção do arquivo CSV de entrada;
* Definição do tamanho da Memória Física e Memória Virtual;
* Seleção da política de escalonamento e de substituição de páginas.

---

# 3. Núcleo de Simulação

## 3.1 Escalonamento de Processos

O simulador deve implementar obrigatoriamente os seguintes algoritmos:

1. **Round-Robin (RR)**

   * Com definição de quantum via interface.

2. **SJF Preemptivo (Shortest Job First)**

3. **Prioridade Preemptiva**

---

## 3.2 Gerenciamento de Memória

O sistema deve simular:

* Paginação;
* Memória virtual.

Ao carregar um processo, o simulador deve:

* Verificar a disponibilidade de frames;
* Gerenciar a Tabela de Páginas.

Deverão ser implementadas políticas de substituição de páginas, por exemplo:

* FIFO;
* LRU.

---

# 4. Saídas Esperadas (Relatórios)

Ao final da execução, o software deve gerar um relatório detalhado contendo:

## Linha do Tempo

* Visualização da execução dos processos.

## Métricas de Performance

* Tempo Médio de Resposta (*Average Response Time*);
* Tempo Médio de Espera (*Average Wait Time*);
* Total de *Page Faults* ocorridos.

---

# 5. Gerenciamento de Memória

O simulador implementa memória virtual com paginação.

## 5.1 Configurações

* Memória física;
* Memória virtual;
* Política de substituição.

---

## 5.2 Políticas

* FIFO;
* LRU;
* Ótimo.

---

# 6. Critérios de Avaliação

| Item                                                   | Pontuação |
| ------------------------------------------------------ | --------- |
| Interface Gráfica                                      | 2.0       |
| Algoritmos de Escalonamento (RR, SJF-P, Prioridade-P)  | 4.0       |
| Simulação de Memória Virtual e Substituição de Páginas | 4.0       |
| **Total**                                              | **10.0**  |

---

# 7. Instruções Técnicas

* Linguagem: **C ou C++**;
* Bibliotecas sugeridas para GUI:

  * Qt;
  * GTK;
  * SFML;
* Entrega:

  * Código-fonte;
  * Makefile;
* Apresentação do trabalho para o professor;
* O trabalho poderá ser feito em grupos de até 3 pessoas;
* Data de entrega: **21/06**;
* Datas de apresentação: **22/06 e 24/06**.
