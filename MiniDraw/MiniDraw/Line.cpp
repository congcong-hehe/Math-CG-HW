#include "Line.h"

void Line::drawFigure(QPainter& painter)
{
	painter.drawLine(begin_point_, end_point_);
}