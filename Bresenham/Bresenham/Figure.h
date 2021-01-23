#pragma once
#include <QPainter>

class Figure
{
public:
	Figure() {};
	~Figure() {};

	virtual void drawFigure(QPainter &painter) = 0;
};
