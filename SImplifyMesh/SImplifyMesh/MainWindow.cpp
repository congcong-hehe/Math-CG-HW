#include "MainWindow.h"
#include "Simplify.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void MainWindow::slot_openFile()
{
    QString file_name = QFileDialog::getOpenFileName(this, "mesh", ".", "meshs(*.obj)");

    // 防止打开对话框之后关闭
    if (file_name.isEmpty())
    {
        // todo 弹出错误提出

        return;
    }

    file_name_ = file_name;

    if (ui.openGLWidget->mesh_ != nullptr)
    {
        delete ui.openGLWidget->mesh_;
        ui.openGLWidget->mesh_ = nullptr;
    }

    qDebug() << "open file: " << file_name;
    ui.openGLWidget->mesh_ = new TriMesh;
    ui.openGLWidget->mesh_->loadFile(file_name.toStdString());
    ui.openGLWidget->change_mesh_ = true;
    ui.openGLWidget->update();
}

void MainWindow::slot_reload()
{
    if (file_name_.isEmpty())
    {
        // todo 弹出错误提出

        return;
    }

    if (ui.openGLWidget->mesh_ != nullptr)
    {
        delete ui.openGLWidget->mesh_;
        ui.openGLWidget->mesh_ = nullptr;
    }

    qDebug() << "reload file: " << file_name_;
    ui.openGLWidget->mesh_ = new TriMesh;
    ui.openGLWidget->mesh_->loadFile(file_name_.toStdString());
    ui.openGLWidget->change_mesh_ = true;
    ui.openGLWidget->update();
}

void MainWindow::slot_simplify()
{
    TriMesh* triMesh = (TriMesh*)ui.openGLWidget->mesh_;
    simplify(triMesh, file_name_.toStdString(),triMesh->num_vtx_ * 0.5f);
    triMesh->InitBO();
    ui.openGLWidget->update();
}