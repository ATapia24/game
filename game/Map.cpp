#include "stdafx.h"
#include "Map.h"


Map::Map()
{
}


Map::~Map()
{
}

//INITIALIZE
void Map::initialize(WindowMgr* _window, b2World* _world, float density, float friction, float x, float y)
{
	window = _window;
	world = _world;

	originOffsetX = (float)texture.getSize().x / 2.f;
	originOffsetY = (float)texture.getSize().y / 2.f;

	bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;

	//def
	spawnPointX = x;
	spawnPointY = y;
	bodyDef->position.Set(spawnPointX, spawnPointY);
	body = world->CreateBody(bodyDef);
	body->SetUserData(this);

	//shape
	shape = new b2PolygonShape();
	shape->SetAsBox(originOffsetX / 32, originOffsetY / 32);

	//fixture
	fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;

	//properties
	body->CreateFixture(shape, 0);

	//tmp 
	c = 0;
}

//UPDATE
void Map::update()
{
	rotate();
}

//DRAW
void Map::draw()
{
	window->addWorld(sprite);
}

//ROTATE
void Map::rotate()
{
	//window->getWorldView()->rotate(window->getGuiView()->getRotation() + ((600 - (float)sf::Mouse::getPosition().x) / 100.f));
	//sf::Mouse::setPosition(sf::Vector2i(600, 600));
}

//CHANGE ORGIN
void Map::changeOrigin(float32 x, float32 y)
{

}