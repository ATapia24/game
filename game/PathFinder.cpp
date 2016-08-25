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
void PathFinder::findPath(const sf::Vector2f start, const sf::Vector2f end)
{
	sf::Vector2i g = getPathMeshCoordinates(end);
	calculateH(g);
	float d;
	std::cout << "\n\n";
	PathNode* low = calculateNodes(getPathMeshCoordinates(start))[0];
	closed.push_back(low);
	low->onOpen = 0;
	low->onClosed = 1;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (&pathMesh[j][i] == low)
				std::cout << ' ' << ' ';
			else
				std::cout << pathMesh[j][i].onOpen << ' ';
		}

		std::cout << '\n';
	}


	d = sqrt((g.x - low->x)*(g.x - low->x) + (g.y - low->y)*(g.y - low->y));
	system("PAUSE");

	do {
		std::cout << "\n\n";
		std::vector<PathNode*> nodes = calculateNodes(sf::Vector2i(low->x, low->y));
		if (nodes.size() > 0)
			low = nodes[0];
		else break;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (&pathMesh[j][i] == low)
					std::cout << ' ' << ' ';
				else
					std::cout << pathMesh[j][i].onOpen << ' ';
			}

			std::cout << '\n';
		}


		d = sqrt((g.x - low->x)*(g.x - low->x) + (g.y - low->y)*(g.y - low->y));

		//	std::cout << "h: " << low->h << "\n\n";
		system("PAUSE");

		//remove from open and add to closed
		removeFromList(low, open);
		low->onClosed = 1;
		closed.push_back(low);
		low->onOpen = 0;
	} while (d > 1);

	//std::cout << "done\n";
	//special check
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

	//set invalid
	pathMesh[index.x][index.y].valid = 0;

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
				betterMove(parent, c, DIAGONAL_COST);
			}
			else
			{
				c->parent = &pathMesh[index.x][index.y];
				c->g = pathMesh[index.x][index.y].g + DIAGONAL_COST;
				c->f = c->g + c->h;
				c->onOpen = 1;
				nodes.push_back(c);
				open.push_back(c);
			}
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
				betterMove(parent, c, DIAGONAL_COST);
			}
			else
			{
				c->parent = &pathMesh[index.x][index.y];
				c->g = pathMesh[index.x][index.y].g + NORMAL_COST;
				c->f = c->g + c->h;
				c->onOpen = 1;
				nodes.push_back(c);
				open.push_back(c);
			}
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
				betterMove(parent, c, DIAGONAL_COST);
			}
			else
			{
				c->parent = &pathMesh[index.x][index.y];
				c->g = pathMesh[index.x][index.y].g + DIAGONAL_COST;
				c->f = c->g + c->h;
				c->onOpen = 1;
				nodes.push_back(c);
				open.push_back(c);
			}
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
				betterMove(parent, c, DIAGONAL_COST);
			}
			else
			{
				c->parent = &pathMesh[index.x][index.y];
				c->g = pathMesh[index.x][index.y].g + NORMAL_COST;
				c->f = c->g + c->h;
				c->onOpen = 1;
				nodes.push_back(c);
				open.push_back(c);
			}
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
					betterMove(parent, c, DIAGONAL_COST);
			}
			else
			{
				c->parent = &pathMesh[index.x][index.y];
				c->g = pathMesh[index.x][index.y].g + NORMAL_COST;
				c->f = c->g + c->h;
				c->onOpen = 1;
				nodes.push_back(c);
				open.push_back(c);
			}
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
				betterMove(parent, c, DIAGONAL_COST);
			}
			else
			{
				c->parent = &pathMesh[index.x][index.y];
				c->g = pathMesh[index.x][index.y].g + DIAGONAL_COST;
				c->f = c->g + c->h;
				c->onOpen = 1;
				nodes.push_back(c);
				open.push_back(c);
			}
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
				betterMove(parent, c, DIAGONAL_COST);
			}
			else
			{
				c->parent = &pathMesh[index.x][index.y];
				c->g = pathMesh[index.x][index.y].g + NORMAL_COST;
				c->f = c->g + c->h;
				c->onOpen = 1;
				nodes.push_back(c);					
				open.push_back(c);
			}

			std::cout << "x " << c->f << ' ' << c->h << ' ' << c->g << "x \n";
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
				betterMove(parent, c, DIAGONAL_COST);
			}
			else
			{
				c->parent = &pathMesh[index.x][index.y];
				c->g = pathMesh[index.x][index.y].g + DIAGONAL_COST;
				c->f = c->g + c->h;
				c->onOpen = 1;
				nodes.push_back(c);
				open.push_back(c);
			}
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

//BETTER MOVE
bool PathFinder::betterMove(PathNode* a, PathNode* b, unsigned int moveCost)
{
	if (a->g + moveCost > b->g)
		b->parent = a;

	return 0;
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
	for(int i=0; i<width; i++)
		for (int j = 0; j < height; j++)
		{
			sf::RectangleShape s;
			s.setOutlineThickness(1);
			s.setOutlineColor(sf::Color::Black);
			s.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
			s.setPosition(sf::Vector2f(i * GRID_SIZE, j * GRID_SIZE));
			if (!pathMesh[i][j].valid)
			{
				s.setFillColor(sf::Color(255, 0, 0, 50));
				grid.push_back(s);

			}
		}
	return grid;
}