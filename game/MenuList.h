#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "NativePosition.h"
#include "WindowMgr.h"

enum MenuObjectType
{
	TEXT,
	SPRITE,
	COMBO
};

struct MenuObject
{
	MenuObjectType type;
	bool active;
	std::string *string;
	sf::Text text;
	sf::Sprite sprite;
	sf::RectangleShape bg;
};

class MenuList
{
protected:
	WindowMgr *window;

	std::vector< std::vector<MenuObject> > grid;
	std::vector<std::string*> staticStrings;

	//general
	sf::Vector2f position;
	int globalWidth, globalHeight;
	int width, height;
	float verticalSpacing, horizontalSpacing;
	int count;
	std::string s;
	sf::Text t;
	//font
	sf::Font font;
	float fontSize;

	//background
	sf::RectangleShape background;
	bool backgroundEnabled;

public:
	MenuList(WindowMgr* _window);
	MenuList();
	~MenuList();
	void setWindow(WindowMgr* _window);
	virtual void load();
	void draw();
	void add(std::string& string);
	void addStatic(std::string string);
	void setDimensions(int n_col, int n_row, int width, int height);
	void setPosition(float x, float y);
};

