#include "ScanTransfer.h"

ScanTransfer::ScanTransfer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setFixedSize(600, 400);
}

ScanTransfer::~ScanTransfer()
{
    vertexes_.clear();
    for (int i = 0; i < polygons_.size(); ++i)
    {
        delete polygons_[i];
    }
    polygons_.clear();
}

void ScanTransfer::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPixmap pixmap(500, 400);
    pixmap.fill(Qt::white);
    QPainter pixmap_painter(&pixmap);

    //»­µã
    pixmap_painter.setPen(QPen(Qt::black, 3));
    pixmap_painter.drawPoints(vertexes_);

    //»­Í¼ÐÎ
    for (int i = 0; i < polygons_.size(); ++i)
    {
        polygons_[i]->draw(pixmap_painter, pixmap);
    }

    painter.drawPixmap(0, 0, pixmap);
}

void ScanTransfer::mousePressEvent(QMouseEvent* event)
{
    if (Qt::LeftButton == event->button())
    {
        vertexes_.push_back(event->pos());
        update();
    }
    else
    {
        vertexes_.push_back(event->pos());
        if (ui.comboBox->currentIndex() == 0)
        {
            polygons_.push_back(new Polygon(vertexes_, QColor(Qt::red)));
        }
        else if(ui.comboBox->currentIndex() == 1)
        {
            polygons_.push_back(new Polygon(vertexes_, QColor(Qt::green)));
        }
        else
        {
            polygons_.push_back(new Polygon(vertexes_, QColor(Qt::blue)));
        }
        vertexes_.clear();
        update();
    }
}

void ScanTransfer::slot_clear()
{
    vertexes_.clear();
    for (int i = 0; i < polygons_.size(); ++i)
    {
        delete polygons_[i];
    }
    polygons_.clear();
    update();
}