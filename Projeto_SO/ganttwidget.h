#ifndef GANTTWIDGET_H
#define GANTTWIDGET_H

#include <QWidget>
#include <QPainter>
#include "process.h"
#include <vector>

using namespace std;

class GanttWidget : public QWidget {
    Q_OBJECT
public:
    explicit GanttWidget(QWidget *parent = nullptr);

    void setDados(vector<Intervalo>& intervalos, int totalProcessos);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    vector<Intervalo> intervalos;
    int totalProcessos;

    QColor corProcesso(int id);
};

#endif