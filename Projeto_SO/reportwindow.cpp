#include "reportwindow.h"

ReportWindow::ReportWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ReportWindow)
{
    ui->setupUi(this);
}

ReportWindow::~ReportWindow() {
    delete ui;
}

void ReportWindow::exibirRelatorio(Report& report) {
    QString texto = QString::fromStdString(report.gerarRelatorio());
    ui->textRelatorio->setText(texto);
}

void ReportWindow::on_btnFechar_clicked() {
    this->close();
}