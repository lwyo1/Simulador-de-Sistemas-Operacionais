#ifndef TELA_INICIAL_H
#define TELA_INICIAL_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Tela_Inicial : public QMainWindow
{
    Q_OBJECT
public:
    explicit Tela_Inicial(QWidget *parent = nullptr);

signals:
};

#endif // TELA_INICIAL_H
