#include "Polygon.h"

void Polygon::drawFigure(QPainter& painter)
{
	for (std::vector<QPoint>::size_type i = 1; i < points_.size(); ++i)
	{
		painter.drawLine(points_[i-1], points_[i]);
	}
	painter.drawLine(points_[points_.size()-1], points_[0]);
}
