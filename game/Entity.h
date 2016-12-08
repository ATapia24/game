#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Box2D/Box2D.h"
#include "WindowMgr.h"
#include "misc.h"
#include "Timer.h"
#include <string>

enum EntityType
{
	PLAYER = 0x0001,
	SOLID = 0x0002,
	PROJECTILE = 0x0004,
	SCREEN = 0x0008
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
	sf::Vector2f viewBlockerPoints[4];
	unsigned int N_VBP = 4;

	//spawn
	bool spawned;
	bool killed;
	float spawnPointX, spawnPointY;

	b2Body* body;
	b2BodyDef* bodyDef;
	b2PolygonShape* shape;
	b2FixtureDef* fixtureDef;
	
	//move
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
	virtual void setName(std::string _name);
	virtual std::string getName();

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
	virtual bool wasKilled();
	virtual bool isAlive();
	sf::Vector2f getSpawnPoint() { return sf::Vector2f(spawnPointX, spawnPointY); }

	//collision
	bool onScreen;
	void startContact(Entity* entity);
	void endContact(Entity* enitity);
	void setOnScreen(bool _onScreen) { onScreen = _onScreen;}
	bool isOneScreen() { return onScreen; }

	EntityType getType() { return type; };
};

#endif
