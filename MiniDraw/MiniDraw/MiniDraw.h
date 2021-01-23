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

    std::vector<Figure*> figure_array;  //ͼ��ָ������
    std::vector<QPoint> points;     //����Ŀǰ��Ļ�ϵĵ�
    FigureType current_figure;  //��ǰѡ���ͼ��

    QPoint begin_point_;    

private slots:
    void clear();       // ��ջ�ͼ���
    void setLine();
    void setEllipse();
    void setRect();
    void setPolygon();
    void setFreehand();
};
