#pragma once

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include "IDW.h"
#include "RBF.h"

class SourceWidget : public QWidget
{
	Q_OBJECT

public:
	SourceWidget(QImage* source_img);
	~SourceWidget();

	enum class ClickMode{LEFT, RIGHT};

	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent *event);

	void imageWarpByIDW(QImage* target_img, bool* if_change);
	void imageWarpByRBF(QImage* target_img, bool* if_change);
	void clearPoints();
	//whether p_points.size() == q_points.size()
	bool equal();

private:
	QImage* source_img_;
	
	std::vector<QPoint> p_points_;
	std::vector<QPoint> q_points_;

	ClickMode current_mode_;
};
