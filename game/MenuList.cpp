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
	fontSize = 22;
	position.x = 0;
	position.y = 0;
	horizontalSpacing = 0;
	verticalSpacing = 0;
	menuBackgroundEnabled = 0;
	objectBackgroundEnabled = 0;
	verticalFill = 1;
	currentIndex = 0;
	lastIndex = 0;
	defaultColor = sf::Color::White;
	selectedColor = sf::Color::Red;

	//tmp
	background.setFillColor(sf::Color(76, 88, 68, 255));
}


MenuList::~MenuList()
{

}


//DRAW
void MenuList::draw()
{
	//menu background
	if (menuBackgroundEnabled)
		window->addGui(background);

	for (unsigned int y = 0; y < grid.size(); y++)
	{
		for (unsigned int x = 0; x < grid[y].size(); x++)
		{
			MenuObject* obj = &grid[y][x];

			//object background
			if (objectBackgroundEnabled)
				window->addGui(obj->bg);

			//object
			if (obj->type == MenuObjectType::TEXT)
				window->addGui(obj->text);
			else if (obj->type == MenuObjectType::SPRITE)
				window->addGui(obj->sprite);
			//else if (obj->type == MenuObjectType::COMBO)
		}
	}
}

//UPDATE
void MenuList::update()
{
	for (unsigned int i = 0; i < updatables.size(); i++)
	{
		if (updatables[i]->type == MenuObjectType::TEXT)
			updatables[i]->text.setString(updatables[i]->string->c_str());
		else if (updatables[i]->type == MenuObjectType::SPRITE)
		{
			updatables[i]->sprite.setTexture(*updatables[i]->texture);
			updatables[i]->sprite.setScale(sf::Vector2f(0.2f, 0.2f));
			updatables[i]->sprite.setTextureRect(sf::IntRect(0, 0, updatables[i]->texture->getSize().x, updatables[i]->texture->getSize().y));
		}
	}
}


//ADD - Dynamic
void MenuList::add(std::string& string)
{
	//determine next open spot
	sf::Vector2i index = calcNextIndex();

	//set object
	MenuObject* obj = &grid[index.y][index.x];
	updatables.push_back(obj);
	objects.push_back(obj);
	obj->type = MenuObjectType::TEXT;
	obj->active = 1;
	obj->string = &string;
	obj->text.setFont(font);
	obj->text.setCharacterSize(fontSize);
	obj->text.setPosition(obj->bg.getPosition());
	obj->text.setFillColor(defaultColor);
	obj->text.setString(obj->string->c_str());
	//obj->width = width;
	//obj->height = height;

	//calc pos
	sf::Vector2f pos = obj->bg.getPosition();
	position.y -= obj->text.getGlobalBounds().height / 2;
	obj->text.setPosition(pos);
}

//ADD - Static
void MenuList::addStatic(std::string string)
{
	//store string
	std::string* tmp = new std::string;
	*tmp = string;
	staticStrings.push_back(tmp);

	//determine next open spot
	sf::Vector2i index = calcNextIndex();

	//set object
	MenuObject* obj = &grid[index.y][index.x];
	objects.push_back(obj);
	obj->type = MenuObjectType::TEXT;
	obj->active = 1;
	obj->string = staticStrings[staticStrings.size() - 1];
	obj->text.setFont(font);
	obj->text.setCharacterSize(fontSize);
	obj->text.setFillColor(defaultColor);
	obj->text.setString(obj->string->c_str());
	obj->width = width;
	obj->height = height;

	//calc pos
	sf::Vector2f pos = obj->bg.getPosition();
	position.y -= obj->text.getGlobalBounds().height / 2;
	obj->text.setPosition(pos);
}

//ADD SPRITE
void MenuList::add(sf::Texture& texture)
{
	//set object
	sf::Vector2i index = calcNextIndex();
	MenuObject* obj = &grid[index.y][index.x];
	objects.push_back(obj);
	updatables.push_back(obj);
	obj->type = MenuObjectType::SPRITE;
	obj->active = 1;
	obj->texture = &texture;
	obj->sprite.setTexture(*obj->texture);
	obj->width = width;
	obj->height = height;
	obj->sprite.setPosition(obj->bg.getPosition());
}

