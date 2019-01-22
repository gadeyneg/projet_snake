#include "serpent.h"

Serpent::Serpent()
{

}

Serpent::Serpent(Point p)
{
    this->corps = std::vector<Point> (1, p);
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
