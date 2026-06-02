#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <vector>      // armazenar lista de processos
#include <queue>       // fila para Round-Robin e FIFO
#include <algorithm>   // sort para SJF
#include <fstream>     // leitura do CSV
#include <sstream>     // parsing do CSV
#include <string>      // manipulação de strings
#include <climits>     // INT_MAX (útil no SJF/LRU)
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinMemVirtual_valueChanged(int arg1);

    void on_spinMemFisica_valueChanged(int arg1);

    void on_buttonSelecionaCSV_clicked();

    void on_comboAlgoritmo_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
