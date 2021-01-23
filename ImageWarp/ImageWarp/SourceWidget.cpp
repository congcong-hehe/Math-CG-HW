#include "SourceWidget.h"
#include <stdio.h>

SourceWidget::SourceWidget(QImage* source_img) 
	: source_img_(source_img)
{
	current_mode_ = ClickMode::LEFT;
}

SourceWidget::~SourceWidget()
{
}

void SourceWidget::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	painter.drawImage(0, 0, *source_img_);

	QPen pen;
	pen.setWidth(5);
	
	//paint p points
	pen.setColor(Qt::blue);
	painter.setPen(pen);
	for (int i = 0; i < p_points_.size(); ++i)
	{
		painter.drawPoint(p_points_[i]);
	}

	//paint q points
	pen.setColor(Qt::red);
	painter.setPen(pen);
	for (int i = 0; i < q_points_.size(); ++i)
	{
		painter.drawPoint(q_points_[i]);
	}

}

void SourceWidget::mousePressEvent(QMouseEvent* event)
{
	if (Qt::LeftButton == event->button())
	{
		if (current_mode_ == ClickMode::LEFT)
		{
			p_points_.push_back(event->pos());
			current_mode_ = ClickMode::RIGHT;
			update();
		}
	}
	else
	{
		if (current_mode_ == ClickMode::RIGHT)
		{
			q_points_.push_back(event->pos());
			current_mode_ = ClickMode::LEFT;
			update();
		}
	}
}

void SourceWidget::imageWarpByIDW(QImage* target_img, bool* if_change)
{
	IDW idw(p_points_, q_points_);
	int image_width = source_img_->width();
	int image_height = source_img_->height();

	for (int i = 0; i < image_width; ++i)
	{
		for (int j = 0; j < image_height; ++j)
		{
			QPoint p(i, j);
			QPoint new_p = idw.transfer(p);
			
			if (new_p.x() > 0 && new_p.y() > 0 && new_p.x() < image_width && new_p.y() < image_height)
			{
				if_change[i * image_width + j] = true;
				target_img->setPixel(new_p, source_img_->pixel(p));
			}
		}
	}
}

void SourceWidget::imageWarpByRBF(QImage* target_img, bool* if_change)
{
	RBF rbf(p_points_, q_points_);
	int image_width = source_img_->width();
	int image_height = source_img_->height();

	for (int i = 0; i < image_width; ++i)
	{
		for (int j = 0; j < image_height; ++j)
		{
			QPoint p(i, j);
			QPoint new_p = rbf.transfer(p);

			if (new_p.x() > 0 && new_p.y() > 0 && new_p.x() < image_width && new_p.y() < image_height)
			{
				if_change[i * image_width + j] = true;
				target_img->setPixel(new_p, source_img_->pixel(p));
			}
		}
	}
}

void SourceWidget::clearPoints()
{
	p_points_.clear();
	q_points_.clear();
	update();
}

bool SourceWidget::equal() {
	return p_points_.size() == q_points_.size();
}

