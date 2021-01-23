#pragma once

#include "Tri.h"
#include "Vec.h"
#include <vector>
#include <string>
#include "Mesh.h"

class TriMesh : public Mesh
{
public:
	TriMesh();
	~TriMesh();

	virtual void loadFile(std::string file_name) override;
	virtual void setMesh() override;
	virtual void drawMesh(QOpenGLFunctions_3_3_Core* ff, QMatrix4x4 &projection, QMatrix4x4 &model) override;
	virtual void destroyGL() override;
	virtual bool isEmpty() override;
	void shader();
	void InitBO();

	int num_vtx_{ 0 };	// 顶点数量
	int num_tri_{ 0 };	// 面片数量

	std::vector<Vec3f> vtxs_; 
	std::vector<Tri> tris_;

	QOpenGLBuffer vbo_, ebo_;
	QOpenGLVertexArrayObject vao_;

	QOpenGLShaderProgram shader_program_;

	REAL scale_factor_{ 1 };
	QVector3D translate_;
};

