#pragma once

#include "Figure.h"
#include <QVector>
#include <QPainter>
#include <QPoint>
#include <math.h>

class Circle : public Figure
{
public:
	Circle(QPoint center_point, QPoint edge_point);
	~Circle();
	void drawFigure(QPainter& painter);
	void generatePoints();

private:
	QPoint center_point_;
	QPoint edge_point_;
	QVector<QPoint> points_;
};

