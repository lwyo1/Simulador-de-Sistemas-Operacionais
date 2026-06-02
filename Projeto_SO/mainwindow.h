#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "process.h"

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

    void on_buttonIniciar_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Processo> processos;
    QString caminhoCSV;
};

#endif