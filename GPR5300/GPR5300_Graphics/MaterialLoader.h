#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "MaterialLoaderData.h"

using namespace std;

class MaterialLoader
{
public:
	static MaterialLoaderData* LoadFromFile(string fileName);

private:
	static void ParseLine(string line);
	static void ParseAmbient(string line);
	static void ParseDiffuse(string line);
	static void ParseSpecular(string line);
	static void ParseEmissive(string line);
	static void ParseSpecularExponent(string line);
	static void ParseDissolve(string line);
	static void ParseTexture(string line);
	static void ParseNormalMap(string line);

	static MaterialLoaderData* data;
};

