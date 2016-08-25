#include "stdafx.h"
#include "PathFinder.h"


//CONSTRUCTOR
PathFinder::PathFinder()
{
}

//DECONSTRUCTOR
PathFinder::~PathFinder()
{
}

//ADD OBJECT
void PathFinder::addObject(Entity& object)
{
	if (object.getType() == EntityType::SOLID)
		objects.push_back(&object);
}

//SET PATH MESH
void PathFinder::setPathMesh(unsigned int _width, unsigned  int _height)
{
	//size
	width = _width;
	height = _height;

	//create path mesh
	pathMesh = new PathNode*[width];
	for (int w = 0; w < width; w++)
		pathMesh[w] = new PathNode[height];

	//set all to valid
	for (int w = 0; w < width; w++)
		for (int h = 0; h < height; h++)
		{
			pathMesh[w][h].valid = 1;
			pathMesh[w][h].g = 0;
			pathMesh[w][h].onOpen = 0;
			pathMesh[w][h].onClosed = 0;
			pathMesh[w][h].keyNode = 0;

			pathMesh[w][h].x = w;
			pathMesh[w][h].y = h;
		}

	//set all grid nodes with objects invalid
	for (int i = 0; i < objects.size(); i++)
	{
		std::vector<sf::Vector2f> points = misc::getAreaPoints(objects[i]->getHitbox(), GRID_SIZE / 12, 1);

		for (int p = 0; p < points.size(); p++)
		{
			sf::Vector2i pos = getPathMeshCoordinates(points[p]);

			if (pos.x >= 0 && pos.y >= 0 && pos.x < width - 1 && pos.y < height - 1)
				pathMesh[pos.x][pos.y].valid = 0;
		}
	}
}

//CALCULATE H
void PathFinder::calculateH(const sf::Vector2i end)
{
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			pathMesh[x][y].h = (std::abs(end.x - x) + std::abs(end.y - y));
}

//GET PATH MESH COORDINATES
sf::Vector2i PathFinder::getPathMeshCoordinates(sf::Vector2f pos)
{
	return sf::Vector2i(pos.x / GRID_SIZE, pos.y / GRID_SIZE);
}

//FIND PATH
std::vector<sf::Vector2f> PathFinder::findPath(const sf::Vector2f start, const sf::Vector2f end)
{
	sf::Vector2i goalCoords = getPathMeshCoordinates(end);
	sf::Vector2i startCoords = getPathMeshCoordinates(start);
	PathNode* currentNode = calculateNodes(startCoords)[0];
	PathNode* startNode = &pathMesh[startCoords.x][startCoords.y];
	PathNode* goalNode = &pathMesh[goalCoords.x][goalCoords.y];
	
	//start setup
	pathFound = 1;
	calculateH(goalCoords);
	closed.push_back(currentNode);
	currentNode->onClosed = 1;

	do {
		std::vector<PathNode*> nodes = calculateNodes(sf::Vector2i(currentNode->x, currentNode->y));

		if (nodes.size() > 0)
			currentNode = nodes[0];
		else
		{
			pathFound = 0;
			break;
		}

		//remove from open and add to closed
		removeFromList(currentNode, open);
		currentNode->onClosed = 1;
		closed.push_back(currentNode);
		currentNode->onOpen = 0;

	} while (currentNode != goalNode);

	std::vector<sf::Vector2f> path;
	float sizeOffset = GRID_SIZE / 2;
	if (currentNode == goalNode)
		while (currentNode != startNode && currentNode != nullptr)
		{
			path.insert(path.begin(), sf::Vector2f((currentNode->x * GRID_SIZE) + sizeOffset, (currentNode->y * GRID_SIZE) + sizeOffset));
			currentNode->keyNode = 1;
			currentNode = currentNode->parent;
		}


	//std::cout << "Path Found: " << pathFound
	for (int i = 0; i < open.size(); i++)
	{
		open[i]->g = 0;
		open[i]->onOpen = 0;
		open[i]->onClosed = 0;
		open[i]->parent = nullptr;
	}

	for (int i = 0; i < closed.size(); i++)
	{
		closed[i]->g = 0;
		closed[i]->onOpen = 0;
		closed[i]->onClosed = 0;
		closed[i]->parent = nullptr;
	}

	open.clear();
	closed.clear();
	return path;
}

