#include "Map.h"


Map::Map()
{
}


Map::~Map()
{
}

//LOAD FILE
std::vector<Entity*> Map::loadFile(std::string _filename, std::vector<Texture*> textures, WindowMgr* _window, b2World* _world)
{
	window = _window;
	world = _world;
	std::ifstream f;
	f.open(_filename.c_str());
	std::string line;
	char t = ',';

	if (f.is_open())
	{

		objects.clear();
		Entity* obj;
		while (!f.eof())
		{
			std::getline(f, line);
			//static
			if (line[0] == 's')
			{
				//parse
				float posX = std::stof(misc::extractBetween(line, t, '#'));
				float posY = std::stof(misc::extractBetween(line, t, '#'));
				float rot = std::stof(misc::extractBetween(line, t, '#'));
				float sizeX = std::stof(misc::extractBetween(line, t, '#'));
				float sizeY = std::stof(misc::extractBetween(line, t, '#'));
				std::string textureName = misc::extractBetween(line, t, '#');
				std::string type = misc::extractBetween(line, t, '#');
				Entity* entity;
			}
			//rect
			else if (line[0] == 'r')
			{
				float posX = std::stof(misc::extractBetween(line, t, '#'));
				float posY = std::stof(misc::extractBetween(line, t, '#'));
				float rot = std::stof(misc::extractBetween(line, t, '#'));
				float sizeX = std::stof(misc::extractBetween(line, t, '#'));
				float sizeY = std::stof(misc::extractBetween(line, t, '#'));
				std::string textureName = misc::extractBetween(line, t, '#');
				obj = new Solid;
				obj->getHitbox().setSize(sf::Vector2f(sizeX, sizeY));
				obj->getHitbox().setPosition(sf::Vector2f(posX, posY));
				obj->getHitbox().setRotation(rot);
				obj->getHitbox().setFillColor(sf::Color::White);
				obj->initialize(window, world, 1, 1, posX, posY);
				obj->getBody()->SetTransform(obj->getBody()->GetPosition(), rot * -DEG2RAD);
			}

			//add
			objects.push_back(obj);
		}
	}


	for (int i = 0; i < objects.size(); i++)
		objects[i]->spawn();
	return objects;
}

//GENERATE FILE
void Map::generateFile(std::string filename, EditorObject* objects, unsigned int n_objects)
{
	filename = "Assets/" + filename;
	std::ofstream f(filename.c_str());
	char t = ',';
	for (int i = 0; i < n_objects; i++)
	{
		sf::RectangleShape* r = &objects[i].rectangle;

		switch (objects[i].type)
		{
		case ObjType::RECTANGLE:
			f << 'r' << t;
			f << r->getPosition().x << t << r->getPosition().y << t;//pos
			f << r->getRotation() << t;//rotation
			f << r->getSize().x << t << r->getSize().y << t; //size
			f << objects[i].textureName << t;
			break;
		case ObjType::STATIC_OBJ:
			f << 's' << t;
			f << r->getPosition().x << t << r->getPosition().y << t;//pos
			f << r->getRotation() << t;//rotation
			f << r->getSize().x << t << r->getSize().y << t; //size
			f << objects[i].textureName << t;
			break;
		case ObjType::DYNAMIC_OBJ:
			break;
		}

		f << '\n';
	}

	f.close();

	std::cout << "saved\n";
}