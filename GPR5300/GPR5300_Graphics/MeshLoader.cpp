#include "MeshLoader.h"

MeshLoaderData* MeshLoader::data = nullptr;
USHORT MeshLoader::currentIndex = 0;

MeshLoaderData* MeshLoader::LoadFromFile(string fileName)
{
	currentIndex = 0;
	data = new MeshLoaderData;
	data->Init();

	string path = "Models/Objects/" + fileName + ".obj";
	string token;

	ifstream filestream(path);
	while (getline(filestream, token))
		ParseLine(token);

	BuildVertices();
	CalculateTangentAndBiNormal();

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
}

void MeshLoader::BuildVertices()
{
	for (USHORT i = 0; i < data->vertexIndices->size(); i++)
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

void MeshLoader::CalculateTangentAndBiNormal()
{
	for (int i = 0; i < data->vertices->size(); i += 3)
	{
		float position1[3], position2[3];
		float tuVector[2], tvVector[2];
		float den, length;

		XMFLOAT3 tangent, bitangent;

		position1[0] = data->vertices->at(i + 1).pos.x - data->vertices->at(i).pos.x;
		position1[1] = data->vertices->at(i + 1).pos.y - data->vertices->at(i).pos.y;
		position1[2] = data->vertices->at(i + 1).pos.z - data->vertices->at(i).pos.z;

		position2[0] = data->vertices->at(i + 2).pos.x - data->vertices->at(i).pos.x;
		position2[1] = data->vertices->at(i + 2).pos.y - data->vertices->at(i).pos.y;
		position2[2] = data->vertices->at(i + 2).pos.z - data->vertices->at(i).pos.z;

		tuVector[0] = data->vertices->at(i + 1).uv.x - data->vertices->at(i).uv.x;
		tvVector[0] = data->vertices->at(i + 1).uv.y - data->vertices->at(i).uv.y;

		tuVector[1] = data->vertices->at(i + 2).uv.x - data->vertices->at(i).uv.x;
		tvVector[1] = data->vertices->at(i + 2).uv.y - data->vertices->at(i).uv.y;

		den = 1.0f / (tuVector[0] * tvVector[1] - tuVector[1] * tvVector[0]);

		tangent.x = (tvVector[1] * position1[0] - tvVector[0] * position2[0]) * den;
		tangent.y = (tvVector[1] * position1[1] - tvVector[0] * position2[1]) * den;
		tangent.z = (tvVector[1] * position1[2] - tvVector[0] * position2[2]) * den;

		bitangent.x = (tuVector[0] * position2[0] - tuVector[1] * position1[0]) * den;
		bitangent.y = (tuVector[0] * position2[1] - tuVector[1] * position1[1]) * den;
		bitangent.z = (tuVector[0] * position2[2] - tuVector[1] * position1[2]) * den;

		length = sqrt((tangent.x * tangent.x) + (tangent.y * tangent.y) + (tangent.z * tangent.z));

		tangent.x /= length;
		tangent.y /= length;
		tangent.z /= length;

		length = sqrt((bitangent.x * bitangent.x) + (bitangent.y * bitangent.y) + (bitangent.z * bitangent.z));

		bitangent.x = bitangent.x / length;
		bitangent.y = bitangent.y / length;
		bitangent.z = bitangent.z / length;

		data->vertices->at(i).tangent = tangent;
		data->vertices->at(i + 1).tangent = tangent;
		data->vertices->at(i + 2).tangent = tangent;

		data->vertices->at(i).binormal = bitangent;
		data->vertices->at(i + 1).binormal = bitangent;
		data->vertices->at(i + 2).binormal = bitangent;
	}
}
