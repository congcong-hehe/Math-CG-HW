#include "LineAntialiasing.h"
extern void swapPoint(QPoint& a, QPoint& b);

LineAntialiasing::LineAntialiasing(QPoint begin_point, QPoint end_point)
	: begin_point_(begin_point), end_point_(end_point)
{
	generatePoints();
}

LineAntialiasing::~LineAntialiasing()
{

}

void LineAntialiasing::drawFigure(QPainter &painter)
{
	painter.setPen(QPen(QColor(0, 0, 0), 1));
	painter.drawPoints(gray_points_);

	painter.setPen(QPen(QColor(128, 128, 128), 1));
	painter.drawPoints(gray_1_2_points_);

	painter.setPen(QPen(QColor(192, 192, 192), 1));
	painter.drawPoints(gray_1_4_points_);

	painter.setPen(QPen(QColor(64, 64, 64), 1));
	painter.drawPoints(gray_3_4_points_);
}

void LineAntialiasing::generatePoints()
{
	if (begin_point_.y() > end_point_.y())
	{
		swapPoint(begin_point_, end_point_);
	}
	int x = begin_point_.x(), y = begin_point_.y();
	int dx = end_point_.x() - x, dy = end_point_.y() - y;
	int d = 0;

	if (dx >= 0)
	{
		if (dy <= dx)
		{
			d = 4 * dy - 2 * dx;
			while (x <= end_point_.x())
			{
				gray_points_.push_back(QPoint(x, y));
				if (d > -1 * dx && d < 0 || d > 0 && d < dx)
				{
					gray_3_4_points_.push_back(QPoint(x, y + 1));
					gray_1_4_points_.push_back(QPoint(x, y - 1));
				}
				else
				{
					gray_1_2_points_.push_back(QPoint(x, y + 1));
					gray_1_4_points_.push_back(QPoint(x, y - 1));
				}

				if (d >= 0)
				{
					y++;
					d -= 4 * dx;
				}
				d += 4 * dy;
				x++;
			}
		}
		else
		{
			d = 4 * dx - 2 * dy;
			while (y <= end_point_.y())
			{
				gray_points_.push_back(QPoint(x, y));
				if (d > -1 * dx && d < 0 || d > 0 && d < dx)
				{
					gray_3_4_points_.push_back(QPoint(x, y + 1));
					gray_1_4_points_.push_back(QPoint(x, y - 1));
				}
				else
				{
					gray_1_2_points_.push_back(QPoint(x, y + 1));
					gray_1_4_points_.push_back(QPoint(x, y - 1));
				}

				if (d >= 0)
				{
					x++;
					d -= 4 * dy;
				}
				d += 4 * dx;
				y++;
			}
		}
	}
	else
	{
		if (dy <= -dx)
		{
			d = 2 * dx - 4 * dy;
			while (x >= end_point_.x())
			{
				gray_points_.push_back(QPoint(x, y));
				if (d > -1 * dx && d < 0 || d > 0 && d < dx)
				{
					gray_3_4_points_.push_back(QPoint(x, y + 1));
					gray_1_4_points_.push_back(QPoint(x, y - 1));
				}
				else
				{
					gray_1_2_points_.push_back(QPoint(x, y + 1));
					gray_1_4_points_.push_back(QPoint(x, y - 1));
				}

				if (d >= 0)
				{
					y++;
					d -= 4 * (-dx);
				}
				d += 4 * dy;
				x--;
			}
		}
		else
		{
			d = 2 * dy - 4 * dx;
			while (y <= end_point_.y())
			{
				gray_points_.push_back(QPoint(x, y));
				if (d > -1 * dx && d < 0 || d > 0 && d < dx)
				{
					gray_3_4_points_.push_back(QPoint(x, y + 1));
					gray_1_4_points_.push_back(QPoint(x, y - 1));
				}
				else
				{
					gray_1_2_points_.push_back(QPoint(x, y + 1));
					gray_1_4_points_.push_back(QPoint(x, y - 1));
				}

				if (d >= 0)
				{
					x--;
					d -= 4 * dy;
				}
				d += 4 * (-dx);
				y++;
			}
		}
	}

}