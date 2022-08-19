#pragma once
#include <map>
#include "Shapes.h"
#include "MeshLoaderData.h"

class MeshGenerator
{
public:
	//Generates the specified Shape.
	static MeshLoaderData* GenerateShape(Shape shape);
	//Generates an icosahedron.
	static MeshLoaderData* GenerateIcosahedron();
	//Generates an icosahedron and divides it into smaller triangles to form a sphere.
	static MeshLoaderData* GenerateIcoSpehre(int subdivisions);
	//Divides each triangle in the MeshLoaderData into 4 triangles.
	static void SubdivideMesh(MeshLoaderData* pMeshLoaderData);

private:
	//Returns an existing vertexindex or generates a new vertex
	static USHORT GetNewVertex(MeshLoaderData* pMeshLoaderData, USHORT i1, USHORT i2);
	static std::map<unsigned int, int> newVertices;
};

