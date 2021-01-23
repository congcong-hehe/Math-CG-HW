#pragma once

#include <QtWidgets/QWidget>
#include "ui_ImageWarp.h"
#include "SourceWidget.h"
#include "TargetWidget.h"
#include <QImage>

class ImageWarp : public QWidget
{
    Q_OBJECT

public:
    ImageWarp(QWidget *parent = Q_NULLPTR);
    ~ImageWarp();
    void fillHole(QImage* target_img, bool* change);

    enum class TransferMode { IDW, RBF };

private:
    Ui::ImageWarpClass ui;

    QImage* source_img_;

    SourceWidget* source_widget_;

    TransferMode current_mode_;
    
private slots:
    void openFile();
    void imageWarp();
    void clearPoints();
    void chooseAlgorithm();
};
