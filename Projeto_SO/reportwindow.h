#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include <QMainWindow>
#include "ui_reportwindow.h"
#include "report.h"


class ReportWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit ReportWindow(QWidget *parent = nullptr);
    ~ReportWindow();
    void exibirRelatorio(Report& report);

private slots:
    void on_btnFechar_clicked();

private:
    Ui::ReportWindow *ui;
};

#endif