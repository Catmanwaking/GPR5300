#include "MaterialLoader.h"

MaterialLoaderData* MaterialLoader::data = nullptr;

MaterialLoaderData* MaterialLoader::LoadFromFile(string fileName)
{
    data = new MaterialLoaderData;
    string path = "Models/Materials/" + fileName;
    string token;

    ifstream filestream(path);
    while (getline(filestream, token))
    {
        ParseLine(token);
    }

    return data;
}

void MaterialLoader::ParseLine(string line)
{
    if (line.substr(0, 2) == "Ka") ParseAmbient(line);
    else if (line.substr(0, 2) == "Kd") ParseDiffuse(line);
    else if (line.substr(0, 2) == "Ks") ParseSpecular(line);
    else if (line.substr(0, 2) == "Ke") ParseEmissive(line);
    else if (line.substr(0, 2) == "Ns") ParseSpecularExponent(line);
    else if (line.substr(0, 2) == "d ") ParseDissolve(line);
    else if (line.substr(0, 6) == "map_Kd") ParseTexture(line);
    else if (line.substr(0, 4) == "norm") ParseNormalMap(line);
}

void MaterialLoader::ParseAmbient(string line)
{
    string prefix;
    float r, g, b;

    istringstream s(line);
    s >> prefix >> r >> g >> b;

    data->ambient = { r, g, b, 1.0f };
}

void MaterialLoader::ParseDiffuse(string line)
{
    string prefix;
    float r, g, b;

    istringstream s(line);
    s >> prefix >> r >> g >> b;

    data->diffuse = { r, g, b, 1.0f };
}

void MaterialLoader::ParseSpecular(string line)
{
    string prefix;
    float r, g, b;

    istringstream s(line);
    s >> prefix >> r >> g >> b;

    data->specular = { r, g, b, 1.0f };
}

void MaterialLoader::ParseEmissive(string line)
{
    string prefix;
    float r, g, b;

    istringstream s(line);
    s >> prefix >> r >> g >> b;

    data->emissive = { r, g, b, 1.0f };
}

void MaterialLoader::ParseSpecularExponent(string line)
{
    string prefix;
    float e;

    istringstream s(line);
    s >> prefix >> e;

    data->specularPower = FLOAT(e);
}

void MaterialLoader::ParseDissolve(string line)
{
    string prefix;
    float d;

    istringstream s(line);
    s >> prefix >> d;

    data->dissolve = d;
}

void MaterialLoader::ParseTexture(string line)
{
    string prefix, textureName;
    istringstream s(line);
    s >> prefix >> textureName;

    textureName = "Models/Images/" + textureName;

    data->textureFileName = wstring(textureName.begin(), textureName.end());
}

void MaterialLoader::ParseNormalMap(string line)
{
    string prefix, textureName;
    istringstream s(line);
    s >> prefix >> textureName;

    textureName = "Models/Images/" + textureName;

    data->normalMapFileName = wstring(textureName.begin(), textureName.end());
}
