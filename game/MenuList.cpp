#include "stdafx.h"
#include "MenuList.h"


MenuList::MenuList(WindowMgr* _window)
{
	window = _window;
	load();
}

MenuList::MenuList()
{
	load();
}

//LOAD
void MenuList::load()
{
	font.loadFromFile("assets/font.ttf");
	fontSize = 12;
	position.x = 0;
	position.y = 0;
	horizontalSpacing = 10;
	verticalSpacing = 10;
	backgroundEnabled = 1;
	count = 0;

	//tmp
	background.setFillColor(sf::Color(76, 88, 68, 255));
	s = "HELLO";
	t.setFont(font);
	t.setColor(sf::Color::Red);
	t.setCharacterSize(fontSize);
	t.setPosition(sf::Vector2f(100, 100));
	t.setString(s);
}


MenuList::~MenuList()
{

}


//DRAW
void MenuList::draw()
{
	if (backgroundEnabled)
		window->addGui(background);

	for (int y = 0; y < grid.size(); y++)
	{
		for (int x = 0; x < grid[y].size(); x++)
		{
			MenuObject* obj = &grid[y][x];

			if (backgroundEnabled)
				window->addGui(obj->bg);

			if (obj->type == MenuObjectType::TEXT)
			{
				window->addGui(obj->text);
			}
			else if (obj->type == MenuObjectType::SPRITE)
			{

			}
			else if (obj->type == MenuObjectType::COMBO)
			{

			}
		}
	}
}


//ADD - Dynamic
void MenuList::add(std::string& string)
{

}

//ADD - Static
void MenuList::addStatic(std::string string)
{
	//store string
	std::string* tmp = new std::string;
	*tmp = string;
	staticStrings.push_back(tmp);

	//store text
	count++;
	int i = count % grid.size();
	MenuObject* obj = &grid[i - count][i];

	obj->type = MenuObjectType::TEXT;
	obj->active = 1;
	obj->string = staticStrings[staticStrings.size() - 1];
	obj->text.setFont(font);
	obj->text.setCharacterSize(fontSize);
	obj->text.setPosition(sf::Vector2f(position.x, position.y));
	obj->text.setColor(sf::Color::Black);
	obj->text.setString(obj->string->c_str());
}

//SET WINDOW
void MenuList::setWindow(WindowMgr* _window)
{
	window = _window;
}

//SET DIMENSIONS
void MenuList::setDimensions(int n_cols, int n_rows, int _width, int _height)
{
	//objects size
	width = _width;
	height = _height;

	//resize gid
	grid.resize(n_rows);
	for (int i = 0; i < n_rows; i++)
	{
		grid[i].resize(n_cols);
	}

	//objects
	for (int y = 0; y < grid.size(); y++)
	{
		for (int x = 0; x < grid[y].size(); x++)
		{
			grid[y][x].bg.setSize(sf::Vector2f(width, height));
			grid[y][x].bg.setFillColor(sf::Color::White);
		}
	}

	//position
	setPosition(position.x, position.y);

	//menu size
	globalWidth = ((width + horizontalSpacing) * n_cols) - horizontalSpacing;
	globalHeight = ((height + verticalSpacing) * n_rows) - verticalSpacing;

	//background
	background.setPosition(sf::Vector2f(position.x, position.y));
	background.setSize(sf::Vector2f(globalWidth, globalHeight));
}

//SET POSITION
void MenuList::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;

	//calculate new pos
	for (int y = 0; y < grid.size(); y++)
	{
		for (int x = 0; x < grid[y].size(); x++)
		{
			grid[y][x].bg.setPosition(sf::Vector2f((width*x + (x*horizontalSpacing)) + position.x, (height*y + (y*verticalSpacing)) + position.y));
		}
	}

	background.setPosition(sf::Vector2f(position.x, position.y));
}