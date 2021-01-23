#pragma once
#include "Figure.h"

class Line : public Figure
{
public:
	Line(QPoint begin_point, QPoint end_point) : begin_point_(begin_point), end_point_(end_point) {}

	void drawFigure(QPainter& painter);

private:
	QPoint begin_point_;
	QPoint end_point_;
};