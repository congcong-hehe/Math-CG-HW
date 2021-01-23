#include "ImageWarp.h"
#include <QString>
#include <QFileDialog>
#include <iostream>

ImageWarp::ImageWarp(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    source_img_ = new QImage();

    source_widget_ = Q_NULLPTR;
    
    current_mode_ = TransferMode::IDW;
    this->setFixedSize(362, 43);
}

ImageWarp::~ImageWarp()
{
    delete source_img_;
}


void ImageWarp::openFile()
{
     QString file_name = QFileDialog::getOpenFileName(this, "Image", ".", "Images(*.bmp *.jpg *.png *.jpeg)");

     if (file_name.isEmpty()) {
         return;
     }

     source_img_->load(file_name);
     source_widget_ = new SourceWidget(source_img_);
     std::cout << "image size : " << source_img_->width() << "  " << source_img_->height() << std::endl;
     source_widget_->setFixedSize(source_img_->width(), source_img_->height());
     source_widget_->setWindowTitle("source_image");
     source_widget_->show();
     source_widget_->update();
}

void ImageWarp::imageWarp()
{
    if (source_widget_ == Q_NULLPTR)
    {
        return;
    }

    if (!source_widget_->equal()) {
        return;
    }

    QImage* target_img = new QImage();
    *target_img = *source_img_;
    TargetWidget* target_widget;
    target_widget = new TargetWidget(target_img);

    bool* if_change = new bool[(long long)source_img_->width() * source_img_->height()]();

    if (current_mode_ == TransferMode::IDW)
    {
        source_widget_->imageWarpByIDW(target_img, if_change);

        target_widget->setFixedSize(target_img->width(), target_img->height());
        target_widget->setWindowTitle("target_image:IDW");
    }
    else
    {
        source_widget_->imageWarpByRBF(target_img, if_change);
        target_widget->setFixedSize(target_img->width(), target_img->height());
        target_widget->setWindowTitle("target_image:RBF");
    }
    fillHole(target_img, if_change);
    target_widget->show();
    target_widget->update();
    delete[]if_change;
}

void ImageWarp::clearPoints()
{
    source_widget_->clearPoints();
}

void ImageWarp::chooseAlgorithm()
{
    if (ui.comboBox->currentIndex() == 0)
    {
        current_mode_ = TransferMode::IDW;
    }
    else
    {
        current_mode_ = TransferMode::RBF;
    }
}

void ImageWarp::fillHole(QImage* target_img, bool* if_change)
{
    int x[8] = {0, 1, 1, 1, 0, -1, -1, -1 };
    int y[8] = {1, 1, 0, -1, -1, -1, 0, 1 };

    int img_width = target_img->width();
    int img_height = target_img->height();

    QColor color;

    for (int i = 1; i < img_width - 1; ++i)
    {
        for (int j = 1; j < img_height - 1; ++j)
        {
            if (!if_change[i * img_width + j])
            {
                int r = 0, g = 0, b = 0;
                for (int k = 0; k < 8; ++k)
                {
                    color = target_img->pixelColor(i + x[k], j + y[k]);
                    r += color.red();
                    g += color.green();
                    b += color.blue();
                }
                target_img->setPixelColor(i, j, QColor(r / 8, g / 8, b / 8));
            }
        }
    }
}