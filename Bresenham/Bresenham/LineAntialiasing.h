#pragma once

#include "Figure.h"
#include <QVector>
#include <QPainter>
#include <QPoint>


class LineAntialiasing :  public Figure
{
public:
	LineAntialiasing(QPoint begin_point, QPoint end_point);
	~LineAntialiasing();

	void drawFigure(QPainter &painter);
	void generatePoints();

private:
	QPoint begin_point_;
	QPoint end_point_;

	QVector<QPoint> gray_points_;
	QVector<QPoint> gray_1_2_points_;
	QVector<QPoint> gray_1_4_points_;
	QVector<QPoint> gray_3_4_points_;
};

