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

    QString file_name_;  // �򿪵������ļ�����

private slots:
    void slot_openFile();   // ���ļ�
    void slot_reload();     // �����ļ�
    void slot_simplify();   // �����
};
