#include "stdafx.h"
#include "KeyManager.h"


//CONSTRUCTOR
Key::Key()
{
}

//DESTRUCTOR
Key::~Key()
{
}

//CONSTRUCTOR W/ setup
Key::Key(sf::Keyboard::Key _key, KeyType _type)
{
	key = _key;
	type = _type;
}

//SET
void Key::set(sf::Keyboard::Key _key, KeyType _type)
{
	key = _key;
	type = _type;
}

//SINGLE CHECK
bool Key::singleCheck()
{
	if (sf::Keyboard::isKeyPressed(key) && released)
	{
		released = 0;
		return true;
	}
	else if(!sf::Keyboard::isKeyPressed(key) && !released)
	{
		released = 1;
	}

	return false;
}

//LIVE CHECK
bool Key::repeatedCheck()
{
	return sf::Keyboard::isKeyPressed(key);
}

//GET VALUE
bool Key::getValue()
{
	switch (type)
	{
	case SINGLE:
		return singleCheck();
		break;
	case REPEATED:
		return repeatedCheck();
		break;
	default:
		return 0;
	}
}