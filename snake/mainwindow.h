#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller.h"
#include <QKeyEvent>
#include "draw.h"
#include "macros.h"
#include <thread>
#include <chrono>
#include <unistd.h>
#include "reseau.h"
#include <QApplication>
#include "serpent.h"
#include "joueur.h"
#include "population.h"
#include <QTimer>
#include <iostream>
#include <sstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setController(Controller cont);

public slots:

    //entrainement d'une ai, simulation du résultat.
    void launchAI();

    //mode joueur.
    void launchSnake();

    //retour au menu.
    void backtomenue();

    //controle du mode simulation :

    //appelé par le timer, fait jouer le réseau de la génération courante.
    void proceed();

    //passage à la génération suivante.
    void gotonext();

    //passage à la génération précédente.
    void gotoprevious();

    //permet de diminuer l'intervalle entre deux actions.
    void speedtimer();

    //augmente l'intervalle de temps entre deux actions.
    void slowtimer();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    Controller m_controller;
};

#endif // MAINWINDOW_H
