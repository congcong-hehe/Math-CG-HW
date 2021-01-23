#include "Circle.h"

Circle::Circle(QPoint center_point, QPoint edge_point) :
	center_point_(center_point), edge_point_(edge_point)
{
	generatePoints();
}

Circle::~Circle()
{

}

void Circle::drawFigure(QPainter& painter)
{
	painter.setPen(QPen(Qt::black, 1));
	painter.drawPoints(points_);
}

void Circle::generatePoints()
{
	int center_x = center_point_.x();
	int center_y = center_point_.y();
	int r = (int)round(sqrt((center_x - edge_point_.x()) * (center_x - edge_point_.x())
		+ (center_y - edge_point_.y()) * (center_y - edge_point_.y())));
	//the initial value point is the top point of circle, move the center point to the orign point
	int x = 0, y = r; 
	int d = 2 - 3 * r;

	//calculate points of 1/8 of circle
	while (x < y)
	{
		points_.push_back(QPoint(x, y));
		if (d < 0)
		{
			d += 4 * x + 6;
		}
		else
		{
			d += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}

	//calculate other points of circle
	int temp_size = points_.size();
	for (int i = 0; i < temp_size; ++i)
	{
		int p_x = points_[i].x();
		int p_y = points_[i].y();

		points_.push_back(QPoint(p_y, p_x));
		points_.push_back(QPoint(p_y, -p_x));
		points_.push_back(QPoint(p_x, -p_y));
		points_.push_back(QPoint(-p_x, -p_y));
		points_.push_back(QPoint(-p_y, -p_x));
		points_.push_back(QPoint(-p_y, p_x));
		points_.push_back(QPoint(-p_x, p_y));
	}

	for (int i = 0; i < points_.size(); ++i)
	{
		points_[i].rx() += center_x;
		points_[i].ry() += center_y;
	}
}

