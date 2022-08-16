#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <string>
#include "Vertex.h"

using namespace DirectX;

class MeshLoaderData
{
public:
	std::vector<Vertex>* vertices = {};
	std::vector<USHORT>* indices = {};

	std::vector<XMFLOAT3>* vertexPosition = {};
	std::vector<XMFLOAT3>* vertexNormals = {};
	std::vector<XMFLOAT2>* textureCoordinates = {};

	std::vector<USHORT>* vertexIndices = {};
	std::vector<USHORT>* normalIndices = {};
	std::vector<USHORT>* uvIndices = {};

	std::string materialFileName = {};

	BOOL usesQuads = false;

	void Init();
	void DeInit();
};

