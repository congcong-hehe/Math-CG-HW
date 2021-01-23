#include "Rect.h"

void Rect::drawFigure(QPainter &painter)
{
	painter.drawRect(begin_point_.x(), begin_point_.y(), w_, h_);
}
