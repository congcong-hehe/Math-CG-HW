#pragma once
#include "Figure.h"

class Polygon :
    public Figure
{
public:
    Polygon(std::vector<QPoint> &points) : points_(points){}
    void drawFigure(QPainter &painter);

private:
    std::vector<QPoint> points_;
};

