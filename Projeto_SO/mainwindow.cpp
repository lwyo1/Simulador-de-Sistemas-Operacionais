#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvreader.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinMemFisica_valueChanged(int arg1)
{
    // arredonda para o múltiplo de 128 mais próximo
    int arredondado = (arg1 / 128) * 128;
    
    if (arredondado != arg1) {
        ui->spinMemFisica->setValue(arredondado); // corrige o valor
        return;
    }

    ui->spinMemVirtual->setMinimum(arredondado + 128);

}

void MainWindow::on_spinMemVirtual_valueChanged(int arg1)
{
    int arredondado = (arg1 / 256) * 256;
    
    if (arredondado != arg1) {
        ui->spinMemVirtual->setValue(arredondado);
        return;
    }
}

void MainWindow::on_buttonSelecionaCSV_clicked()
{
    QString caminho = QFileDialog::getOpenFileName(
        this,
        "Selecione o CSV de processos",   // título
        "",                          // diretório inicial
        "CSV Files (*.csv)"          // filtro
        );

    if (!caminho.isEmpty()) {
        ui->labelArquivo->setText(caminho); // mostra o caminho na tela
        ui->buttonIniciar->setEnabled(1);
    }
}


void MainWindow::on_comboAlgoritmo_currentIndexChanged(int index)
{
    ui->spinQuantum->setVisible(index == 0);
    ui->labelQuantum->setVisible(index == 0);
}

