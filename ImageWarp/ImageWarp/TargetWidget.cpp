#include "TargetWidget.h"

TargetWidget::TargetWidget(QImage* target_img): target_img_(target_img)
{
	
}

TargetWidget::~TargetWidget()
{
}

void TargetWidget::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	painter.drawImage(0, 0, *target_img_);
}
