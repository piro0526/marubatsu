#pragma once
#include <string>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <iosfwd>


// 座標. 
class Point
{
public:
    Point()
    {
        Point(0, 0);
    }

    Point(int x, int y)
    {
        _x = x;
        _y = y;
    }

    int getX() const;
    int getY() const;

    void setX(int x);
    void setY(int y);

private:
    int _x;
    int _y;
};
