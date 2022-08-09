#pragma once
#include <map>
#include "MeshLoaderData.h"

class MeshGenerator
{
public:
	enum Shape
	{
		Tetrahedron,
		Icosahedron,
		IcoSpehre
	};

	static MeshLoaderData* GenerateShape(Shape shape);
	static MeshLoaderData* GenerateIcosahedron();
	static MeshLoaderData* GenerateIcoSpehre(int subdivisions);
	static void SubdivideMesh(MeshLoaderData* pMeshLoaderData);

private:
	static std::map<unsigned int, int> newVertices;

	static USHORT GetNewVertex(MeshLoaderData* pMeshLoaderData, USHORT i1, USHORT i2);
};

