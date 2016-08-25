#pragma once
#include <iostream>
#include "misc.h"
#include "Entity.h"
#include <cmath>
#include <vector>

struct PathNode
{
	bool valid;
	int h;
	int g;
	int f;
	bool onOpen;
	bool onClosed;
	int x, y;
	PathNode* parent;
	bool keyNode;
};

class PathFinder
{
private:
	PathNode** pathMesh;
	unsigned int width, height;
	const unsigned int GRID_SIZE = 25;
	const unsigned int DIAGONAL_COST = 10;
	const unsigned int NORMAL_COST = 10;
	bool pathFound;
	std::vector<Entity*> objects;
	std::vector<PathNode*> open;
	std::vector<PathNode*> closed;
	void calculateH(const sf::Vector2i end);
	sf::Vector2i getPathMeshCoordinates(sf::Vector2f pos);
	std::vector<PathNode*> calculateNodes(sf::Vector2i index);
	void removeFromList(PathNode* node, std::vector<PathNode*> list);

public:
	void addObject(Entity& object);
	void setPathMesh(unsigned int _width, unsigned  int _height);
	std::vector<sf::Vector2f> findPath(const sf::Vector2f start,const sf::Vector2f end);
	PathFinder();
	~PathFinder();
	std::vector<sf::RectangleShape> getGrid();
};

