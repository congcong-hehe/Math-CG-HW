#pragma once
#include "Figure.h"

class Freehand :
    public Figure
{
public:
    Freehand(std::vector<QPoint> points) : points_(points) {}
    void drawFigure(QPainter& painter);

private:
    std::vector<QPoint> points_;

};

