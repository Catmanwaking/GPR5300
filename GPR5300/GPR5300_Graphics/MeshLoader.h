#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "MeshLoaderData.h"

using namespace std;

class MeshLoader
{
public:
	static MeshLoaderData* LoadFromFile(string fileName);

private:
	static void ParseLine(string line);
	static void ParseMaterial(string line);
	static void ParseVertexPosition(string line);
	static void ParseTextureCoordinate(string line);
	static void ParseVertexNormal(string line);
	static void ParseFace(string line);
	static void ParseIndices(string line);

	static void BuildVertices();
	static void CalculateTangentAndBiNormal();

	static USHORT currentIndex;
	static MeshLoaderData* data;
};

