#pragma once
#include <d3d9.h>
#include <DirectXMath.h>
#include <vector>
#include <string>
#include "Vertex.h"

using namespace DirectX;

class MeshData
{
public:
	int vertexCount;
	int indexCount;

	std::vector<Vertex>* vertices;

	std::vector<XMFLOAT3>* vertexPosition;
	std::vector<XMFLOAT3>* vertexNormals;
	std::vector<XMFLOAT2>* textureCoordinates;

	std::vector<USHORT>* vertexIndices;
	std::vector<USHORT>* normalIndices;
	std::vector<USHORT>* uvIndices;

	std::string textureFileName;

	void Init();
	void DeInit();
};
