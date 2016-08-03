#include "stdafx.h"
#include "MenuSelect.h"

MenuSelect::MenuSelect(){}
MenuSelect::~MenuSelect(){}

//LOAD
void MenuSelect::load()
{
	//general
	font.loadFromFile("assets/font.ttf");
	fontSize = 12;

	//index based
	wrapIndex = 1;
	currentIndex = 0;
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
		//indexUp();
		upIndexKeyReleased = 0;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		upIndexKeyReleased = 1;
	}


	//index down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && downIndexKeyReleased)
	{
		//indexDown();
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