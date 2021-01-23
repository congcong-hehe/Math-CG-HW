#pragma once

#include "Figure.h"
#include <QVector>
#include <QPainter>
#include <QPoint>

class CircleAntialiasing : public Figure
{
public:
	CircleAntialiasing(QPoint center_point, QPoint edge_point);
	~CircleAntialiasing();
	void drawFigure(QPainter& painter);
	void generatePoints();
private:
	QPoint center_point_;
	QPoint edge_point_;
	QVector<QPoint> gray_points_;
	QVector<QPoint> gray_1_4_points_;
};

