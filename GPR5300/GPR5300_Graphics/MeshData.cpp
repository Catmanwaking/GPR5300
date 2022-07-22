#include "MeshData.h"
#include "Utils.h"

void MeshData::Init()
{
	vertices = new std::vector<Vertex>;
	indices = new std::vector<USHORT>;

	vertexPosition = new std::vector<XMFLOAT3>;
	vertexNormals = new std::vector<XMFLOAT3>;
	textureCoordinates = new std::vector<XMFLOAT2>;

	vertexIndices = new std::vector<USHORT>;
	normalIndices = new std::vector<USHORT>;
	uvIndices = new std::vector<USHORT>;
}

void MeshData::DeInit()
{
	SafeClearAndDelete<std::vector<Vertex>>(vertices);
	SafeClearAndDelete<std::vector<USHORT>>(indices);

	SafeClearAndDelete<std::vector<XMFLOAT3>>(vertexPosition);
	SafeClearAndDelete<std::vector<XMFLOAT3>>(vertexNormals);
	SafeClearAndDelete<std::vector<XMFLOAT2>>(textureCoordinates);

	SafeClearAndDelete<std::vector<USHORT>>(vertexIndices);
	SafeClearAndDelete<std::vector<USHORT>>(normalIndices);
	SafeClearAndDelete<std::vector<USHORT>>(uvIndices);
}
