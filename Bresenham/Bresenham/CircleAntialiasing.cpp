#include "CircleAntialiasing.h"

CircleAntialiasing::CircleAntialiasing(QPoint center_point, QPoint edge_point)
	: center_point_(center_point), edge_point_(edge_point)
{
	generatePoints();
}

CircleAntialiasing::~CircleAntialiasing()
{

}

void CircleAntialiasing::drawFigure(QPainter& painter)
{
	painter.setPen(QPen(QColor(0, 0, 0), 1));
	painter.drawPoints(gray_points_);

	painter.setPen(QPen(QColor(192, 192, 192), 1));
	painter.drawPoints(gray_1_4_points_);
}

void CircleAntialiasing::generatePoints()
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
		gray_points_.push_back(QPoint(x, y));

		if (d < 0)
		{
			gray_1_4_points_.push_back(QPoint(x, y + 1));
		}
		else
		{
			gray_1_4_points_.push_back(QPoint(x, y - 1));
		}

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
	int temp_size = gray_points_.size();
	for (int i = 0; i < temp_size; ++i)
	{
		int p_x = gray_points_[i].x();
		int p_y = gray_points_[i].y();

		gray_points_.push_back(QPoint(p_y, p_x));
		gray_points_.push_back(QPoint(p_y, -p_x));
		gray_points_.push_back(QPoint(p_x, -p_y));
		gray_points_.push_back(QPoint(-p_x, -p_y));
		gray_points_.push_back(QPoint(-p_y, -p_x));
		gray_points_.push_back(QPoint(-p_y, p_x));
		gray_points_.push_back(QPoint(-p_x, p_y));
	}

	temp_size = gray_1_4_points_.size();
	for (int i = 0; i < temp_size; ++i)
	{
		int p_x = gray_1_4_points_[i].x();
		int p_y = gray_1_4_points_[i].y();

		gray_1_4_points_.push_back(QPoint(p_y, p_x));
		gray_1_4_points_.push_back(QPoint(p_y, -p_x));
		gray_1_4_points_.push_back(QPoint(p_x, -p_y));
		gray_1_4_points_.push_back(QPoint(-p_x, -p_y));
		gray_1_4_points_.push_back(QPoint(-p_y, -p_x));
		gray_1_4_points_.push_back(QPoint(-p_y, p_x));
		gray_1_4_points_.push_back(QPoint(-p_x, p_y));
	}

	for (int i = 0; i < gray_points_.size(); ++i)
	{
		gray_points_[i].rx() += center_x;
		gray_points_[i].ry() += center_y;
	}

	for (int i = 0; i < gray_1_4_points_.size(); ++i)
	{
		gray_1_4_points_[i].rx() += center_x;
		gray_1_4_points_[i].ry() += center_y;
	}
}