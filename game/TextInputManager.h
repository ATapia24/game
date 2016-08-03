#pragma once

#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include "KeyManager.h"
#include "misc.h"

enum TextInputMode
{
	ALL,
	NUMBERS,
	LETTERS
};

class TextInputManager
{
private:
	bool done;
	TextInputMode mode;
	Key a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;
	Key n0, n1, n2, n3, n4, n5, n6, n7, n8, n9;
	Key space, enter, tab, backspace, del;
	char spaceKey, enterKey, backspaceKey, capslockKey, nullKey, capsOffset;
	std::string text;
	void keySetup();
	char determineKeypress();
	short int cursor;
	void newCharacter(char key);
	void eraseCharacter();

public:
	TextInputManager();
	void update();
	void reset();
	void clear();
	void setMode(TextInputMode _mode);
	void setString(const std::string string);
	void setString(const double value);
	const std::string getString();
	const int getIntegerValue();
	const short getCursor();
	const bool isDone();
	void forceDone();
};

