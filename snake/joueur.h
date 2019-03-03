#ifndef JOUEUR_H
#define JOUEUR_H

#include "reseau.h"
#include "controller.h"

class Joueur
{
public:
    Joueur();

    //fait jouer une partie au joueur avec son reseau. Modifie m_score à la fin de la partie.
    void makePlay();

    int m_score;
    int m_score_2; //on classe par score, puis par longueur.
    Reseau m_reseau;
    bool m_alive;
    Controller m_controller;
};

Joueur generate_joueur(const Joueur &a, const Joueur &b);

#endif // JOUEUR_H
