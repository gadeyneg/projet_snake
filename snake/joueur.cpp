#include "joueur.h"

Joueur::Joueur()
{
    m_score =0;
    //ajout test
    m_controller = Controller();
    m_controller.setCible(Cible(Point(5,5)));
    m_controller.setSnake(Serpent(Point(10,10)));
    m_controller.m_cible.resetCible(m_controller.m_snake.corps);
    //fin
    std::vector<int> topologie;
    topologie.push_back(20);

    topologie.push_back(4); //la topologie doit se finir par le nombre d'output.
    m_reseau = Reseau(topologie, 2); //l'entier désigne la fonction d'activation utilisée
}

Joueur generate_joueur2(const Joueur &a, const Joueur &b)
{
    Joueur res = a;
    //pour chaque couche du reseau
    for(int i = 0; i< res.m_reseau.m_listeCouches.size(); i++){
        //pour chaque neurone de chaque couche
        for(int j=0; j<res.m_reseau.m_listeCouches[i].m_listeNeurones.size(); j++){
            //pour chaque poids de chaque neurone
            for(int k=0; k<res.m_reseau.m_listeCouches[i].m_listeNeurones[j].m_poids.size(); k++){
                //50%de chance
                if(std::rand()%2==0){
                    //on prend le poids de b
                    res.m_reseau.m_listeCouches[i].m_listeNeurones[j].m_poids[k] = b.m_reseau.m_listeCouches[i].m_listeNeurones[j].m_poids[k];
                }
            }
        }
    }
    res.m_score = 0;
    res.m_score_2 = 0;
    return res;
}

Joueur generate_joueur(const Joueur &a, const Joueur &b)
{
    Joueur res = a;
    //pour chaque couche du reseau
    for(int i = 0; i< res.m_reseau.m_listeCouches.size(); i++){
        //pour chaque neurone de chaque couche
        for(int j=0; j<res.m_reseau.m_listeCouches[i].m_listeNeurones.size(); j++){
            //50%de chance
            if(std::rand()%2==0){
                //on prend le poids de b
                res.m_reseau.m_listeCouches[i].m_listeNeurones[j] = b.m_reseau.m_listeCouches[i].m_listeNeurones[j];

            }
        }
    }
    return res;
}

void Joueur::makePlay(){
    //créer le jeux.
    int i = 0;
    m_controller.resetSnake();
    while(m_controller.m_snake.m_perdu != true and i<600){
        m_controller.nextMove(m_reseau);
        i++;
    }
    m_score = int(m_controller.m_snake.corps.size());
    m_score_2 = i;
}

