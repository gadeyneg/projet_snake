#include "serpent.h"

Serpent::Serpent()
{

}

Serpent::Serpent(Point p)
{
    this->corps = std::vector<Point> (1, p);
    this->corps.push_back(Point(p.getX(),p.getY()+1));
    this->corps.push_back(Point(p.getX(),p.getY()+2));
    this->corps.push_back(Point(p.getX()-1,p.getY()+2));
    m_perdu = false;
}

void Serpent::setPerdu(bool val)
{
    m_perdu = val;
}

bool Serpent::getPerdu()
{
    return m_perdu;
}

void Serpent::addAndDelete(Point p)
{
    corps.erase(corps.begin());
    corps.push_back(p);
}

void Serpent::add(Point p)
{
    corps.push_back(p);
}

std::vector<Point> Serpent::getCorps(){
    return this->corps;
}
