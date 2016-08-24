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
	PathMesh = new PathNode*[width];
	for (int w = 0; w < width; w++)
		PathMesh[w] =new PathNode[height];

	//set all to valid
	for (int w = 0; w < width; w++)
		for (int h = 0; h < height; h++)
			PathMesh[w][h].valid = 1;

	for (int i = 0; i < objects.size(); i++)
	{
		std::vector<sf::Vector2f> points = misc::getAreaPoints(objects[i]->getHitbox(), GRID_SIZE/12, 1);

		for (int p = 0; p < points.size(); p++)
		{
			int x = (points[p].x / GRID_SIZE);
			int y = (points[p].y / GRID_SIZE);
			
			if(x >= 0 && y >= 0 && x < width-1 && y < height-1)
			PathMesh[x][y].valid = 0;
		}
	}



}

//GET GRID
sf::VertexArray PathFinder::getGrid()
{
	sf::VertexArray v(sf::Quads);
	int c = 0;
	for(int i=0; i<width; i++)
		for (int j = 0; j < height; j++)
		{
				v.resize(v.getVertexCount() + 4);
				v[0 + c] = sf::Vector2f(i * GRID_SIZE, j * GRID_SIZE);
				v[1 + c] = sf::Vector2f((GRID_SIZE * i) + GRID_SIZE, j * GRID_SIZE);
				v[2 + c] = sf::Vector2f((GRID_SIZE * i) + GRID_SIZE, (j * GRID_SIZE) + GRID_SIZE);
				v[3 + c] = sf::Vector2f(GRID_SIZE * i, (j * GRID_SIZE) + GRID_SIZE);
		}

	for (int i = 0; i < v.getVertexCount(); i++)
		v[i].color = sf::Color(255, 0, 0, 50);

	return v;
}