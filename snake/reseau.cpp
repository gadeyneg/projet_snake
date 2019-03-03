#include "reseau.h"
#include <iostream>
#include <tgmath.h>
#define INPUT_SIZE 7 //9 avec 4 valeurs tete/cible //8 sans biai


Reseau::Reseau()
{

}

Reseau::Reseau(std::vector<int> topo, int fct){
    m_listeCouches = std::vector<Couche>(topo.size());
    //l'appel pour chaque neurone rend tous les poids identiques.
    for(unsigned long i=0; i < topo.size();i++){
        if(i==0){
            m_listeCouches[i] = Couche(topo[i], INPUT_SIZE);
        }else{
        m_listeCouches[i] = Couche(topo[i], topo[i-1]);
        }
    }
    m_fonction = fct;
}

std::vector<float> Reseau::compute(std::vector<float> inputs){
    for(int i=0; i<m_listeCouches.size(); i++){ //on regarde chaque couche
        if(i==0){           //première couche différente
            for(int j=0; j<m_listeCouches[i].m_listeNeurones.size(); j++){ //
                m_listeCouches[i].m_listeNeurones[j].updateNeurone(inputs);
            }
        }else{
            std::vector<float> new_inputs = std::vector<float>();           //pour chaque autre couche, on créé une liste avec les valeurs d'émission des neurones
            for(int j=0; j<m_listeCouches[i-1].m_listeNeurones.size(); j++){ //pour chaque neurone de la couche précédante
                float val = m_listeCouches[i-1].m_listeNeurones[j].m_currentValue;
                new_inputs.push_back(Reseau::activate(val));                                  //RAJOUTER LA FONCTION D'ACTIVATION
            }
            for(int j=0; j<m_listeCouches[i].m_listeNeurones.size(); j++){ //
                m_listeCouches[i].m_listeNeurones[j].updateNeurone(new_inputs);
            }
        }
    }
    std::vector<float> res;
    for(int i=0; i < m_listeCouches[m_listeCouches.size()-1].m_listeNeurones.size(); i++){ //pour chaque neurone de la dernière couche
        res.push_back(m_listeCouches[m_listeCouches.size()-1].m_listeNeurones[i].m_currentValue);
    }
    return res;
}

float Reseau::activate(float value){
    if(m_fonction==0){
        //identite
        return value;
    }
    if(m_fonction==1){
        //ReLU
        if(value>0){
            return value;
        }else{
            return 0;
        }
    }
    if(m_fonction==2){
        //tanh
        return tanh(value);
    }
}
