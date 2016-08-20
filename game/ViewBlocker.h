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
	sf::ConvexShape shape;
	Entity* entity;
};

class ViewBlocker
{
	WindowMgr* window;
	b2World* world;
	Entity* player;
	sf::Vector2f center;
	Blocker* blockers;

	//tmp
	std::thread* threads;
	int cores;
	int n_blockers;
	int max_blockers = 1000;
	void calculateBlocker(Blocker& blocker);
public:
	ViewBlocker();
	~ViewBlocker();
	void set(Entity& _player, WindowMgr* _window, b2World* _world);
	void addObject(Entity& entity);
	void update();
	void draw();
};

