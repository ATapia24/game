#include "stdafx.h"
#include "Floor.h"

Floor::Floor(WindowMgr* _window)
{
	window = _window;
	spawnPointX = 0;
	spawnPointY = 0;
	spawned = 0;
	hitbox.setFillColor(sf::Color::Green);
}

Floor::Floor()
{
	moveable = 0;
	type = EntityType::FLOOR;
}


Floor::~Floor()
{
}