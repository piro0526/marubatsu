#include "Point.h"

typedef int Mark;
static const Mark EMPTY = 0;
static const Mark X = -1;
static const Mark O = 1;
static const Mark WALL = 2;

// ボードに置かれる石. 
class Disc : public Point
{
public:
    Disc() : Point(0, 0)
    {
        _mark = EMPTY;
    }

    Disc(int x, int y, Mark mark) : Point(x, y)
    {
        _mark = mark;
    }

    Mark getMark() const;
    void setMark(const Mark& mark);

private:
    // 石の色. 
    Mark _mark;
};
