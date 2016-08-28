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

	//clear
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
			sf::Vector2i pos = getIndex(points[p]);

			if (pos.x >= 0 && pos.y >= 0 && pos.x < width - 1 && pos.y < height - 1)
				pathMesh[pos.x][pos.y].valid = 0;
		}
	}
}

//GET PATH MESH COORDINATES
sf::Vector2i PathFinder::getIndex(sf::Vector2f pos)
{
	return sf::Vector2i(pos.x / GRID_SIZE, pos.y / GRID_SIZE);
}

//FIND PATH
std::vector<sf::Vector2f> PathFinder::findPath(const sf::Vector2f start, const sf::Vector2f end)
{
	//t.start();
	//coords nodes
	sf::Vector2i start_coords = getIndex(start);
	sf::Vector2i goal_coords = getIndex(end);


	//nodes
	startNode = &pathMesh[start_coords.x][start_coords.y];
	goalNode = &pathMesh[goal_coords.x][goal_coords.y];
	PathNode* current = calculateNodes(start_coords);

	//check for invalid goal node
	if (!goalNode->valid)
	{
		goalNode->valid = 1;
		invalidGoalNode = 1;
	}
	else
		invalidGoalNode = 0;
	
	//loop until goal
	while (distance(current, goalNode) != 0)
	{
		
		//get lowest f, h if equal
		for (int i = 0; i < open.size(); i++)
		{
			if (open[i]->f < current->f || (open[i]->f == current->f && open[i]->h < current->h))
				current = open[i];
		}

		//if on node break
		if (distance(goalNode, current) == 0)
			break;

		//calc
		current = calculateNodes(sf::Vector2i(current->x, current->y));
	}

	//get path points
	std::vector<sf::Vector2f> path;
	float sizeOffset = GRID_SIZE / 2;
	while (current != startNode)
	{
		path.insert(path.begin(), sf::Vector2f((current->x * GRID_SIZE) + sizeOffset, (current->y * GRID_SIZE) + sizeOffset));
		current->keyNode = 1;
		current = current->parent;
	}

	//t.stop();
	//std::cout << "time: " << t.getTimeInt() << '\n';


	//reset invalid goal node
	if (invalidGoalNode)
		goalNode->valid = 0;

	return path;
}

//CALCULATE NODES
PathNode* PathFinder::calculateNodes(sf::Vector2i index)
{

	//remove current from open and add to closed
	PathNode* current = &pathMesh[index.x][index.y];
	for (int i = 0; i < open.size(); i++)
		if (open[i] == current)
		{
			open.erase(open.begin() + i);
			i = open.size() + 1;
		}
	closed.push_back(current);
	current->onClosed = 1;
	current->onOpen = 0;

	//get sides
	std::vector<PathNode*> sides = getSides(current);

	//calcs
	for (int i = 0; i < sides.size(); i++)
	{
		if (!sides[i]->onClosed && sides[i]->valid)
		{
			int cost = current->g + distance(current, sides[i]);
			if (cost < sides[i]->g || !sides[i]->onOpen)
			{
				sides[i]->g = cost;
				sides[i]->h = distance(goalNode, sides[i]);
				sides[i]->parent = current;

				if (!sides[i]->onOpen)
				{
					sides[i]->onOpen = 1;
					sides[i]->openIndex = open.size();
					open.push_back(sides[i]);
				}

				sides[i]->f = sides[i]->g + sides[i]->h;
			}
		}
	}

	return open[0];
}

//GET SIDES
std::vector<PathNode*> PathFinder::getSides(PathNode* current)
{
	//get edges
	bool top = 0, left = 0, right = 0, bottom = 0;
	if (current->y <= 0)
		top = 1;
	else if (current->y >= height - 1)
		bottom = 1;
	if (current->x <= 0)
		left = 1;
	else if (current->x >= width - 1)
		right = 1;

	//vect
	std::vector<PathNode*> sides;

	//top left
	if (!top && !left)
	{
		PathNode* topLeft = &pathMesh[current->x - 1][current->y - 1];
		sides.push_back(topLeft);
	}

	//top mid
	if (!top)
	{
		PathNode* topMid = &pathMesh[current->x][current->y - 1];
		sides.push_back(topMid);
	}

	//top right
	if (!top && !right)
	{
		PathNode* topRight = &pathMesh[current->x + 1][current->y - 1];
		sides.push_back(topRight);
	}

	//mid left
	if (!left)
	{
		PathNode* midLeft = &pathMesh[current->x - 1][current->y];
		sides.push_back(midLeft);
	}

	//mid right
	if (!right)
	{
		PathNode* midRight = &pathMesh[current->x + 1][current->y];
		sides.push_back(midRight);
	}

	//bottom left
	if (!left && !bottom)
	{
		PathNode* btmLeft = &pathMesh[current->x - 1][current->y + 1];
		sides.push_back(btmLeft);
	}

	//bottom mid
	if (!bottom)
	{
		PathNode* btmMid = &pathMesh[current->x][current->y + 1];
		sides.push_back(btmMid);
	}

	//bottom right
	if (!bottom && !right)
	{
		PathNode* btmRight = &pathMesh[current->x + 1][current->y + 1];
		sides.push_back(btmRight);
	}

	return sides;
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