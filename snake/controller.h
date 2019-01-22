#pragma once

#ifndef CONTROLLER_H
#define CONTROLLER_H


class Draw;
#include "serpent.h"
#include "cible.h"
#include "reseau.h"

class Controller
{
public:
    Controller();
    ~Controller();

    void action(int direction);
    int isDead(Point new_point);

    //fonctions set et get, relicat de quand les attributs étaient privés
    Serpent getSnake();
    Cible getCible();

    void setCible(Cible cible);
    void setSnake(Serpent snake);
    void setDrawer(Draw* drawer);

    //détermine le prochain mouvement d'un reseau. Le reseau est passé en paramètre de la méthode et non en attribut,
    //puisqu'un controller peut faire jouer plusieurs reseaux jouants sur le même serpent par exemple.
    //Ne pas mettrre const : la méthode utilise Reseau::compute(), qui modifie les valeurs émises par les neurones, et ceci est bien le comportement voulu.
    void nextMove(Reseau &reseau);

    //prend une decision sur l'action suivante en fonction des outputs obtenus en sortie d'un reseau.
    int decision(std::vector<float> output);

    //remet le jeux à 0, soit : reset al cible; m_snake de taille 1.
    void resetSnake();

    //attributs.
    Serpent m_snake;
    Cible m_cible;
    Draw* m_drawer;
    std::vector<float> getInputs(); //cette procedure ne sert que pour la partie controllée par réseau de neurone

};

#endif // CONTROLLER_H
