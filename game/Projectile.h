#pragma once

#include "Entity.h"
#include "Timer.h"
#include "globals.h"

class Projectile : public Entity
{
private:
	Timer time;
	float speed;
	int lifetime;
public:
	Projectile();
	~Projectile();
	void initialize(WindowMgr* _window, b2World* _world, float density, float friction, float x, float y);
	void spawn(float angle, b2Vec2 pos);
	void update();
	void startContact(Entity* entity);
	void endContact(Entity* entity);
};

