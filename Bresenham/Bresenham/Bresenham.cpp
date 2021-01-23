#include "Bresenham.h"
#include <iostream>

Bresenham::Bresenham(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    this->setFixedSize(600, 400);
    current_mouse_mode_ = MouseMode::LEFT;
    begin_point_ = QPoint(-1, -1);
    end_point_ = QPoint(-1, -1);
    pixmap_x_ = ui.widget_2->x();
    pixmap_y_ = ui.widget_2->y();
}

Bresenham::~Bresenham()
{
    clear_slot();
}

void Bresenham::paintEvent(QPaintEvent* event)
{
    std::cout << "123";
    QPainter painter(this);
    QPixmap pixmap(ui.widget_2->width(),ui.widget_2->height());
    pixmap.fill(Qt::white);
    QPainter pp(&pixmap);

    pp.setPen(QPen(Qt::blue, 3));
    pp.drawPoint(begin_point_);
    pp.setPen(QPen(Qt::red, 3));
    pp.drawPoint(end_point_);

    for (int i = 0; i < figures_.size(); ++i)
    {
        figures_[i]->drawFigure(pp);
    }

    painter.drawPixmap(pixmap_x_, pixmap_y_ , pixmap);
}

void Bresenham::mousePressEvent(QMouseEvent* event)
{
    int x = event->pos().x();
    int y = event->pos().y();

    if (x < pixmap_x_ || x > pixmap_x_ + ui.widget_2->width() ||
        y < pixmap_y_ || y > pixmap_y_ + ui.widget_2->height())
    {
        return;
    }
       

    if (Qt::LeftButton == event->button())
    {
        if (current_mouse_mode_ == MouseMode::LEFT)
        {
            begin_point_ = QPoint(x - pixmap_x_, y - pixmap_y_);
            current_mouse_mode_ = MouseMode::RIGHT;
            update();
        }
    }
    else
    {
        if (current_mouse_mode_ == MouseMode::RIGHT)
        {
            end_point_ = QPoint(x - pixmap_x_, y - pixmap_y_);
            current_mouse_mode_ = MouseMode::LEFT;
            if (ui.comboBox->currentIndex() == 0)
            {
                if (ui.checkBox->isChecked())
                {
                    figures_.push_back(new LineAntialiasing(begin_point_, end_point_));
                }
                else
                {
                    figures_.push_back(new Line(begin_point_, end_point_));
                }
            }
            else
            {
                if (ui.checkBox->isChecked())
                {
                    figures_.push_back(new CircleAntialiasing(begin_point_, end_point_));
                }
                else
                {
                    figures_.push_back(new Circle(begin_point_, end_point_));
                }
                
            }
            begin_point_ = QPoint(-1, -1);
            end_point_ = QPoint(-1, -1);
            update();
        }
    }
}

void Bresenham::clear_slot()
{
    for (int i = 0; i < figures_.size(); ++i)
    {
        delete figures_[i];
    }
    figures_.clear();
    update();
}
