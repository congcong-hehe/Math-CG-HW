#pragma once

#include <QtWidgets/QWidget>
#include "ui_MiniDraw.h"
#include "Line.h"
#include "Ellipse.h"
#include "Rect.h"
#include "Polygon.h"
#include "Freehand.h"
#include <QMouseEvent>
#include <vector>
#include <QPainter>

class MiniDraw : public QWidget
{
    Q_OBJECT

public:
    MiniDraw(QWidget *parent = Q_NULLPTR);
    ~MiniDraw();

    enum class FigureType{TLine, TEllipse, TRect, TPolygon, TFreehand};

    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void changeBtnColor();

private:
    Ui::MiniDrawClass ui;

    std::vector<Figure*> figure_array;  //图形指针数组
    std::vector<QPoint> points;     //保存目前屏幕上的点
    FigureType current_figure;  //当前选择的图形

    QPoint begin_point_;    

private slots:
    void clear();       // 清空绘图面板
    void setLine();
    void setEllipse();
    void setRect();
    void setPolygon();
    void setFreehand();
};
