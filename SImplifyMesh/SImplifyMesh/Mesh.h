#pragma once
#include <string>
#include <QDebug>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShader>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <limits.h>
#include <algorithm>

class Mesh
{
public:
	virtual void loadFile(std::string file_name) = 0;
	virtual void setMesh() = 0;
	virtual void drawMesh(QOpenGLFunctions_3_3_Core* ff, QMatrix4x4& projection, QMatrix4x4& model) = 0;
	virtual void destroyGL() = 0;
	virtual bool isEmpty() = 0;
};