#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "KeyManager.h"
#include "WindowMgr.h"

enum GUI_Button_Type
{
	CLICK,
	CHECK_BOX
};

class GUI_Button
{
private:
	WindowMgr* window;
	GUI_Button_Type type;
	bool value;
	Key_M click;
	sf::Vector2f position, size;
	sf::Mouse mouse;
	sf::RectangleShape rect;
	sf::Text text;
	sf::Font font;
	std::string textString;
	bool mouseWithin();

public:
	GUI_Button();
	~GUI_Button();
	GUI_Button(WindowMgr* _window, GUI_Button_Type _type, sf::Vector2f _position, sf::Vector2f _size);
	void set(WindowMgr* _window, GUI_Button_Type _type, sf::Vector2f _position, sf::Vector2f _size);
	void update();
	void draw();
	bool getValue() { return value; }
	void setValue(bool _value) { value = _value; }
};

#endif