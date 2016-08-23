#pragma once

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include "WindowMgr.h"
#include "Entity.h"
#include "globals.h"
#include <cmath>
#include <thread>
struct  Blocker
{
	Entity* entity;
	sf::Vector2f points[4];
};

class ViewBlocker
{
	WindowMgr* window;
	b2World* world;
	Entity* player;
	sf::Vector2f center;
	sf::Vector2f lastCenter;
	float lastRotation;
	bool containsMovables;
	Blocker* blockers;
	int n_blockers;
	int max_blockers = 1000000;
	void calculateBlocker(Blocker& blockerd);
	unsigned int d;
	sf::VertexArray va;
	sf::Vector2f* points;
	int pcount;
	bool newUpdate;

public:
	ViewBlocker();
	~ViewBlocker();
	void set(Entity& _player, WindowMgr* _window, b2World* _world);
	void addObject(Entity& entity);
	void update();
	void draw();
	bool inShadow(const Blocker& entity);
};