//CALCULATE NODES
std::vector<PathNode*> PathFinder::calculateNodes(sf::Vector2i index)
{
	//get edges
	bool top = 0, left=0, right=0, bottom=0;
	if (index.y <= 0)
		top = 1;
	else if (index.y >= height-1)
		bottom = 1;
	if (index.x <= 0)
		left = 1;
	else if (index.x >= width-1)
		right = 1;

	//parent - add to closed
	closed.push_back(&pathMesh[index.x][index.y]);

	//surrounding note vector
	std::vector<PathNode*> nodes;
	PathNode* parent = &pathMesh[index.x][index.y];
	PathNode* c;

	//set parent, gcost, fvalue, and add to open
	//top left
	if (!top && !left)
	{
		c = &pathMesh[index.x - 1][index.y - 1];
		if (c->valid && !c->onClosed)
		{
			if (c->onOpen)
			{
				if (parent->g + DIAGONAL_COST < c->g)
					c->parent = parent;
			}
			else
			{
				c->parent = parent;
				c->onOpen = 1;
				nodes.push_back(c);
				open.push_back(c);
			}

			nodes.push_back(c);
			c->g = parent->g + DIAGONAL_COST;
			c->f = c->g + c->h;
		}
	}

	//top mid
	if (!top)
	{
		c = &pathMesh[index.x][index.y - 1];
		if (c->valid && !c->onClosed)
		{
			if (c->onOpen)
			{
				if (parent->g + NORMAL_COST < c->g)
					c->parent = parent;
			}
			else
			{
				c->parent = parent;
				c->onOpen = 1;
				nodes.push_back(c);
				open.push_back(c);
			}

			nodes.push_back(c);
			c->g = parent->g + NORMAL_COST;
			c->f = c->g + c->h;
		}
	}
	//top right
	if (!top && !right)
	{
		c = &pathMesh[index.x + 1][index.y - 1];
		if (c->valid && !c->onClosed)
		{
			if (c->onOpen)
			{
				if (parent->g + DIAGONAL_COST < c->g)
					c->parent = parent;
			}
			else
			{
				c->parent = &pathMesh[index.x][index.y];
				c->onOpen = 1;
				nodes.push_back(c);
				open.push_back(c);
			}

			nodes.push_back(c);
			c->g = parent->g + DIAGONAL_COST;
			c->f = c->g + c->h;
		}
	}

	//mid left
	if (!left)
	{
		c = &pathMesh[index.x - 1][index.y];
		if (c->valid && !c->onClosed)
		{
			if (c->onOpen)
			{
				if (parent->g + NORMAL_COST < c->g)
					c->parent = parent;
			}
			else
			{
				c->parent = parent;
				c->onOpen = 1;
				nodes.push_back(c);
				open.push_back(c);
			}

			nodes.push_back(c);
			c->g = parent->g + NORMAL_COST;
			c->f = c->g + c->h;
		}
	}

	//mid right
	if (!right)
	{
		c = &pathMesh[index.x + 1][index.y];
		if (c->valid && !c->onClosed)
		{

			if (c->onOpen)
			{
				if (parent->g + NORMAL_COST < c->g)
					c->parent = parent;
			}
			else
			{
				c->parent = parent;
				c->onOpen = 1;
				nodes.push_back(c);
				open.push_back(c);
			}

			nodes.push_back(c);
			c->g = parent->g + NORMAL_COST;
			c->f = c->g + c->h;
		}
	}

	//bottom left
	if (!left && !bottom)
	{
		c =& pathMesh[index.x - 1][index.y + 1];
		if (c->valid && !c->onClosed)
		{
			if (c->onOpen)
			{
				if (parent->g + DIAGONAL_COST < c->g)
					c->parent = parent;
			}
			else
			{
				c->parent = parent;
				c->onOpen = 1;
				nodes.push_back(c);
				open.push_back(c);
			}

			nodes.push_back(c);
			c->g = parent->g + DIAGONAL_COST;
			c->f = c->g + c->h;
		}
	}
	//bottom mid
	if (!bottom)
	{
		c = &pathMesh[index.x][index.y + 1];
		if (c->valid && !c->onClosed)
		{
			if (c->onOpen)
			{
				if (parent->g + NORMAL_COST < c->g)
					c->parent = parent;
			}
			else
			{
				c->parent = parent;
				c->onOpen = 1;					
				open.push_back(c);
			}

			nodes.push_back(c);
			c->g = parent->g + NORMAL_COST;
			c->f = c->g + c->h;
		}
	}

	//bottom right
	if (!bottom && !right)
	{
		c = &pathMesh[index.x + 1][index.y + 1];
		if (c->valid && !c->onClosed)
		{
			if (c->onOpen)
			{
				if (parent->g + DIAGONAL_COST < c->g)
					c->parent = parent;
			}
			else
			{
				c->parent = parent;
				c->onOpen = 1;
				open.push_back(c);
			}

			nodes.push_back(c);
			c->g = parent->g + DIAGONAL_COST;
			c->f = c->g + c->h;
		}
	}

	//sort nodes TEMP**
	for(int i=0; i<nodes.size(); i++)
		for (int j = 0; j < nodes.size(); j++)
		{
			if (nodes[i]->f < nodes[j]->f)
			{
				PathNode* tmp = nodes[i];
				nodes[i] = nodes[j];
				nodes[j] = tmp;
			}
		}

	return nodes;
}

//REMOVE FROM CLOSED
void PathFinder::removeFromList(PathNode* node, std::vector<PathNode*> list)
{
	for (int i = 0; i < list.size(); i++)
		if (node == list[i])
		{
			list.erase(list.begin() + i);
			i = list.size() + 1;
		}
}

//GET GRID
std::vector<sf::RectangleShape> PathFinder::getGrid()
{
	std::vector<sf::RectangleShape> grid;
	for(int i=0; i<100; i++)
		for (int j = 0; j < 100; j++)
		{
			sf::RectangleShape s;
			s.setOutlineThickness(1);
			s.setOutlineColor(sf::Color::Black);
			s.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
			s.setPosition(sf::Vector2f(i * GRID_SIZE, j * GRID_SIZE));
			if (pathMesh[i][j].keyNode)
			{
				s.setFillColor(sf::Color(0, 255, 0, 50));
				grid.push_back(s);
			}
			
			if (!pathMesh[i][j].valid)
			{
				s.setFillColor(sf::Color(255, 0, 0, 50));
				grid.push_back(s);
			}
		}
	return grid;
}