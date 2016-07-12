#include "stdafx.h"
#include "MenuSelect.h"

MenuSelect::MenuSelect(){}
MenuSelect::~MenuSelect(){}

//LOAD
void MenuSelect::load()
{
	//general
	layer = 0;
	font.loadFromFile("assets/font.ttf");
	topPadding = 0;
	leftPadding = 0;
	topSpacing = 0;
	leftSpacing = 0;
	fontSize = 12;

	//index based
	wrapIndex = 1;
	currentIndex = 0;
	lines[currentIndex].text.setColor(sf::Color::Red);
}

//UPDATE
//desc. return input and general update
int MenuSelect::update()
{
	//return input
	return input();
}

//INPUT
int MenuSelect::input()
{


	//index up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && upIndexKeyReleased)
	{
		indexUp();
		upIndexKeyReleased = 0;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		upIndexKeyReleased = 1;
	}


	//index down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && downIndexKeyReleased)
	{
		indexDown();
		downIndexKeyReleased = 0;
	}else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		downIndexKeyReleased = 1;
	}

	//select
	//check for select and return index
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && returnIndexKeyReleased)
	{
		returnIndexKeyReleased = 0;
		return currentIndex;
	}else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		returnIndexKeyReleased = 1;
	}

	//return no input
	return -1;
}

//INDEX UP
void MenuSelect::indexUp()
{
	//set last color
	lines[currentIndex].text.setColor(sf::Color::White);

	if (wrapIndex)
	{
		currentIndex == 0 ? currentIndex = lines.size() - 1 : currentIndex--;
	}
	else
	{
		currentIndex == 0 ? currentIndex = 0: currentIndex--;
	}

	//set current color
	lines[currentIndex].text.setColor(sf::Color::Red);
}

//INDEX DOWN
void MenuSelect::indexDown()
{
	//set last color
	lines[currentIndex].text.setColor(sf::Color::White);

	if (wrapIndex)
	{
		currentIndex == lines.size() - 1 ? currentIndex = 0 : currentIndex++;
	}
	else
	{
		currentIndex == lines.size() - 1 ? currentIndex = currentIndex : currentIndex++;
	}

	//set current color
	lines[currentIndex].text.setColor(sf::Color::Red);
}
