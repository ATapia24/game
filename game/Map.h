#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "misc.h"
#include "EditorObject.h"
#include "Entity.h"
#include "misc.h"
#include "Solid.h"
#include "TextureManager.h"
#include "Box2D/Box2D.h"
#include "WindowMgr.h"

class Map
{
private:
	WindowMgr* window;
	b2World* world;
	std::vector<Entity*> objects;
public:
	Map();
	~Map();
	void generateFile(std::string _filename, EditorObject* objects, unsigned int n_objects);
	std::vector<Entity*> loadFile(std::string _filename, std::vector<Texture*> textures, WindowMgr* _window, b2World* _world);
};

