#ifndef POPULATION_H
#define POPULATION_H

#include "joueur.h"

class Population
{
public:
    Population();

    //création d'une population de taille size, poids aléatoires.
    Population(unsigned long size);

    //créé une nouvelle génération via l'algorithme génétique.
    //ici aussi, la création de population s'occupe de faire jouer les joueurs, et de les classer.
    Population(const Population &gen_precedente);

    //tri par peigne de la population selon les scores des joueurs.
    void sort();

    //attributs.
    std::vector<Joueur> m_listeJoueurs;
};

#endif // POPULATION_H
