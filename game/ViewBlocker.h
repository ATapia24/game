#pragma once

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include <vector>
#include "WindowMgr.h"
#include "Entity.h"
#include "globals.h"
#include <cmath>

struct  Blocker
{
	sf::ConvexShape shape;
	Entity* entity;

	sf::RectangleShape line;
};

class ViewBlocker
{
	WindowMgr* window;
	b2World* world;
	Entity* player;
	sf::Vector2f center;
	std::vector<Blocker*> blockers;
	void calculateBlocker(Blocker* blocker);
public:
	ViewBlocker();
	~ViewBlocker();
	void set(Entity& _player, WindowMgr* _window, b2World* _world);
	void addObject(Entity& entity);
	void update();
	void draw();
};

