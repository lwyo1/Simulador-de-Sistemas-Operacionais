#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvreader.h"
#include "scheduler.h"
#include "memory.h"
#include "report.h"
#include "reportwindow.h"
#include <QFileDialog>
#include <QFileInfo>

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
        caminhoCSV = caminho;
        processos = lerCSV(caminho.toStdString());
        ui->labelArquivo->setText(QFileInfo(caminho).fileName());
        ui->buttonIniciar->setEnabled(true);
    }
}


void MainWindow::on_comboAlgoritmo_currentIndexChanged(int index)
{
    ui->spinQuantum->setVisible(index == 0);
    ui->labelQuantum->setVisible(index == 0);
}


void MainWindow::on_buttonIniciar_clicked()
{
    // 1. lê configurações da interface
    int memFisica  = ui->spinMemFisica->value();
    int memVirtual = ui->spinMemVirtual->value();
    int tamPagina  = ui->comboTamanhoPaginacao->currentText().toInt();
    int algoritmo  = ui->comboAlgoritmo->currentIndex();
    int politica   = ui->comboPoliticaPaginacao->currentIndex();
    int quantum    = ui->spinQuantum->value();

    // 2. cria o gerenciador de memória
    GerenciadorMemoria memoria(memFisica, tamPagina);

    // 3. cria o scheduler
    Scheduler scheduler(processos, &memoria, quantum, politica);

    // 4. executa o algoritmo selecionado
    if (algoritmo == 0){
        scheduler.executarRoundRobin();
    } else if (algoritmo == 1) {
        scheduler.executarSJF();
    } else{
        scheduler.executarPrioridade();
    }

    // 5. gera o relatório
    Report report(
        scheduler.finalizados,
        scheduler.linhaDoTempo,
        scheduler.calcularTempoMedioEspera(),
        scheduler.calcularTempoMedioResposta(),
        memoria.pageFaults
        );

    // 6. abre a janela de relatório
    ReportWindow* rw = new ReportWindow(this);
    rw->exibirRelatorio(report);
    rw->show();
}

