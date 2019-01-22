#ifndef SERPENT_H
#define SERPENT_H
#include <iostream>
#include <vector>
#include "point.h"

using namespace std;

class Serpent
{

public:
    Serpent();
    Serpent(Point p);

    //méthode utilisée quand le serpent ne mange pas de pomme.
    void addAndDelete(Point p);

    //méthode utilisée quand le serpent mange une pomme.
    void add(Point p);

    vector<Point> getCorps();

    void setPerdu(bool);

    bool getPerdu();

    //attributs.
    vector<Point> corps;
    bool m_perdu;
};

#endif // SERPENT_H
