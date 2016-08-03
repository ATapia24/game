#include "stdafx.h"
#include "KeyManager.h"


//CONSTRUCTOR
Key::Key()
{
	cooldownTime = 120;
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

//SINGLE COOLDOWN CHECK
bool Key::singleCooldownCheck()
{
	if (sf::Keyboard::isKeyPressed(key) && released)
	{
		released = 0;
		cooldownTimer.start();
		return true;
	}
	else if ((!sf::Keyboard::isKeyPressed(key) && !released) || cooldownTimer.getTimeInt() > cooldownTime)
	{
		released = 1;
	}

	return false;
}

//SET COOLDOWN TIME
void Key::setCooldownTime(const int _cooldownTime)
{
	cooldownTime = _cooldownTime;
}

//GET COOLDOWN TIME
const int Key::getCooldownTime()
{
	return cooldownTime;
}

//GET VALUE
const bool Key::getValue()
{
	switch (type)
	{
	case SINGLE:
		return singleCheck();
		break;
	case REPEATED:
		return repeatedCheck();
		break;
	case SINGLE_COOLDOWN:
		return singleCooldownCheck();
		break;
	default:
		return 0;
	}
}