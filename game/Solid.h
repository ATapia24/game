#pragma once
#include "Entity.h"
class Solid : public Entity
{
private:

public:
	Solid();
	~Solid();
	void initialize(WindowMgr* _window, b2World* _world, float density, float friction, float x, float y);
};
