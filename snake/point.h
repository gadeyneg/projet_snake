#ifndef POINT_H
#define POINT_H


class Point
{
private:
    int x;
    int y;
public:
    Point();
    Point(int x, int y);
    ~Point();
    void display();
    int getX();
    int getY();
};

#endif // POINT_H
