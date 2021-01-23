#pragma once
#include <QPainter>
#include <QPoint>
#include <vector>

class Figure
{
public:
	virtual void drawFigure(QPainter &painter) = 0;
};