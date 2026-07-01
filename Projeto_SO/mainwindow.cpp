#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvreader.h"
#include "scheduler.h"
#include "memory.h"
#include "report.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <fstream>

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
        this, "Selecione o CSV de processos", "", "CSV Files (*.csv)"
        );

    if (!caminho.isEmpty()) {
        try{
            caminhoCSV = caminho;
            processos = lerCSV(caminho.toStdString());
            ui->labelArquivo->setText(QFileInfo(caminho).fileName());
            ui->buttonIniciar->setEnabled(true);
        }catch(const exception& e) {
            QMessageBox::critical(this, "Erro ao carregar CSV", QString::fromStdString(e.what()));
            ui->buttonIniciar->setEnabled(false);
        }

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
    GerenciadorMemoria memoria(memFisica, tamPagina, memVirtual);

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

    atualizarProgressoMemoria(memoria.framesMaxUsados, memoria.framesTotal);

    // 5. gera o relatório
    Report report(
        scheduler.finalizados,
        scheduler.linhaDoTempo,
        scheduler.calcularTempoMedioEspera(),
        scheduler.calcularTempoMedioResposta(),
        memoria.pageFaults,
        memoria.totalPaginasExpulsas
        );

    // 6. exibe relatório
    exibirRelatorio(report);
}


void MainWindow::on_buttonNovaSim_clicked()
{
    // limpa os dados
    processos.clear();
    caminhoCSV = "";

    vector<Intervalo> vazio;

    // reseta a interface
    ui->labelArquivo->setText("Nenhum arquivo selecionado");
    ui->buttonIniciar->setEnabled(false);
    ui->btnExportar->setEnabled(false);
    ui->textRelatorio->clear();
    ui->widgetGantt->setDados(vazio, 0);
    ui->widgetGantt->setVisible(false);
    ui->spinMemFisica->setValue(512);
    ui->spinMemVirtual->setValue(1024);
    ui->comboAlgoritmo->setCurrentIndex(0);
    ui->comboPoliticaPaginacao->setCurrentIndex(0);
    ui->comboTamanhoPaginacao->setCurrentIndex(0);
    ui->spinQuantum->setValue(2);
}

void MainWindow::atualizarProgressoMemoria(int framesUsados, int framesTotal) {
    int percentual = (int)((float)framesUsados / framesTotal * 100);
    ui->progressMemoria->setValue(percentual);
    ui->progressMemoria->setFormat(QString("%1%").arg(percentual));
}


void MainWindow::exibirRelatorio(Report& report) {
    QString texto = QString::fromStdString(report.gerarRelatorio());
    ui->textRelatorio->setText(texto);
    ui->textRelatorio->setVisible(true);
    ui->btnExportar->setEnabled(true);
    ui->widgetGantt->setVisible(true);
    ui->widgetGantt->setDados(report.linhaDoTempo, report.finalizados.size());
}
void MainWindow::on_btnExportar_clicked()
{
    QString caminho = QFileDialog::getSaveFileName(
        this,
        "Salvar Relatório",
        "relatorio.txt",
        "Text Files (*.txt)"
        );

    if (!caminho.isEmpty()) {
        ofstream arquivo(caminho.toStdString());

        if (arquivo.is_open()) {
            arquivo << ui->textRelatorio->toPlainText().toStdString();
            arquivo.close();
            QMessageBox::information(this, "Sucesso", "Relatório exportado com sucesso!");
        } else {
            QMessageBox::critical(this, "Erro", "Não foi possível salvar o arquivo.");
        }
    }
}

