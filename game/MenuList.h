#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "WindowMgr.h"
#include "misc.h"

enum MenuObjectType
{
	TEXT,
	SPRITE,
	COMBO,
	EMPTY
};

struct MenuObject
{
	MenuObjectType type;
	bool active;
	std::string *string;
	sf::Text text;
	sf::Sprite sprite;
	sf::Texture *texture;
	sf::RectangleShape bg;
};

class MenuList
{
protected:
	WindowMgr *window;

	std::vector< std::vector<MenuObject> > grid;
	std::vector<std::string*> staticStrings;
	std::vector<MenuObject*> objects;
	std::vector<MenuObject*> updatables;

	//general
	sf::Vector2f position;
	int globalWidth, globalHeight;
	int n_cols, n_rows;
	int width, height;
	bool verticalFill;
	float verticalSpacing, horizontalSpacing;

	//text
	sf::Font font;
	unsigned int fontSize;
	sf::Color defaultColor;
	sf::Color selectedColor;

	//background
	sf::RectangleShape background;
	bool menuBackgroundEnabled;
	bool objectBackgroundEnabled;

	//misc
	sf::Vector2i calcNextIndex();

	//select
	int currentIndex, lastIndex;

public:
	MenuList(WindowMgr* _window);
	MenuList();
	~MenuList();
	void setWindow(WindowMgr* _window);
	virtual void load();
	void draw();
	void update();
	void add(std::string& string);
	void add(sf::Texture& texture);
	void addStatic(std::string string);
	void setDimensions(int n_col, int n_row, int width, int height);
	void setPosition(float x, float y);
	void setSpacing(float _verticalSpacing, float horizontalSpacing);
	void setFontSize(unsigned int _fontSize);
	void enableBackgrounds(bool _menuBackgroundEnabled, bool _objectBackgroundEnabled);
	void indexUp();
	void indexDown();
	void updateSelected();
	std::string getSelectedText();
	unsigned int getSelectedIndex();
	void clear();
};

