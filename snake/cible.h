#ifndef CIBLE_H
#define CIBLE_H

#include "point.h"
#include <vector>

class Cible
{

private:
    Point m_cible;
public:
    Cible();
    Cible(Point p);
    ~Cible();
    Point getCible();
    void setCible(Point p);

    //réinitialise la position de la cible, en assurant qu'elle ne fasse pas partie de corps (pas de pomme qui aparait "sur" le corps).
    void resetCible(std::vector<Point> corps);
};

#endif // CIBLE_H
