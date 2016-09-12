#include "stdafx.h"
#include "GUI_Button.h"


GUI_Button::GUI_Button()
{
	value = 0;
	window = nullptr;
	click.set(sf::Mouse::Button::Left, SINGLE);
}


GUI_Button::GUI_Button(WindowMgr* _window, GUI_Button_Type _type, sf::Vector2f _position, sf::Vector2f _size)
{
	window = _window;
	type = _type;
	position = _position;
	size = _size;
	value = 0;
	rect.setSize(size);
	rect.setPosition(position);
	rect.setFillColor(sf::Color::Red);
}

void GUI_Button::set(WindowMgr* _window, GUI_Button_Type _type, sf::Vector2f _position, sf::Vector2f _size)
{
	window = _window;
	type = _type;
	position = _position;
	size = _size;
	value = 0;
	rect.setSize(size);
	rect.setPosition(position);
	rect.setFillColor(sf::Color::Red);
	font.loadFromFile("Assets/font.ttf");
	text.setFont(font);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);
	text.setString("Value: " + misc::doubleToString(value));
	sf::FloatRect textRect = text.getGlobalBounds();
	text.setOrigin(sf::Vector2f(textRect.width / 2, textRect.height / 2));
	text.setPosition(sf::Vector2f(position.x + (size.x / 2), position.y + (size.y / 2)));
}

void GUI_Button::update()
{
	switch (type)
	{
	
		case CLICK:
		{
			value = 0;
			if (click.getValue() && mouseWithin())
				value = 1;
			break;
		}
	
		case CHECK_BOX:
		{
			if (click.getValue() && mouseWithin())
				value = !value;
			break;
		}
	
		default:
			break;
	}

	text.setString("Value: " + misc::doubleToString(value));
}

void GUI_Button::draw()
{
	window->addGui(rect);
	window->addGui(text);
}

GUI_Button::~GUI_Button()
{
}

bool GUI_Button::mouseWithin()
{

	int x = mouse.getPosition(*window->getWindow()).x / window->getScale().x;
	int y = mouse.getPosition(*window->getWindow()).y / window->getScale().y;
	if (rect.getGlobalBounds().contains(sf::Vector2f(x, y)))
		return 1;

	return 0;
}
