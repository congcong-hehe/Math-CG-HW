#include "Line.h"
//#include <iostream>

void swapPoint(QPoint& a, QPoint& b)
{
	QPoint temp = a;
	a = b;
	b = temp;
}

Line::Line(QPoint begin_point, QPoint end_point) 
	: begin_point_(begin_point), end_point_(end_point)
{
	generatePoints();
}

Line::~Line()
{

}

void Line::drawFigure(QPainter& painter)
{
	painter.setPen(QPen(Qt::black, 1));
	painter.drawPoints(points_);
}
void Line::generatePoints()
{
	if (begin_point_.y() > end_point_.y())
	{
		swapPoint(begin_point_, end_point_);
	}
	int x = begin_point_.x(), y = begin_point_.y();
	int dx = end_point_.x() - x, dy = end_point_.y() - y;
	int d = 0;

	//printf("begin: %d %d end: %d %d\n", begin_point_.x(), begin_point_.y(), end_point_.x(), end_point_.y());
	//printf("---------------------------------------\n");
	if (dx >= 0)
	{
		if (dy <= dx)
		{
			d = 2 * dy - dx;
			while (x <= end_point_.x())
			{
				points_.push_back(QPoint(x, y));
				//printf("%d %d\n", x, y);
				if (d >= 0)
				{
					y++;
					d -= 2 * dx;
				}
				d += 2 * dy;
				x++;
			}
		}
		else
		{
			d = 2 * dx - dy;
			while (y <= end_point_.y())
			{
				points_.push_back(QPoint(x, y));
				//printf("%d %d\n", x, y);
				if (d >= 0)
				{
					x++;
					d -= 2 * dy;
				}
				d += 2 * dx;
				y++;
			}
		}
	}
	else
	{
		if (dy <= -dx)
		{
			d = dx - 2 * dy;
			while (x >= end_point_.x())
			{
				points_.push_back(QPoint(x, y));
				//printf("%d %d\n", x, y);
				if (d >= 0)
				{
					y++;
					d -= 2 * (-dx);
				}
				d += 2 * dy;
				x--;
			}
		}
		else
		{
			d = dy - 2 * dx;
			while (y <= end_point_.y())
			{
				points_.push_back(QPoint(x, y));
				//printf("%d %d\n", x, y);
				if (d >= 0)
				{
					x--;
					d -= 2 * dy;
				}
				d += 2 * (-dx);
				y++;
			}
		}
	}
	
}
