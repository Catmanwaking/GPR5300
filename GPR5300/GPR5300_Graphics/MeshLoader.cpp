#include "MeshLoader.h"

MeshData* MeshLoader::data = nullptr;
USHORT MeshLoader::currentIndex = 0;

MeshData* MeshLoader::LoadFromFile(string fileName)
{
	currentIndex = 0;
	data = new MeshData;
	data->Init();

	string path = "Models/Objects/" + fileName + ".obj";
	string token;

	ifstream filestream(path);
	while (getline(filestream, token))
		ParseLine(token);

	BuildVertices();

	return data;
}

void MeshLoader::ParseLine(string line)
{
	if (line.substr(0, 2) == "v ") ParseVertexPosition(line);
	else if (line.substr(0, 2) == "vt") ParseTextureCoordinate(line);
	else if (line.substr(0, 2) == "vn") ParseVertexNormal(line);
	else if (line.substr(0, 2) == "f ") ParseFace(line);
	else if (line.substr(0, 6) == "mtllib") ParseMaterial(line);
}

void MeshLoader::ParseMaterial(string line)
{
	string prefix, materialName;
	istringstream s(line);
	s >> prefix >> materialName;

	data->materialFileName = materialName;
}

void MeshLoader::ParseVertexPosition(string line)
{
	string prefix;
	float x, y, z;

	istringstream s(line);
	s >> prefix >> x >> y >> z;

	data->vertexPosition->push_back(XMFLOAT3(x, y, z));
}

void MeshLoader::ParseTextureCoordinate(string line)
{
	string prefix;
	float u, v;

	istringstream s(line);
	s >> prefix >> u >> v;

	data->textureCoordinates->push_back(XMFLOAT2(u, v));
}

void MeshLoader::ParseVertexNormal(string line)
{
	string prefix;
	float nx, ny, nz;

	istringstream s(line);
	s >> prefix >> nx >> ny >> nz;

	data->vertexNormals->push_back(XMFLOAT3(nx, ny, nz));
}

void MeshLoader::ParseFace(string line)
{
	//TODO test with tri
	string prefix, face1, face2, face3, face4;

	istringstream s(line);
	s >> prefix >> face1 >> face2 >> face3 >> face4;

	ParseIndices(face1);
	ParseIndices(face2);
	ParseIndices(face3);
	if (face4 != "")
	{
		data->indices->push_back(currentIndex - 3);
		data->indices->push_back(currentIndex - 1);
		ParseIndices(face4);
		data->indexCount += 2;
	}
}

void MeshLoader::ParseIndices(string line)
{
	string token;
	istringstream s(line);

	getline(s, token, '/');
	data->vertexIndices->push_back(atoi(token.c_str()) - 1);

	getline(s, token, '/');
	data->uvIndices->push_back(atoi(token.c_str()) - 1);

	getline(s, token, '/');
	data->normalIndices->push_back(atoi(token.c_str()) - 1);

	data->indices->push_back(currentIndex++);
	data->indexCount++;
	data->vertexCount++;
}

void MeshLoader::BuildVertices()
{
	for (USHORT i = 0; i < data->vertexCount; i++)
	{
		USHORT posIndex = data->vertexIndices->at(i);
		USHORT normalIndex = data->vertexNormals->empty() ? USHRT_MAX : data->normalIndices->at(i);
		USHORT uvIndex = data->textureCoordinates->empty() ? USHRT_MAX : data->uvIndices->at(i);

		data->vertices->push_back
		(
			Vertex
			(
				data->vertexPosition->at(posIndex),
				normalIndex == USHRT_MAX ? XMFLOAT3() : data->vertexNormals->at(normalIndex),
				uvIndex == USHRT_MAX ? XMFLOAT2() : data->textureCoordinates->at(uvIndex)
			)
		);
	}
}