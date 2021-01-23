#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QDebug>
#include <QString>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <QFileDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);

private:
    Ui::MainWindowClass ui;

    QString file_name_;  // 打开的网格文件名字

private slots:
    void slot_openFile();   // 打开文件
    void slot_reload();     // 重载文件
    void slot_simplify();   // 网格简化
};
