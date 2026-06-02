#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <iostream>
#include <vector>      // armazenar lista de processos
#include <queue>       // fila para Round-Robin e FIFO
#include <algorithm>   // sort para SJF
#include <fstream>     // leitura do CSV
#include <sstream>     // parsing do CSV
#include <string>      // manipulação de strings
#include <climits>     // INT_MAX (útil no SJF/LRU)
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
