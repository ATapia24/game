#pragma once

#include <SFML\Graphics.hpp>

class NativePosition
{

private:
	sf::Vector2f* position;
public:
	NativePosition();
	~NativePosition();
	
	//move
	void move(float x, float y);
	void moveX(float x);
	void moveY(float y);

	//set
	void set(float x, float y);
	void setX(float x);
	void setY(float y);

	sf::Vector2f get();
	float x();
	float y();
};

