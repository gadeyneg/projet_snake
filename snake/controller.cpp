#include "controller.h"
#include "cible.h"
#include "macros.h"
#include "draw.h"

//dimension du plateau : 0:19 à 0:19

Controller::Controller()
{

}

Controller::~Controller()
{

}

void Controller::setCible(Cible cible)
{
    m_cible = cible;
}

void Controller::setSnake(Serpent snake)
{
    m_snake = snake;
}

void Controller::setDrawer(Draw* drawer)
{
    m_drawer = drawer;
}

Serpent Controller::getSnake()
{
    return this->m_snake;
}

Cible Controller::getCible()
{
    return this->m_cible;
}

int Controller::isDead(Point new_point)
{
    //vérifier que le serpent ne sort pas du jeux
    if(new_point.getX()>19 or new_point.getY()>19 or new_point.getX()<0 or new_point.getY()<0){
        return 1;
    }
    for(int i=0; i<(int)m_snake.getCorps().size(); i++){
        if(new_point.getX() == m_snake.getCorps()[i].getX() and new_point.getY() == m_snake.getCorps()[i].getY()){
            return 1;
        }
    }
    return 0;
}

void Controller::action(int direction)
{
    //utilisation de macros
    auto fin = m_snake.getCorps().size()-1;
    int x = m_snake.getCorps()[fin].getX();
    int y = m_snake.getCorps()[fin].getY();
    int new_x = 0;
    int new_y = 0;

    switch(direction){
    case LEFT :
        new_x = x-1;
        new_y = y;
        break;
    case RIGHT :
        new_x = x+1;
        new_y = y;
        break;
    case UP :
        new_x = x;
        new_y = y-1;
        break;
    case DOWN :
        new_x = x;
        new_y = y+1;
        break;
    }

    Point new_point(new_x, new_y);
    if(Controller::isDead(new_point) == 1){
        //tuer le serpent
        m_snake.setPerdu(true);
    }else{
        if(new_point.getX() == m_cible.getCible().getX() and new_point.getY() == m_cible.getCible().getY()){
            //on gagne un point
            m_snake.add(new_point);
            m_cible.resetCible(m_snake.getCorps());
        }else{
            //on ne gagne pas de point
            m_snake.addAndDelete(new_point);
        }
    }
}

void Controller::nextMove(Reseau &reseau)
{
    std::vector<float> inputs = Controller::getInputs();
    std::vector<float> output = reseau.compute(inputs);
    int decision = Controller::decision(output);
    Controller::action(decision);
}

int Controller::decision(std::vector<float> output)
{
    int res = 0;
    for(int i = 1; i<output.size();i++){
        if(output[i]>output[0]){
            res=i;
        }
    }
    return res;
}

void Controller::resetSnake()
{
    setSnake(Serpent(Point(10,10)));
    m_snake.m_perdu = false;
    m_cible.resetCible(m_snake.corps);
}

std::vector<float> Controller::getInputs()
{
    std::vector<float> res;
    int teteX = m_snake.getCorps()[0].getX();
    int teteY = m_snake.getCorps()[0].getY();
    res.push_back(teteX);
    res.push_back(teteY);
    res.push_back(m_cible.getCible().getX());
    res.push_back(m_cible.getCible().getX());
    //maintenant, le snake "regarde" autour de lui.
    //à droite
    for(int i = 0; i<m_snake.getCorps().size(); i++){
        if(i!=0 and teteY == m_snake.getCorps()[i].getY() and teteX < m_snake.getCorps()[i].getX()){
            res.push_back(m_snake.getCorps()[i].getX()-teteX);
            break;
        }
        if(i==m_snake.getCorps().size()-1){
            //on a parcouru tout le serpent sans rencontrer de corps à droite
            res.push_back(20-teteX);
        }
    }
    //a gauche
    for(int i = 0; i<m_snake.getCorps().size(); i++){
        if(i!=0 and teteY == m_snake.getCorps()[i].getY() and teteX > m_snake.getCorps()[i].getX()){
            res.push_back(teteX-m_snake.getCorps()[i].getX());
            break;
        }
        if(i==m_snake.getCorps().size()-1){
            //on a parcouru tout le serpent sans rencontrer de corps à droite
            res.push_back(teteX);
        }
    }
    //en bas
    for(int i = 0; i<m_snake.getCorps().size(); i++){
        if(i!=0 and teteX == m_snake.getCorps()[i].getX() and teteY < m_snake.getCorps()[i].getY()){
            res.push_back(m_snake.getCorps()[i].getY()-teteY);
            break;
        }
        if(i==m_snake.getCorps().size()-1){
            //on a parcouru tout le serpent sans rencontrer de corps à droite
            res.push_back(20-teteY);
        }
    }
    //en haut
    for(int i = 0; i<m_snake.getCorps().size(); i++){
        if(i!=0 and teteX == m_snake.getCorps()[i].getX() and teteY > m_snake.getCorps()[i].getY()){
            res.push_back(teteY-m_snake.getCorps()[i].getY());
            break;
        }
        if(i==m_snake.getCorps().size()-1){
            //on a parcouru tout le serpent sans rencontrer de corps à droite
            res.push_back(teteY);
        }
    }

    res.push_back(1); //le biai
    return res;
}
