#include "ganttwidget.h"

GanttWidget::GanttWidget(QWidget *parent) : QWidget(parent) {
    totalProcessos = 0;
}

void GanttWidget::setDados(vector<Intervalo>& ivs, int total) {
    intervalos = ivs;
    totalProcessos = total;
    update(); // força redesenho
}

QColor GanttWidget::corProcesso(int id) {
    // cor diferente para cada processo
    static QList<QColor> cores = {
        QColor(70, 130, 180),  // azul
        QColor(220, 100, 60),  // laranja
        QColor(80, 160, 80),   // verde
        QColor(180, 80, 180),  // roxo
        QColor(200, 180, 50),  // amarelo
    };
    return cores[(id - 1) % cores.size()];
}

void GanttWidget::paintEvent(QPaintEvent *event) {
    if (intervalos.empty()) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int margem = 50;
    int alturaBloco = 30;
    int larguraTotal = width() - 2 * margem;

    // calcula tempo total
    int tempoMax = 0;
    for (auto& iv : intervalos) {
        if (iv.fim > tempoMax) tempoMax = iv.fim;
    }

    if (tempoMax == 0) return;

    float escala = (float)larguraTotal / tempoMax;

    // desenha cada intervalo
    for (auto& iv : intervalos) {
        int x = margem + iv.inicio * escala;
        int w = (iv.fim - iv.inicio) * escala;
        int y = margem + (iv.idProcesso - 1) * (alturaBloco + 10);

        // bloco colorido
        painter.setBrush(corProcesso(iv.idProcesso));
        painter.setPen(Qt::black);
        painter.drawRect(x, y, w, alturaBloco);

        // label P1, P2...
        painter.setPen(Qt::white);
        painter.drawText(x, y, w, alturaBloco, Qt::AlignCenter,
                         QString("P%1").arg(iv.idProcesso));
    }

    // eixo de tempo
    painter.setPen(Qt::black);
    for (int t = 0; t <= tempoMax; t++) {
        int x = margem + t * escala;
        painter.drawLine(x, margem - 10, x, margem - 5);
        painter.drawText(x - 5, margem - 15, QString::number(t));
    }
}