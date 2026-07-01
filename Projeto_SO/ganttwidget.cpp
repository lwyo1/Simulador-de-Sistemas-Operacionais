#include "ganttwidget.h"
#include <QToolTip>
#include <QMouseEvent>

GanttWidget::GanttWidget(QWidget *parent) : QWidget(parent) {
    totalProcessos = 0;
    setMouseTracking(true);
}

void GanttWidget::setDados(vector<Intervalo>& ivs, int total) {
    intervalos = ivs;
    totalProcessos = total;

    if (!intervalos.empty()) {
        int tempoMax = 0;
        for (auto& iv : intervalos) {
            if (iv.fim > tempoMax) tempoMax = iv.fim;
        }
        setMinimumWidth(max(800, tempoMax * 40));
        setMinimumHeight(totalProcessos * 60 + 80);
    } else {
        setMinimumWidth(0);
        setMinimumHeight(0);
    }

    update();
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

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    for (int proc = 1; proc <= totalProcessos; proc++) {
        int y = margem + (proc - 1) * (alturaBloco + 10);
        painter.drawText(5, y, margem - 5, alturaBloco,
                         Qt::AlignVCenter | Qt::AlignRight,
                         QString("P%1").arg(proc));
    }

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

    int legendaY = margem + totalProcessos * (alturaBloco + 10) + 20;
    for (int proc = 1; proc <= totalProcessos; proc++) {
        int x = margem + (proc - 1) * 80;
        painter.setBrush(corProcesso(proc));
        painter.setPen(Qt::black);
        painter.drawRect(x, legendaY, 20, 20);
        painter.setPen(Qt::white);
        painter.drawText(x + 25, legendaY, 60, 20, Qt::AlignVCenter,
                         QString("P%1").arg(proc));
    }
}

void GanttWidget::mouseMoveEvent(QMouseEvent *event) {
    int margem = 50;
    int alturaBloco = 30;

    int tempoMax = 0;
    for (auto& iv : intervalos) {
        if (iv.fim > tempoMax) tempoMax = iv.fim;
    }

    if (tempoMax == 0) return;

    float escala = (float)(width() - 2 * margem) / tempoMax;

    for (auto& iv : intervalos) {
        int x = margem + iv.inicio * escala;
        int w = (iv.fim - iv.inicio) * escala;
        int y = margem + (iv.idProcesso - 1) * (alturaBloco + 10);

        QRect rect(x, y, w, alturaBloco);
        if (rect.contains(event->pos())) {
            QToolTip::showText(event->globalPosition().toPoint(),
                               QString("P%1 | Início: %2 | Fim: %3 | Duração: %4")
                                   .arg(iv.idProcesso)
                                   .arg(iv.inicio)
                                   .arg(iv.fim)
                                   .arg(iv.fim - iv.inicio));
            return;
        }
    }
    QToolTip::hideText();
}