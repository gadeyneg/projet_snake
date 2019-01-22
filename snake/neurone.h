#ifndef NEURONE_H
#define NEURONE_H

#include <vector>

class Neurone
{
public:
    Neurone();

    //création d'un neurone relié à "taille" neurone. taille est donc la longueur de la liste de poids
    //les poids sont initialisés aléatoirements.
    Neurone(unsigned long taille);

    //création d'un neurone en faisant prendre la valeur liste_pods à m_poids.
    Neurone(std::vector<float> liste_poids);

    ~Neurone();

    void setPoids(std::vector<float>);

    //change la valeur émise par le neurone "m_currentvalue" en fonction des inputs et de m_poids.
    float updateNeurone(std::vector<float> inputs);

    std::vector<float> m_poids;
    float m_currentValue;
};

#endif // NEURONE_H
