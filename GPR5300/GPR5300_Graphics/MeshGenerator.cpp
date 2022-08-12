#include "MeshGenerator.h"
#include "Vector3.h"
#include "Math.h"

using namespace Constants;

std::map<unsigned int, int> MeshGenerator::newVertices = {};

MeshLoaderData* MeshGenerator::GenerateShape(Shape shape)
{
    switch (shape)
    {
    case Tetrahedron:
        return nullptr;
    case Icosahedron:
        return GenerateIcosahedron();
    case IcoSpehre:
        return GenerateIcoSpehre(3);
    default:
        return nullptr;
    }
}

MeshLoaderData* MeshGenerator::GenerateIcosahedron()
{
    MeshLoaderData* pData = new MeshLoaderData;
    pData->Init();

    float a = 1.0f;
    float b = 1.0f / goldenRatio;

    pData->vertices->push_back(Vertex(0, b, -a));
    pData->vertices->push_back(Vertex(b, a, 0));
    pData->vertices->push_back(Vertex(-b, a, 0));
    pData->vertices->push_back(Vertex(0, b, a));
    pData->vertices->push_back(Vertex(0, -b, a));
    pData->vertices->push_back(Vertex(-a, 0, b));
    pData->vertices->push_back(Vertex(0, -b, -a));
    pData->vertices->push_back(Vertex(a, 0, -b));
    pData->vertices->push_back(Vertex(a, 0, b));
    pData->vertices->push_back(Vertex(-a, 0, -b));
    pData->vertices->push_back(Vertex(b, -a, 0));
    pData->vertices->push_back(Vertex(-b, -a, 0));

    pData->indices->push_back( 2); pData->indices->push_back( 1); pData->indices->push_back( 0);
    pData->indices->push_back( 1); pData->indices->push_back( 2); pData->indices->push_back( 3);
    pData->indices->push_back( 5); pData->indices->push_back( 4); pData->indices->push_back( 3);
    pData->indices->push_back( 4); pData->indices->push_back( 8); pData->indices->push_back( 3);
    pData->indices->push_back( 7); pData->indices->push_back( 6); pData->indices->push_back( 0);
    pData->indices->push_back( 6); pData->indices->push_back( 9); pData->indices->push_back( 0);
    pData->indices->push_back(11); pData->indices->push_back(10); pData->indices->push_back( 4);
    pData->indices->push_back(10); pData->indices->push_back(11); pData->indices->push_back( 6);
    pData->indices->push_back( 9); pData->indices->push_back( 5); pData->indices->push_back( 2);
    pData->indices->push_back( 5); pData->indices->push_back( 9); pData->indices->push_back(11);
    pData->indices->push_back( 8); pData->indices->push_back( 7); pData->indices->push_back( 1);
    pData->indices->push_back( 7); pData->indices->push_back( 8); pData->indices->push_back(10);
    pData->indices->push_back( 2); pData->indices->push_back( 5); pData->indices->push_back( 3);
    pData->indices->push_back( 8); pData->indices->push_back( 1); pData->indices->push_back( 3);
    pData->indices->push_back( 9); pData->indices->push_back( 2); pData->indices->push_back( 0);
    pData->indices->push_back( 1); pData->indices->push_back( 7); pData->indices->push_back( 0);
    pData->indices->push_back(11); pData->indices->push_back( 9); pData->indices->push_back( 6);
    pData->indices->push_back( 7); pData->indices->push_back(10); pData->indices->push_back( 6);
    pData->indices->push_back( 5); pData->indices->push_back(11); pData->indices->push_back( 4);
    pData->indices->push_back(10); pData->indices->push_back( 8); pData->indices->push_back( 4);

    return pData;
}

MeshLoaderData* MeshGenerator::GenerateIcoSpehre(int subdivisions)
{
    MeshLoaderData* pMeshData = GenerateIcosahedron();
    for (int i = 0; i < subdivisions; i++)
        SubdivideMesh(pMeshData);
    int vCount = pMeshData->vertices->size();
    for (int i = 0; i < vCount; i++)
    {
        Vector3 toNormalize = Vector3(pMeshData->vertices->at(i).pos);
        toNormalize.Normalize();
        pMeshData->vertices->at(i).pos = toNormalize.ToXMFloat3();
        pMeshData->vertices->at(i).normal = toNormalize.ToXMFloat3();
    }
    return pMeshData;
}

void MeshGenerator::SubdivideMesh(MeshLoaderData* pMeshLoaderData)
{
    newVertices = std::map<unsigned int, int>();

    std::vector<USHORT>* indices = new std::vector<USHORT>;

    int indexCount = pMeshLoaderData->indices->size();
    for (int i = 0; i < indexCount; i += 3)
    {
        USHORT i1 = pMeshLoaderData->indices->at(i + 0);
        USHORT i2 = pMeshLoaderData->indices->at(i + 1);
        USHORT i3 = pMeshLoaderData->indices->at(i + 2);

        USHORT a = GetNewVertex(pMeshLoaderData, i1, i2);
        USHORT b = GetNewVertex(pMeshLoaderData, i2, i3);
        USHORT c = GetNewVertex(pMeshLoaderData, i3, i1);
        indices->push_back(i1); indices->push_back(a); indices->push_back(c);
        indices->push_back(i2); indices->push_back(b); indices->push_back(a);
        indices->push_back(i3); indices->push_back(c); indices->push_back(b);
        indices->push_back(a); indices->push_back(b); indices->push_back(c);
    }

    pMeshLoaderData->indices = indices;
}

USHORT MeshGenerator::GetNewVertex(MeshLoaderData* pMeshLoaderData, USHORT i1, USHORT i2)
{
    if (i1 < i2)
    {
        USHORT foo = i1;
        i1 = i2;
        i2 = foo;
    }

    unsigned int key = ((unsigned int)i1 << 16 | (unsigned int)i2);
    if (newVertices.find(key) != newVertices.end())
        return newVertices[key];

    USHORT newIndex = pMeshLoaderData->vertices->size();
    newVertices[key] = newIndex;

    Vertex newVertex = {};
    newVertex.pos.x = (pMeshLoaderData->vertices->at(i1).pos.x + pMeshLoaderData->vertices->at(i2).pos.x) * 0.5f;
    newVertex.pos.y = (pMeshLoaderData->vertices->at(i1).pos.y + pMeshLoaderData->vertices->at(i2).pos.y) * 0.5f;
    newVertex.pos.z = (pMeshLoaderData->vertices->at(i1).pos.z + pMeshLoaderData->vertices->at(i2).pos.z) * 0.5f;
    pMeshLoaderData->vertices->push_back(newVertex);
    return newIndex;
}
