#pragma once
#include <iostream>
#include "misc.h"
#include "Entity.h"
#include <vector>

struct PathNode
{
	bool valid;
	int h;
	int g;
	int f;
	PathNode* parent;
};

class PathFinder
{
private:
	PathNode** PathMesh;
	unsigned int width, height;
	const unsigned int GRID_SIZE = 25;
	std::vector<Entity*> objects;
	std::vector<PathNode*> open;
	std::vector<PathNode*> closed;
public:
	void addObject(Entity& object);
	void setPathMesh(unsigned int _width, unsigned  int _height);
	PathFinder();
	~PathFinder();
	sf::VertexArray getGrid();
};

