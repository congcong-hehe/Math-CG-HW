#pragma once

#include <QPainter>
#include <QPoint>
#include <QVector>

class Polygon
{
public:
	Polygon(QVector<QPoint>& vertexs, QColor &color);
	~Polygon();

	void drawLine(QPainter& painter, QPixmap& pixmap);
	void drawInside(QPainter& painter, QPixmap& pixmap);
	void draw(QPainter& painter, QPixmap& pixmap);

private:
	QVector<QPoint> vertexes_;		//¶¥µã

	QColor color_;
};

