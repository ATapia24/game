#pragma once

#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Projectile.h"
#include "WindowMgr.h"
#include "Box2D\Box2D.h"
#include <vector>

class Holdable
{
	sf::Sprite sprite;
	Animation main;
	b2World* world;
	WindowMgr* window;

	std::vector<Projectile*> bullets;
	
public:
	Holdable();
	~Holdable();
	void load(WindowMgr* _window, b2World* _world);
	void update();
	void draw();
	void fire(float angle, b2Vec2 pos);
};

