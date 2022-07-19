#include "MeshLoader.h"

MeshData* MeshLoader::LoadFromFile(string fileName)
{
    data = new MeshData;
    string path = "Models/" + fileName;
    string token;

    ifstream filestream(path);
    while (getline(filestream, token))
    {
        ParseLine(token);
    }

    return nullptr;
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

}

void MeshLoader::ParseTexturePath(string line)
{
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
    //TODO test
    string prefix, face1, face2, face3, face4;

    istringstream s(line);
    s >> prefix >> face1 >> face2 >> face3 >> face4;

    ParseIndices(face1);
    ParseIndices(face2);
    ParseIndices(face3);
    if (face4 == "")
    {
        ParseIndices(face1);
        ParseIndices(face3);
        ParseIndices(face4);
    }

    //build here
}

void MeshLoader::ParseIndices(string line)
{
    string token;
    istringstream s(line);

    getline(s, token, '/');
    data->vertexIndices->push_back(atoi(token.c_str()));

    getline(s, token, '/');
    data->uvIndices->push_back(atoi(token.c_str()));

    getline(s, token, '/');
    data->normalIndices->push_back(atoi(token.c_str()));
    
}
