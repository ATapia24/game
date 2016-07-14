#pragma once

#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include "Box2D\Box2D.h"
#include "WindowMgr.h"
#include "NativePosition.h"
#include "Timer.h"
#include <string>

class Map
{
private:
	WindowMgr* window;
	b2World* world;
	std::string name;
	sf::Sprite sprite;
	sf::Texture texture;

	//spawn
	bool spawned;
	float spawnPointX, spawnPointY;

	b2Body* body;
	b2BodyDef* bodyDef;
	b2PolygonShape* shape;
	b2FixtureDef* fixtureDef;
	float originOffsetX, originOffsetY;
	void rotate();
	int c;
public:
	Map();
	~Map();
	virtual void initialize(WindowMgr* _window, b2World* _world, float density, float friction, float x, float y);
	virtual void update();
	virtual void draw();
	void changeOrigin(float32 x, float32 y);
	sf::Sprite* getSprite() { return &sprite; };
	sf::Texture* getTexture() { return &texture; };
	b2Body* getBody() { return body; };
	b2Shape* getShape() { return shape; };
};

