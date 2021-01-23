#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ScanTransfer.h"
#include <QPainter>
#include <QPixmap>
#include <QVector>
#include <Qpoint>
#include <QMouseEvent>
#include "Polygon.h"

class ScanTransfer : public QMainWindow
{
    Q_OBJECT

public:
    ScanTransfer(QWidget *parent = Q_NULLPTR);
    ~ScanTransfer();
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    Ui::ScanTransferClass ui;
    QVector<QPoint> vertexes_;
    QVector<Polygon*> polygons_;

private slots:
    void slot_clear();
};
