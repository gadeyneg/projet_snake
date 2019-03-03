#include "population.h"
#include <algorithm>

Population::Population()
{

}

Population::Population(const Population &gen_precedente)
{
    unsigned long size = gen_precedente.m_listeJoueurs.size();
    unsigned long bestPlayers_size = size / 6 ;
    unsigned long randomPlayers_size = size /12;
    unsigned long childre_size = size - bestPlayers_size - randomPlayers_size;

    //on met les meilleurs
    for(int i = 0; i< bestPlayers_size; i++){
        m_listeJoueurs.push_back(gen_precedente.m_listeJoueurs[i]);
    }

    //on met certains joueurs aléatoires
    for(int i = 0; i<randomPlayers_size; i++){
        m_listeJoueurs.push_back(gen_precedente.m_listeJoueurs[std::rand()%size]);
    }

    //enfants aléatoires : pour chaque "sélectionné", on prend un autre aprent aléatoire, et on fait un enfait.
    int added = 0;

    //s'assurer que chaque parent a deux enfants
    for(int k = 0; k<2; k++){
        for(int j = 0; j < bestPlayers_size+randomPlayers_size; j++){
            //le premier parent est le j.
            //le deuxième est tiré aléatoirement
            m_listeJoueurs.push_back(generate_joueur(
                                         m_listeJoueurs[j],
                                         m_listeJoueurs[std::rand()%bestPlayers_size+randomPlayers_size]
                                         ));
            added+=1;
        }
    }

    //on complète
    while(m_listeJoueurs.size() < gen_precedente.m_listeJoueurs.size()){
        m_listeJoueurs.push_back(generate_joueur(
                                     m_listeJoueurs[std::rand()%bestPlayers_size+randomPlayers_size],
                                     m_listeJoueurs[std::rand()%bestPlayers_size+randomPlayers_size]
                                     ));
        added+=1;
    }
    //on remet les scores à 0 et on fait rejouer.
    for(int i=0; i < size;i++){
        m_listeJoueurs[i].m_score=0;
        m_listeJoueurs[i].makePlay();
    }
}

Population::Population(unsigned long size)
{
    m_listeJoueurs = std::vector<Joueur>(size);
    for(int i=0; i<size;i++){
        m_listeJoueurs[i].makePlay();
    }
}

void Population::sort()
{
    int intervalle = m_listeJoueurs.size();
    bool changed = false;
    int i;

    while(intervalle > 1 or changed == true){
        intervalle = intervalle/1.3;
        if(intervalle<1){
            intervalle = 1;
        }

        i=0;
        changed = false;

        while(i < m_listeJoueurs.size() - intervalle){
            if(m_listeJoueurs[i].m_score < m_listeJoueurs[i+intervalle].m_score){
                iter_swap(m_listeJoueurs.begin()+i, m_listeJoueurs.begin()+i+intervalle);
                changed = true;
            }else if(m_listeJoueurs[i].m_score == m_listeJoueurs[i+intervalle].m_score and m_listeJoueurs[i].m_score_2 < m_listeJoueurs[i+intervalle].m_score_2){
                iter_swap(m_listeJoueurs.begin()+i, m_listeJoueurs.begin()+i+intervalle);
                changed = true;
            }
            i = i+1;
        }
    }
}
