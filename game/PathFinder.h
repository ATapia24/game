#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <iostream>
#include "misc.h"
#include "Entity.h"
#include <cmath>
#include <vector>

#include "Timer.h"

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
	int openIndex;
};

class PathFinder
{
private:
	PathNode** pathMesh;
	unsigned int width, height;
	const unsigned int GRID_SIZE = 25, DIAGONAL_COST = 14, NORMAL_COST = 10;
	std::vector<Entity*> objects;
	std::vector<PathNode*> open, closed;
	PathNode* calculateNodes(sf::Vector2i index);
	PathNode* goalNode, *startNode;
	bool invalidGoalNode;
	int distance(PathNode* a, PathNode* b);
	sf::Vector2i getIndex(sf::Vector2f pos);
	std::vector<PathNode*> getSides(PathNode* current);
	Timer t;
public:
	void addObject(Entity& object);
	void setPathMesh(unsigned int _width, unsigned  int _height);
	std::vector<sf::Vector2f> findPath(const sf::Vector2f start,const sf::Vector2f end);
	PathFinder();
	~PathFinder();
	std::vector<sf::RectangleShape> getGrid();
	void clearNodes();
};

#endif