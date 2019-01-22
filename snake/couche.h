#ifndef COUCHE_H
#define COUCHE_H

#include <vector>
#include "neurone.h"

class Couche
{
public:
    Couche();

    ~Couche();

    //initialise une couche de "nombre_neurones neurones" possédant chacuns "nombre_poids" poids.
    //nombre poids dépendra à l'utilisation de la taille de la couche précédente.
    Couche(unsigned long nombre_neurones, unsigned long nombre_poids);

    int m_longueur; //longueur couche
    std::vector<Neurone> m_listeNeurones;
};

#endif // COUCHE_H
