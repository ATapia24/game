#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

enum KeyType
{
	SINGLE,
	REPEATED
};

class Key
{
private:
	sf::Keyboard::Key key;
	KeyType type;
	bool released;
	bool (Key::*value)();
	bool singleCheck();
	bool repeatedCheck();

public:
	Key();
	Key(sf::Keyboard::Key _key, KeyType _type);
	~Key();
	void set(sf::Keyboard::Key _key, KeyType _type);
	bool getValue();
};

