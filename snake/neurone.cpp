#include "neurone.h"
#include <iostream>
#include "stdlib.h"
#include <time.h>

Neurone::Neurone()
{

}

Neurone::~Neurone()
{
}

Neurone::Neurone(unsigned long taille_poids)
{
    m_poids = std::vector<float>(taille_poids);
    for(int i=0; i < taille_poids; i++){
        m_poids[i] = float((std::rand()%20000-10000.0))/1000.0;
    }
}

Neurone::Neurone(std::vector<float> liste_poids){
    m_poids = liste_poids;
}

float Neurone::updateNeurone(std::vector<float> inputs){
    float newValue =0;
    for(int i =0; i< inputs.size(); i++){
        newValue = newValue + inputs[i]*m_poids[i];
    }
    m_currentValue = newValue;
    return newValue;
}
