#include "NativePosition.h"


NativePosition::NativePosition()
{
	position = new sf::Vector2f(0, 0);
}
NativePosition::~NativePosition(){}

//GET
sf::Vector2f NativePosition::get()
{
	return *position;
}

//MOVE X/Y
void NativePosition::move(float x, float y)
{
	position->x += x;
	position->y += y;
}

//MOVE X
void NativePosition::moveX(float x)
{
	position->x += x;
}

//MOVE Y
void NativePosition::moveY(float y)
{
	position->y += y;
}

//SET X/Y
void NativePosition::set(float x, float y)
{
	position->x = x;
	position->y = y;
}

//SET X
void NativePosition::setX(float x)
{
	position->x = x;
}

//SET Y
void NativePosition::setY(float y)
{
	position->y = y;
}

//X
float NativePosition::x()
{
	return position->x;
}

//Y
float NativePosition::y()
{
	return position->y;
}