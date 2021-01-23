#pragma once

#include "Figure.h"
#include <QVector>
#include <QPainter>
#include <QPoint>

class Line : public Figure
{
public:
	Line(QPoint begin_point, QPoint end_point);
	~Line();

	void drawFigure(QPainter& painter);
	void generatePoints();

private:
	QPoint begin_point_;
	QPoint end_point_;
	QVector<QPoint> points_;
};

