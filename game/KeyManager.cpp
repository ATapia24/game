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

//MOUSE #########################################################################################################################################################################################################

//CONSTRUCTOR
Key_M::Key_M()
{
	cooldownTime = 120;
}

//DESTRUCTOR
Key_M::~Key_M()
{
}

//CONSTRUCTOR W/ setup
Key_M::Key_M(short int _key, KeyType _type)
{
	key = _key;
	type = _type;
}

//SET
void Key_M::set(short int _key, KeyType _type)
{
	key = _key;
	type = _type;
}

//SINGLE CHECK
bool Key_M::singleCheck()
{
	if (sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(key)) && released)
	{
		released = 0;
		return true;
	}
	else if (!sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(key)) && !released)
	{
		released = 1;
	}

	return false;
}

//LIVE CHECK
bool Key_M::repeatedCheck()
{
	return (sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(key)));
}

//SINGLE COOLDOWN CHECK
bool Key_M::singleCooldownCheck()
{
	if (sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(key)) && released)
	{
		released = 0;
		cooldownTimer.start();
		return true;
	}
	else if ((!sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(key)) && !released) || cooldownTimer.getTimeInt() > cooldownTime)
	{
		released = 1;
	}

	return false;
}

//SET COOLDOWN TIME
void Key_M::setCooldownTime(const int _cooldownTime)
{
	cooldownTime = _cooldownTime;
}

//GET COOLDOWN TIME
const int Key_M::getCooldownTime()
{
	return cooldownTime;
}

//GET VALUE
const bool Key_M::getValue()
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