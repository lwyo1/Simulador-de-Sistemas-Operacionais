# Simulador de Sistemas Operacionais
**Coordenação de Engenharia de Computação — Semestre Letivo 2026**

## Participantes

| Nome | RA |
|------|----|
| Luiz Bonfá dos Santos | a2669609 |
| Lorenzo Brugnolo Rosa | a2669587 |
| João Francisco Barcala Paulo | a2669544 |

---

## Descrição

Simulador de Sistemas Operacionais desenvolvido em C++ com interface gráfica Qt, focado em escalonamento de processos e gerenciamento de memória virtual com paginação.

---

## Objetivo

Desenvolver um simulador didático de Sistemas Operacionais capaz de demonstrar o funcionamento de algoritmos de escalonamento de processos e gerenciamento de memória virtual por paginação, permitindo visualizar o comportamento do sistema por meio de uma interface gráfica.

## Funcionalidades Implementadas

### Interface Gráfica
- Seleção de arquivo CSV de entrada
- Definição de memória física e virtual (em MB)
- Seleção do tamanho de página (4, 8, 16, 32 KB)
- Seleção do algoritmo de escalonamento
- Seleção da política de substituição de páginas
- Diagrama de Gantt interativo com legenda e tooltip
- Barras de progresso de uso de memória física e virtual
- Exportação do relatório em .txt

### Algoritmos de Escalonamento
- **Round-Robin (RR)** — com quantum configurável via interface
- **SJF Preemptivo** — Shortest Job First com preempção
- **Prioridade Preemptiva** — menor número = maior prioridade

### Gerenciamento de Memória
- Paginação com tamanho de página configurável
- Tabela de páginas por processo
- Detecção e contagem de page faults
- Memória virtual com registro de páginas expulsas
- Políticas de substituição:
  - **FIFO** — substitui a página mais antiga
  - **LRU** — substitui a página menos recentemente usada
  - **Ótimo** — substitui a página usada mais longe no futuro

### Relatório Final
- Tabela de processos com tempos de chegada, execução, início, fim, espera e resposta
- Tempo Médio de Espera
- Tempo Médio de Resposta
- Total de Page Faults
- Páginas expulsas para memória virtual
- Uso percentual da memória física e virtual
- Linha do tempo textual
- Diagrama de Gantt visual com cores por processo

---

## Estrutura do Projeto
```text
.
├── main.cpp              # Inicialização da aplicação Qt
├── mainwindow.h
├── mainwindow.cpp        # Interface principal e controle da simulação
├── mainwindow.ui         # Layout da interface
├── process.h             # Struct Processo e Intervalo
├── csvreader.h
├── csvreader.cpp         # Leitura e validação do arquivo CSV
├── memory.h
├── memory.cpp            # Gerenciamento de memória e paginação
├── scheduler.h
├── scheduler.cpp         # Algoritmos de escalonamento
├── report.h
├── report.cpp            # Geração do relatório final
├── ganttwidget.h
├── ganttwidget.cpp       # Diagrama de Gantt
└── CMakeLists.txt        # Configuração do projeto
```

---

## Formato do CSV de Entrada

```csv
tempoChegada,tempoExecucao,prioridade,memoriaNecessaria
0,5,2,50
1,3,1,30
2,4,3,40
```

| Campo | Descrição |
|-------|-----------|
| tempoChegada | Instante em que o processo chega |
| tempoExecucao | Tempo total de CPU necessário |
| prioridade | Prioridade (menor número = maior prioridade) |
| memoriaNecessaria | Memória necessária em MB |

---

## Como Compilar e Executar

### Requisitos
- Qt 6.x
- MinGW ou compilador C++ compatível
- CMake 3.16+

### Compilar
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Executar
```bash
./appProjeto_SO
```

---

## Dependências

- Qt 6.x
- CMake 3.16+
- Compilador compatível com C++17
  - MinGW
  - MSVC
  - GCC