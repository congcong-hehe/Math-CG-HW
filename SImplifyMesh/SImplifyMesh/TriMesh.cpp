#include "TriMesh.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <QOpenGLWidget>

TriMesh::TriMesh(): vbo_(QOpenGLBuffer::VertexBuffer),
ebo_(QOpenGLBuffer::IndexBuffer)
{

}

TriMesh::~TriMesh()
{

}

void TriMesh::loadFile(std::string file_name)
{
	std::ifstream in(file_name);

	if (!in)
	{
		std::cout << "The file can not be opened!" << std::endl;
		return;
	}
	
	REAL x_min = FLT_MAX, x_max = FLT_MIN;
	REAL y_min = FLT_MAX, y_max = FLT_MIN;
	REAL z_min = FLT_MAX, z_max = FLT_MIN;

	std::string line;
	while (std::getline(in, line))
	{
		std::string tag;
		std::istringstream is(line);
		
		is >> tag;
		if (tag == "v")
		{
			Vec3f vec3f;
			is >> vec3f.x >> vec3f.y >> vec3f.z;

			// 计算包围盒
			x_min = fmin(x_min, vec3f.x);
			x_max = fmax(x_max, vec3f.x);
			y_min = fmin(y_min, vec3f.y);
			y_max = fmax(y_max, vec3f.y);
			z_min = fmin(z_min, vec3f.z);
			z_max = fmax(z_max, vec3f.z);

			vtxs_.push_back(vec3f);
		}
		else if (tag == "f")
		{
			Tri tri;
			is >> tri.v[0] >> tri.v[1] >> tri.v[2];
			tri.v[0] --;
			tri.v[1] --;
			tri.v[2] --;
			tris_.push_back(tri);
		}
	}
	in.close();

	num_vtx_ = vtxs_.size();
	num_tri_ = tris_.size();

	// 计算模型的缩放比例，保证模型的大小在窗口中合适的显示
	scale_factor_ = fmax(fmax((x_max - x_min), (y_max - y_min)), (z_max - z_min));
	// 将模型的中点平移到原点位置的平移量
	translate_ = QVector3D(-(x_max + x_min) / 2.0f, -(y_max + y_min) / 2.0f, -(y_max + y_min) / 2.0f);
}

void TriMesh::shader()
{
	//  顶点着色器
	bool success = shader_program_.addShaderFromSourceFile(QOpenGLShader::Vertex, "GLSL/vert.glsl");
	if (!success)
	{
		qDebug() << "shaderProgram addShaderFromSourceFile failed!" << shader_program_.log();
		return;
	}

	// 片段着色器
	success = shader_program_.addShaderFromSourceFile(QOpenGLShader::Fragment, "GLSL/frag.glsl");
	if (!success)
	{
		qDebug() << "shaderProgram addShaderFromSourceFile failed!" << shader_program_.log();
		return;
	}

	// 链接着色器
	success = shader_program_.link();
	if (!success)
	{
		qDebug() << "shaderProgram link failed!" << shader_program_.log();
		return;
	}
}

void TriMesh::InitBO()
{
	//vao_.create();
	//QOpenGLVertexArrayObject::Binder vaoBind(&vao_);
	//vao_.bind();

	// 创建并分配vbo对象
	vbo_.create();
	vbo_.bind();
	vbo_.allocate(&vtxs_[0], vtxs_.size() * sizeof(Vec3f));

	// 创建并分配ebo对象
	ebo_.create();
	ebo_.bind();
	ebo_.allocate(&tris_[0], tris_.size() * sizeof(Tri));

	int attr = -1;
	attr = shader_program_.attributeLocation("aPos");
	shader_program_.setAttributeBuffer(attr, GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);	// 设置解析数据的方式
	shader_program_.enableAttributeArray(attr);

	vbo_.release();

	shader_program_.bind();
	// 视图view变换矩阵
	QMatrix4x4 view;
	view.lookAt(QVector3D(0.0f, 0.0f, 4.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
	shader_program_.setUniformValue("view", view);
}

void TriMesh::setMesh()
{
	shader();
	InitBO();
}

void TriMesh::drawMesh(QOpenGLFunctions_3_3_Core* ff, QMatrix4x4 &projection, QMatrix4x4 &model)
{
	model.translate(translate_);		// 平移模型到原点
	model.scale(1.0f / scale_factor_ * 2.0f);
	shader_program_.bind();
	shader_program_.setUniformValue("projection", projection);
	shader_program_.setUniformValue("model", model);

	//QOpenGLVertexArrayObject::Binder vaoBind(&vao_);
	//vao_.bind();

	ff->glDrawElements(GL_TRIANGLES, tris_.size() * 3, GL_UNSIGNED_INT, 0);		// 绘制

	shader_program_.release();
}

void TriMesh::destroyGL()
{
	vao_.destroy();
	vbo_.destroy();
	ebo_.destroy();
}

bool TriMesh::isEmpty()
{
	return num_vtx_ == 0;
}
