#pragma once
#include "Figure.h"
class Ellipse :
    public Figure
{
public:
    Ellipse(QPoint center_point, int rx, int ry): center_point_(center_point), rx_(rx), ry_(ry) {}
    void drawFigure(QPainter& painter);

private:
    QPoint center_point_;
    int rx_, ry_;
};

