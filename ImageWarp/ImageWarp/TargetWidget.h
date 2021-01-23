#pragma once

#include <QWidget>
#include <QImage>
#include <QPainter>

class TargetWidget : public QWidget
{
	Q_OBJECT

public:
	TargetWidget(QImage* target_img);
	~TargetWidget();

	void paintEvent(QPaintEvent*);

private:
	QImage* target_img_;
};
