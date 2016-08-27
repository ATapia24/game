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
			pathMesh[w][h].f = 0;
			pathMesh[w][h].move_cost = 0;
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

//GET PATH MESH COORDINATES
sf::Vector2i PathFinder::getPathMeshCoordinates(sf::Vector2f pos)
{
	return sf::Vector2i(pos.x / GRID_SIZE, pos.y / GRID_SIZE);
}

//FIND PATH
std::vector<sf::Vector2f> PathFinder::findPath(const sf::Vector2f start, const sf::Vector2f end)
{
	//start
	sf::Vector2i start_coords = getPathMeshCoordinates(start);
	startNode = &pathMesh[start_coords.x][start_coords.y];

	//goal
	sf::Vector2i goal_coords = getPathMeshCoordinates(end);
	goalNode = &pathMesh[goal_coords.x][goal_coords.y];

	PathNode* low = calculateNodes(getPathMeshCoordinates(start));
	float d = misc::distance(sf::Vector2f(low->x, low->y), sf::Vector2f(goalNode->x, goalNode->y));
	//loop until goal
	while (d > 1.5)
	{
		/*std::cout << "distance: " << d << '\n';
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				PathNode* n = &pathMesh[j][i];

				if (n->f == 10)
					std::cout << '0' << n->f << ' ';
				else
					std::cout << n->f << ' ';
				/*if (n == low)
					std::cout << 'x' << ' ';
				else if (n->onOpen)
					std::cout << 's' << ' ';
				else if (n->onClosed)
					std::cout << '#' << ' ';
				else if (!n->valid)
					std::cout << ' ' << ' ';
				else if (n == goal)
					std::cout << 'G' << ' ';
				else
					std::cout << '.' << ' ';
			}
			std::cout << '\n';
		}

		system("PAUSE");*/

		low = calculateNodes(sf::Vector2i(low->x, low->y));
		d = misc::distance(sf::Vector2f(low->x, low->y), sf::Vector2f(goalNode->x, goalNode->y));
	}

	if (low == goalNode)
		std::cout << "PATH FOUND\N";

	std::vector<sf::Vector2f> path;
	float sizeOffset = GRID_SIZE / 2;
		while (low != startNode && low != nullptr)
		{
			std::cout << "loop\n";
			path.insert(path.begin(), sf::Vector2f((low->x * GRID_SIZE) + sizeOffset, (low->y * GRID_SIZE) + sizeOffset));
			low->keyNode = 1;
			low = low->parent;
		}


	return path;
}

//CALCULATE NODES
PathNode* PathFinder::calculateNodes(sf::Vector2i index)
{
	//get edges
	bool top = 0, left = 0, right = 0, bottom = 0;
	if (index.y <= 0)
		top = 1;
	else if (index.y >= height - 1)
		bottom = 1;
	if (index.x <= 0)
		left = 1;
	else if (index.x >= width - 1)
		right = 1;


	std::vector<PathNode*> sides;
	PathNode* main = &pathMesh[index.x][index.y];

	//top left
	if (!top && !left)
	{
		PathNode* topLeft = &pathMesh[main->x - 1][main->y - 1];
		topLeft->move_cost = DIAGONAL_COST;
		sides.push_back(topLeft);
	}

	//top mid
	if (!top)
	{
		PathNode* topMid = &pathMesh[main->x][main->y - 1];
		topMid->move_cost = NORMAL_COST;
		sides.push_back(topMid);
	}

	//top right
	if (!top && !right)
	{
		PathNode* topRight = &pathMesh[main->x + 1][main->y - 1];
		topRight->move_cost = DIAGONAL_COST;
		sides.push_back(topRight);
	}

	//mid left
	if (!left)
	{
		PathNode* midLeft = &pathMesh[main->x - 1][main->y];
		midLeft->move_cost = NORMAL_COST;
		sides.push_back(midLeft);
	}

	//mid right
	if (!right)
	{
		PathNode* midRight = &pathMesh[main->x + 1][main->y];
		midRight->move_cost = NORMAL_COST;
		sides.push_back(midRight);
	}

	//bottom left
	if (!left && !bottom)
	{
		PathNode* btmLeft = &pathMesh[main->x - 1][main->y + 1];
		btmLeft->move_cost = DIAGONAL_COST;
		sides.push_back(btmLeft);
	}

	//bottom mid
	if (!bottom)
	{
		PathNode* btmMid = &pathMesh[main->x][main->y + 1];
		btmMid->move_cost = NORMAL_COST;
		sides.push_back(btmMid);
	}

	//bottom right
	if (!bottom && !right)
	{
		PathNode* btmRight = &pathMesh[main->x + 1][main->y + 1];
		btmRight->move_cost = DIAGONAL_COST;
		sides.push_back(btmRight);
	}

	//add main to closed
	main->onOpen = 0;
	for (int i = 0; i < open.size(); i++)
		if (open[i] == main)
			open.erase(open.begin() + i);

	closed.push_back(main);
	main->onClosed = 1;

	//calcs
	for (int i = 0; i < sides.size(); i++)
	{
		if (!sides[i]->onClosed && sides[i]->valid)
		{
			int cost = main->g + distance(main, sides[i]);
			if (cost < sides[i]->g || !sides[i]->onOpen)
			{
				sides[i]->g = cost;
				sides[i]->h = distance(goalNode, sides[i]);
				sides[i]->parent = main;

				if (!sides[i]->onOpen)
				{
					sides[i]->onOpen = 1;
					open.push_back(sides[i]);
				}
			}
		}
	}

	//sort
	for (int i = 0; i < open.size(); i++)
	{
		for (int j = 0; j < open.size(); j++)
		{
			if (open[i]->f > open[j]->f)
			{
				PathNode* tmp = open[i];
				open[i] = open[j];
				open[j] = tmp;
			}
		}
	}

	return open[0];
}

//DISTANCE
int PathFinder::distance(PathNode* a, PathNode* b)
{
	int x = std::abs(a->x - b->x);
	int y = std::abs(a->y - b->y);

	if (x > y)
		return (y * DIAGONAL_COST) + (NORMAL_COST*(x - y));

	return (x * DIAGONAL_COST) + (NORMAL_COST*(y - x));
}

//GET GRID
std::vector<sf::RectangleShape> PathFinder::getGrid()
{
	std::vector<sf::RectangleShape> grid;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
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

//CLEAR NODES
void PathFinder::clearNodes()
{
	for (int i = 0; i < open.size(); i++)
	{
		open[i]->g = 0;
		open[i]->onOpen = 0;
		open[i]->onClosed = 0;
		open[i]->keyNode = 0;
		open[i]->parent = nullptr;
	}

	for (int i = 0; i < closed.size(); i++)
	{
		closed[i]->g = 0;
		closed[i]->onOpen = 0;
		closed[i]->onClosed = 0;
		closed[i]->parent = nullptr;
		closed[i]->keyNode = 0;
	}

	open.clear();
	closed.clear();
}