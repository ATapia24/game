#include "stdafx.h"
#include "Holdable.h"

//CONSTRUCTOR
Holdable::Holdable()
{
}

//DECONSTRUCTOR
Holdable::~Holdable()
{
}

//LOAD
void Holdable::load(WindowMgr* _window, b2World* _world)
{
	world = _world;
	window = _window;
}

//UPDATE
void Holdable::update()
{
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->wasKilled())
		{
			world->DestroyBody(bullets[i]->getBody());
			bullets.erase(bullets.begin() + i);
		}
		else
			bullets[i]->update();
	}
}

//FIRE
void Holdable::fire(float angle, b2Vec2 pos)
{
		Projectile* bullet = new Projectile;
		bullet->initialize(window, world, 1, 1, 20, 0);
		bullet->spawn(angle, pos);
		bullets.push_back(bullet);
}

//DRAW
void Holdable::draw()
{
	for (unsigned int i = 0; i < bullets.size(); i++)
		bullets[i]->draw();
}
