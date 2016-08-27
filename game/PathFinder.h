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
	int move_cost;
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
	const unsigned int DIAGONAL_COST = 14;
	const unsigned int NORMAL_COST = 10;
	std::vector<Entity*> objects;
	std::vector<PathNode*> open;
	std::vector<PathNode*> closed;
	sf::Vector2i getPathMeshCoordinates(sf::Vector2f pos);
	PathNode* calculateNodes(sf::Vector2i index);
	int distance(PathNode* a, PathNode* b);
	PathNode* goalNode, *startNode;

public:
	void addObject(Entity& object);
	void setPathMesh(unsigned int _width, unsigned  int _height);
	std::vector<sf::Vector2f> findPath(const sf::Vector2f start,const sf::Vector2f end);
	PathFinder();
	~PathFinder();
	std::vector<sf::RectangleShape> getGrid();
	void clearNodes();
};

