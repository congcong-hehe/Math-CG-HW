#pragma once
#include "Figure.h"
class Rect :
    public Figure
{
public:
    Rect(QPoint begin_point, int w, int h) : begin_point_(begin_point), w_(w), h_(h) {}
    void drawFigure(QPainter &painter);

private:
    QPoint begin_point_;
    int w_, h_;
};

