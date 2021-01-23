#include "Freehand.h"

void Freehand::drawFigure(QPainter& painter)
{
	for (std::vector<QPoint>::size_type i = 1; i < points_.size(); ++i)
	{
		painter.drawLine(points_[i-1], points_[i]);
	}
}