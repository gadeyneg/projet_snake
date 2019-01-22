#include "point.h"
#include <iostream>

Point::Point() = default;

Point::Point(int _x, int _y)
{
    this->x = _x;
    this->y = _y;
}

Point::~Point(){}

void Point::display()
{
    std::cout << "je suis en (" << this->x << "," << this->y << ")." << std::endl;
}

int Point::getX()
{
    return this->x;
}

int Point::getY()
{
    return this->y;
}
