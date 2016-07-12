#pragma once

#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include "Box2D\Box2D.h"
#include "WindowMgr.h"
#include "NativePosition.h"
#include "Timer.h"
#include <string>

enum EntityType
{
	PLAYER,
	FLOOR
};

enum Direction
{
	RIGHT,
	LEFT
};

struct Point
{
	float x;
	float y;
};


class Entity
{
protected:
	WindowMgr* window;
	b2World* world;
	EntityType type;
	std::string name;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::RectangleShape hitbox;

	//spawn
	bool spawned;
	float spawnPointX, spawnPointY;

	b2Body* body;
	b2BodyDef* bodyDef;
	b2PolygonShape* shape;
	b2FixtureDef* fixtureDef;
	
	//move
	Direction direction;
	bool moveable;

	//animations
	virtual void updateAnimations();

	//misc
	float originOffsetX, originOffsetY;

public:
	Entity();
	~Entity();
	Entity(WindowMgr* _window);
	virtual void initialize(WindowMgr* _window, b2World* _world, float density, float friction, float x, float y);

	virtual void unload();
	virtual void update();
	virtual void draw();

	//sprite
	virtual sf::Sprite& getSprite();
	virtual sf::Texture& getTexture();
	virtual sf::RectangleShape& getHitbox() { return hitbox; }
	virtual b2Body* getBody() { return body; }
	void setName(std::string _name);
	std::string getName();

	//move
	virtual void input();
	virtual bool isMoveable();
	virtual void setMoveable(bool _moveable);
	virtual void walkRight();
	virtual void walkLeft();
	virtual void stopWalkRight();
	virtual void stopWalkLeft();

	//spawn/kill
	virtual void spawn();
	virtual void kill();
	virtual bool isAlive();

	//collision
	void startContact(Entity* entity);
	void endContact(Entity* enitity);

	EntityType getType() { return type; };
};

