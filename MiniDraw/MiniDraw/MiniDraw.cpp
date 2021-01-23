#include "MiniDraw.h"
#include <QPixmap>
#include <QStyleOption>

MiniDraw::MiniDraw(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    this->setFixedSize(800, 600);
    current_figure = FigureType::TFreehand;
    begin_point_ = QPoint(-10, -10);
    ui.freehand_btn->setStyleSheet("color: red");
}

MiniDraw::~MiniDraw()
{
    clear();
}


void MiniDraw::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);

    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(e);

    QPixmap pixmap(700, 800);
    pixmap.fill(Qt::white);
    QPainter pp(&pixmap);
    QPen pen;

    pen.setWidth(5);
    pen.setColor(Qt::blue);
    pp.setPen(pen);
    switch (current_figure)
    {
    case FigureType::TPolygon:
        for (int i = 0; i < points.size(); ++i)
        {
            pp.drawPoint(points[i]);
        }
        break;
    case FigureType::TFreehand:
        pen.setWidth(1);
        pen.setColor(Qt::black);
        pp.setPen(pen);
        for (std::vector<QPoint>::size_type i = 1; i < points.size(); ++i)
        {
            pp.drawLine(points[i-1], points[i]);
        }
        
        break;
    default:
        pp.drawPoint(begin_point_);
        break;
    }

    pen.setWidth(1);
    pen.setColor(Qt::black);
    pp.setPen(pen);
    for (int i = 0; i < figure_array.size(); ++i)
    {
        figure_array[i]->drawFigure(pp);
    }

    painter.drawPixmap(0, 3, pixmap);
}

void MiniDraw::mousePressEvent(QMouseEvent* event)
{
    if (Qt::LeftButton == event->button())
    {
        switch (current_figure)
        {
        case FigureType::TPolygon:
            points.push_back(event->pos());
            break;
        case FigureType::TFreehand:
            points.push_back(event->pos());
            break;
        default:
            begin_point_ = event->pos();
            break;
        }
    }
    else if (Qt::RightButton == event->button() && current_figure != FigureType::TFreehand)
    {
        Figure* figure = nullptr;
        switch (current_figure)
        {
        case FigureType::TPolygon:
            points.push_back(event->pos());
            figure = new Polygon(points);
            points.clear();
            break;
        case FigureType::TLine:
            figure = new Line(begin_point_, event->pos());
            break;
        case FigureType::TEllipse:
            figure = new Ellipse(begin_point_, (event->pos()).rx() - begin_point_.rx(),
                (event->pos()).ry() - begin_point_.ry());
            break;
        case FigureType::TRect:
            figure = new Rect(begin_point_, (event->pos()).rx() - begin_point_.rx(),
                (event->pos()).ry() - begin_point_.ry());
            break;
        }
        figure_array.push_back(figure);
    }
    update();       //强制调用paintEvent()
}

void MiniDraw::mouseMoveEvent(QMouseEvent* event)
{
    if (FigureType::TFreehand == current_figure) {
        points.push_back(event->pos());
        update();
    }
}

void MiniDraw::mouseReleaseEvent(QMouseEvent* event)
{
    Figure* figure = nullptr;
    if (FigureType::TFreehand == current_figure) {
        figure = new Freehand(points);
        points.clear();
        figure_array.push_back(figure);
        update();
    }
}

void MiniDraw::clear()
{
    for (int i = 0; i < figure_array.size(); ++i)
    {
        if (nullptr != figure_array[i])
        {
            delete figure_array[i];
        }
    }
    figure_array.clear();
    update();
}

void MiniDraw::setLine() 
{ 
    changeBtnColor();
    current_figure = FigureType::TLine; 
    ui.line_btn->setStyleSheet("color: red");
}

void MiniDraw::setEllipse()
{ 
    changeBtnColor();
    current_figure = FigureType::TEllipse;
    ui.ellipse_btn->setStyleSheet("color: red");
}

void MiniDraw::setRect()
{ 
    changeBtnColor();
    current_figure = FigureType::TRect; 
    ui.rect_btn->setStyleSheet("color: red");
}
void MiniDraw::setPolygon()
{ 
    changeBtnColor();
    current_figure = FigureType::TPolygon;
    ui.polygon_btn->setStyleSheet("color: red");
}

void MiniDraw::setFreehand()
{ 
    changeBtnColor();
    current_figure = FigureType::TFreehand; 
    ui.freehand_btn->setStyleSheet("color: red");
}

void MiniDraw::changeBtnColor()
{
    switch (current_figure)
    {
    case FigureType::TFreehand:
        ui.freehand_btn->setStyleSheet("color: black");
        break;
    case FigureType::TLine:
        ui.line_btn->setStyleSheet("color: black");
        break;
    case FigureType::TEllipse:
        ui.ellipse_btn->setStyleSheet("color: black");
        break;
    case FigureType::TRect:
        ui.rect_btn->setStyleSheet("color: black");
        break;
    case FigureType::TPolygon:
        ui.polygon_btn->setStyleSheet("color: black");
        break;
    }
}
