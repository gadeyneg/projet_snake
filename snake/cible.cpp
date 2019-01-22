#include "cible.h"
#include "stdlib.h"
#include <time.h>


Cible::Cible()
{

}

Cible::Cible(Point p){
    this->m_cible = p;
}

Cible::~Cible(){

}

Point Cible::getCible(){
    return this->m_cible;
}

void Cible::setCible(Point p)
{
    m_cible = p;
}

void Cible::resetCible(std::vector<Point> corps){
    this->m_cible.~Point();
    bool fini = false;
    bool rate;
    int x = 0;
    int y = 0;
    while(!fini){
        x = std::rand()%19;
        y = std::rand()%19;
        rate=false;
        for(unsigned long i=0; i< corps.size(); i++){
            if(corps[i].getX()==x and corps[i].getY()==y){
                rate = true;  //gérer la cible dans le corps
            }
            fini = !rate;
        }
    }
    Point p(x, y);
    this->m_cible = p;
}
