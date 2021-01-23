#include "Polygon.h"
#include <iostream>

Polygon::Polygon(QVector<QPoint>& vertexs, QColor &color)
	: vertexes_(vertexs), color_(color)
{
	vertexes_.push_back(vertexes_[0]);	//pN = p0
}

Polygon::~Polygon()
{

}

void Polygon::draw(QPainter& painter, QPixmap& pixmap)
{
	drawLine(painter, pixmap);
	drawInside(painter, pixmap);
}

//画边线
void Polygon::drawLine(QPainter& painter, QPixmap& pixmap)
{
	painter.setPen(QPen(Qt::black, 1));
	for (int i = 0; i < vertexes_.size() - 1; ++i)
	{
		double dy = vertexes_[i + 1].y() - vertexes_[i].y();
		int  y_min, y_max;
		double x;
		if (dy != 0)
		{
			double dx = (vertexes_[i + 1].x() - vertexes_[i].x()) / dy;
			if (dy > 0)
			{
				x = vertexes_[i].x();
				y_min = vertexes_[i].y();
				y_max = vertexes_[i + 1].y();
			}
			else
			{
				x = vertexes_[i + 1].x();
				y_min = vertexes_[i + 1].y();
				y_max = vertexes_[i].y();
			}
			for (int y = y_min + 1; y <= y_max; ++y)
			{
				x += dx;
				painter.drawPoint(int(x + 0.5), y);
				//x += dx;
			}
		}
	}
}

//边标志算法画内部点阵
void Polygon::drawInside(QPainter& painter, QPixmap& pixmap)
{
	int x_min, x_max, y_min, y_max;
	x_max = x_min = vertexes_[0].x();
	y_max = y_min = vertexes_[0].y();

	//计算多边形包围盒
	for (int i = 1; i < vertexes_.size(); ++i)
	{
		int x = vertexes_[i].x();
		int y = vertexes_[i].y();
		if (x_min > x)
		{
			x_min = x;
		}
		if (x_max < x)
		{
			x_max = x;
		}
		if (y_min > y)
		{
			y_min = y;
		}
		if (y_max < y)
		{
			y_max = y;
		}
	}

	//画点阵
	painter.setPen(QPen(color_, 1));
	QImage img = pixmap.toImage();
	for (int y = y_min; y <= y_max; ++y)
	{
		bool inside = false;
		for (int x = x_min; x <= x_max; ++x)
		{
			if (img.pixelColor(x, y).black() == 255)
			{
				inside = !inside;
			}
			if (inside)
			{
				painter.drawPoint(x, y);
			}
		}
	}
}
