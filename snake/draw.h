#pragma once

#ifndef DRAW_H
#define DRAW_H

#include "point.h"
#include "cible.h"
#include "serpent.h"
// #include "controller.h"   //le drawer n'a plus son controller en argument pour l'instant. car pb ( inclusion récursive entre autre ).
class Controller;
#include <vector>
#define SIZE 30 //taille d'une case du jeux

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPixmap>

class Draw : public QLabel
{
    Q_OBJECT
public:
    explicit Draw(QWidget *parent = nullptr);
    ~Draw();

    //permet de dessiner un carré. Coin haut gauche en x,y.
    //Couleur vaut 0,1 ou 2 seon qu'on dessine la pomme, la tete, ou le score.
    void drawCarre(int x, int y, int taille, int couleur);

    void setController(Controller*);

    void setLost(bool);

public slots:

    //dessine le jeux actuel. Utilise m_controller à cet effet.
    void draw();

protected:
    QImage m_image;
    Controller *m_controller;
    bool m_lost;

};

#endif // DRAW_H
