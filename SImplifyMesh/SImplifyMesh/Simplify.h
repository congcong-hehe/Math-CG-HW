#pragma once

#include "TriMesh.h"
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Decimater/DecimaterT.hh>
#include <OpenMesh/Tools/Decimater/ModQuadricT.hh>
#include <string>
#include "Vec.h"

using MyMesh = OpenMesh::TriMesh_ArrayKernelT<>;
using MyDecimater = OpenMesh::Decimater::DecimaterT<MyMesh>;
using MyHModQuadric = OpenMesh::Decimater::ModQuadricT<MyMesh>::Handle;

void simplify(TriMesh *triMesh, std::string file_name, int target)
{
	MyMesh mesh;

	if (!OpenMesh::IO::read_mesh(mesh, file_name))
	{
		std::cerr << "read error\n";
		exit(1);
	}

	MyDecimater decimater(mesh);
	MyHModQuadric hModQuadric;

	decimater.add(hModQuadric);
	std::cout << decimater.module(hModQuadric).name() << std::endl;

	decimater.module(hModQuadric).unset_max_err();

	decimater.initialize();
	decimater.decimate_to(target);

	mesh.garbage_collection();

	triMesh->vtxs_.clear();
	triMesh->tris_.clear();
	
	for (MyMesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it)
	{
		float* data = mesh.point(*v_it).data();
		triMesh->vtxs_.push_back(Vec3f(data[0], data[1], data[2]));
	}

	for (MyMesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it)
	{
		MyMesh::FaceVertexIter fv_it = mesh.fv_iter(*f_it);
		int t1 = fv_it->idx();
		fv_it++;
		int t2 = fv_it->idx();
		fv_it++;
		int t3 = fv_it->idx();

		triMesh->tris_.push_back(Tri(t1, t2, t3));
	}

	triMesh->num_tri_ = triMesh->tris_.size();
	triMesh->num_vtx_ = triMesh->vtxs_.size();
}
