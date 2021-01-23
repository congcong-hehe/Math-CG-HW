#pragma once

#include <QtWidgets/QWidget>
#include "ui_Bresenham.h"
#include <QPainter>
#include <QPaintEvent>
#include <Qvector>
#include "Line.h"
#include "Figure.h"
#include "Circle.h"
#include "LineAntialiasing.h"
#include "CircleAntialiasing.h"
#include <QVector>

class Bresenham : public QWidget
{
    Q_OBJECT

public:
    enum class MouseMode{LEFT, RIGHT};
    Bresenham(QWidget *parent = Q_NULLPTR);
    ~Bresenham();

private:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    Ui::BresenhamClass ui;
    MouseMode current_mouse_mode_;
    QPoint begin_point_;
    QPoint end_point_;
    int pixmap_x_;
    int pixmap_y_;

    QVector<Figure*> figures_;

private slots:
    void clear_slot();
};