//ADD SPRITE W/ SIZE
void MenuList::add(sf::Texture& texture, unsigned int _width, unsigned int _height)
{
	//set object
	sf::Vector2i index = calcNextIndex();
	MenuObject* obj = &grid[index.y][index.x];
	objects.push_back(obj);
	updatables.push_back(obj);
	obj->type = MenuObjectType::SPRITE;
	obj->active = 1;
	obj->texture = &texture;
	obj->sprite.setTexture(*obj->texture);
	obj->bg.setSize(sf::Vector2f((float)_width, (float)_height));
	obj->width = _width;
	obj->height = _height;
	obj->sprite.setPosition(obj->bg.getPosition());
}

//SET WINDOW
void MenuList::setWindow(WindowMgr* _window)
{
	window = _window;
}

//SET DIMENSIONS
void MenuList::setDimensions(int _n_cols, int _n_rows, int _width, int _height)
{
	//objects size
	width = _width;
	height = _height;
	n_cols = _n_cols;
	n_rows = _n_rows;

	//resize gid
	grid.resize(n_rows);
	for (int i = 0; i < n_rows; i++)
	{
		grid[i].resize(n_cols);
	}

	//set sizes, color, and set to empty
	for (unsigned int y = 0; y < grid.size(); y++)
	{
		for (unsigned int x = 0; x < grid[y].size(); x++)
		{
			grid[y][x].width = _width;
			grid[y][x].height = _height;
			grid[y][x].type = MenuObjectType::EMPTY;
			grid[y][x].bg.setSize(sf::Vector2f(width, height));
			grid[y][x].bg.setFillColor(sf::Color::Green);
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
	calculatePosition();
}

//CALCULATE POSITIONS
void MenuList::calculatePosition()
{
	unsigned int widthOffset = 0, heightOffset = 0;

	for (unsigned int y = 0; y < grid.size(); y++)
	{
		for (unsigned int x = 0; x < grid[y].size(); x++)
		{
			MenuObject* obj = &grid[y][x];

			obj->bg.setPosition(sf::Vector2f((width*x + (x*horizontalSpacing)) + position.x, (height*y + (y*verticalSpacing)) + position.y));
		}

	}

	background.setPosition(sf::Vector2f(position.x, position.y));
}

//SET SPACING
void MenuList::setSpacing(float _horizontalSpacing, float _verticalSpacing)
{
	horizontalSpacing = _horizontalSpacing;
	verticalSpacing = _verticalSpacing;
	setDimensions(n_cols, n_rows, width, height);
}

//ENABLE BACKGROUND
void MenuList::enableBackgrounds(bool _menuBackgroundEnabled, bool _objectBackgroundEnabled)
{
	menuBackgroundEnabled = _menuBackgroundEnabled;
	objectBackgroundEnabled = _objectBackgroundEnabled;
}

//CALCULATE NEXT INDEX
sf::Vector2i MenuList::calcNextIndex()
{
	sf::Vector2i index;
	if (verticalFill)
	{
		index.x = (objects.size()) / n_rows;
		index.y = (objects.size()) % n_rows;
	}else
	{
		index.x = (objects.size()) % n_cols;
		index.y = (objects.size()) / n_cols;
	}

	return index;
}

//INDEX UP
void MenuList::indexUp()
{
	lastIndex = currentIndex;
	currentIndex < objects.size()-1 ? currentIndex++ : currentIndex = 0;
	updateSelected();
}

//INDEX DOWN
void MenuList::indexDown()
{
	lastIndex = currentIndex;
	currentIndex > 0 ? currentIndex-- : currentIndex = objects.size()-1;
	updateSelected();
}

//UPDATE SELECTED
void MenuList::updateSelected()
{
	objects[lastIndex]->text.setFillColor(defaultColor);
	objects[currentIndex]->text.setFillColor(selectedColor);
}

//GET SELECTED TEXT
std::string MenuList::getSelectedText()
{
	return *(objects[currentIndex]->string);
}

//GET SELECETD INDEX
unsigned int MenuList::getSelectedIndex()
{
	return currentIndex;
}

//SET FONT SIZE
void MenuList::setFontSize(unsigned int _fontSize)
{
	fontSize = _fontSize;
}

//CLEAR
void MenuList::clear()
{
	grid.clear();
	staticStrings.clear();
	objects.clear();
	updatables.clear();
}