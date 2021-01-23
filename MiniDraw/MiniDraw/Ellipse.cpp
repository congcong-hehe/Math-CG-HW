#include "Ellipse.h"

void Ellipse::drawFigure(QPainter& painter)
{
	painter.drawEllipse(center_point_, rx_, ry_);
}