#include "couche.h"
#include <iostream>

Couche::Couche()
{

}

Couche::~Couche()
{

}

Couche::Couche(unsigned long k, unsigned long p)
{
    m_listeNeurones = std::vector<Neurone>(k, Neurone(p));
    for(auto &m: m_listeNeurones){
        m= Neurone(p);
    }
}
