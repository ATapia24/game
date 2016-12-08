#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <SFML/Graphics.hpp>
#include "Timer.h"

enum KeyType
{
	SINGLE,
	REPEATED,
	SINGLE_COOLDOWN,
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
	bool singleCooldownCheck();
	Timer cooldownTimer;
	int cooldownTime;

public:
	Key();
	Key(sf::Keyboard::Key _key, KeyType _type);
	~Key();
	void set(sf::Keyboard::Key _key, KeyType _type);
	void setCooldownTime(const int _cooldownTime);
	const int getCooldownTime();
	const bool getValue();
};

class Key_M
{
private:
	short int key;
	KeyType type;
	bool released;
	bool (Key::*value)();
	bool singleCheck();
	bool repeatedCheck();
	bool singleCooldownCheck();
	Timer cooldownTimer;
	int cooldownTime;

public:
	Key_M();
	Key_M(short int _key, KeyType _type);
	~Key_M();
	void set(short int _key, KeyType _type);
	void setCooldownTime(const int _cooldownTime);
	const int getCooldownTime();
	const bool getValue();
};

#endif