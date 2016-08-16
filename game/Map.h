#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "EditorObject.h"
#include "misc.h"
#include "TextureManager.h"

class Map
{
private:
	std::vector<EditorObject*> objects;
public:
	Map();
	~Map();
	void generateFile(std::string _filename, EditorObject* objects, unsigned int n_objects);
	std::vector<EditorObject*> loadFile(std::string _filename, std::vector<Texture*> textures);
};

