#ifndef RESEAU_H
#define RESEAU_H

#include <vector>
#include "couche.h"

class Reseau
{
public:
    Reseau();

    //création d'un réseau en fonction d'une topologie, et d'un entier désignant la fonction d'activation utlisée.
    Reseau(std::vector<int> topologie, int fct);

    //prend les inputs en entrée, et donne les output en sortie.
    std::vector<float> compute(std::vector<float> inputs); //ici, on renvoie 4 flottants

    //fonction d'activation, permet d'en utiliser plusieurs selon le cas.
    float activate(float);

    //attributs.
    std::vector<Couche> m_listeCouches;
    int m_fonction;
};

#endif // RESEAU_H
