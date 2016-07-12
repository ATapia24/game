#pragma once

#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Animation.h"

class Holdable
{
	sf::Sprite sprite;
	Animation main;
public:
	Holdable();
	~Holdable();
	void load();
	void update();
};

