#include "stdafx.h"
#include "WindowMgr.h"


WindowMgr::WindowMgr(sf::RenderWindow& window, const float _NATIVE_WIDTH, const float _NATIVE_HEIGHT)
{
	//window
	windowPtr = &window;
	NATIVE_WIDTH = _NATIVE_WIDTH;
	NATIVE_HEIGHT = _NATIVE_HEIGHT;
	widthScale = window.getSize().x / _NATIVE_WIDTH;
	heightScale = window.getSize().y / _NATIVE_HEIGHT;

	//queue
	drawQueue = new queueType[MAX_DRAW_SIZE];
	queueSize = 0;
}

//DRAW
void WindowMgr::draw()
{
	windowPtr->clear();

	//draw
	for (unsigned int i = 0; i<queueSize; i++)
	{
		switch (drawQueue[i].type)
		{
			case 1:
				windowPtr->draw(*drawQueue[i].sprite);
				delete drawQueue[i].sprite;
				break;
			case 2:
				windowPtr->draw(*drawQueue[i].text);
				delete drawQueue[i].text;
				break;
			case 3:
				windowPtr->draw(*drawQueue[i].rectangle);
				delete drawQueue[i].rectangle;
				break;
			case 4:
				windowPtr->draw(*drawQueue[i].circle);
				delete drawQueue[i].circle;
				break;
			case 5:
				windowPtr->draw(*drawQueue[i].convex);
				delete drawQueue[i].convex;
				break;
		}
	}

	windowPtr->display();

	//clear queue
	queueSize = 0;
}

//GET WINDOW
sf::RenderWindow* WindowMgr::getWindow()
{
	return windowPtr;
}

//SET RESOLUTION
void WindowMgr::setResolution(int width, int height, bool fullscreen, bool border)
{
	//calculate new scales
	widthScale = width / NATIVE_WIDTH;
	heightScale = height / NATIVE_HEIGHT;

	//set resolution
	windowPtr->create(sf::VideoMode(width, height), "Game", (fullscreen ? sf::Style::Fullscreen : (border ? sf::Style::Titlebar : sf::Style::None)));
	windowPtr->setFramerateLimit(65);
}

//ADD SPRITE
void WindowMgr::add(sf::Sprite& sprite, int layer)
{
	drawQueue[queueSize].type = 1;
	drawQueue[queueSize].layer = layer;
	drawQueue[queueSize].sprite = new sf::Sprite(sprite);
	drawQueue[queueSize].sprite->setScale(widthScale * drawQueue[queueSize].sprite->getScale().x, heightScale* drawQueue[queueSize].sprite->getScale().y);
	drawQueue[queueSize].sprite->setPosition(widthScale * drawQueue[queueSize].sprite->getPosition().x, heightScale* drawQueue[queueSize].sprite->getPosition().y);
	queueSize++;
}

//ADD TEXT
void WindowMgr::add(sf::Text& text, int layer)
{
	drawQueue[queueSize].type = 2;
	drawQueue[queueSize].layer = layer;
	drawQueue[queueSize].text = new sf::Text(text);
	drawQueue[queueSize].text->setScale(widthScale, heightScale);
	drawQueue[queueSize].text->setPosition(widthScale * drawQueue[queueSize].text->getPosition().x, heightScale* drawQueue[queueSize].text->getPosition().y);
	queueSize++;
}

//ADD RECTANGLE
void WindowMgr::add(sf::RectangleShape& rectangle, int layer)
{
	drawQueue[queueSize].type = 3;
	drawQueue[queueSize].layer = layer;
	drawQueue[queueSize].rectangle = new sf::RectangleShape(rectangle);
	drawQueue[queueSize].rectangle->setScale(widthScale, heightScale);
	drawQueue[queueSize].rectangle->setPosition(widthScale * drawQueue[queueSize].rectangle->getPosition().x, heightScale* drawQueue[queueSize].rectangle->getPosition().y);
	queueSize++;
}

//ADD CIRCLE
void WindowMgr::add(sf::CircleShape& circle, int layer)
{
	drawQueue[queueSize].type = 4;
	drawQueue[queueSize].layer = layer;
	drawQueue[queueSize].circle = new sf::CircleShape(circle);
	drawQueue[queueSize].circle->setScale(widthScale, heightScale);
	drawQueue[queueSize].circle->setPosition(widthScale * drawQueue[queueSize].circle->getPosition().x, heightScale* drawQueue[queueSize].circle->getPosition().y);
	queueSize++;
}

//ADD CONVEX
void WindowMgr::add(sf::ConvexShape& convex, int layer)
{
	drawQueue[queueSize].type = 5;
	drawQueue[queueSize].layer = layer;
	drawQueue[queueSize].convex = new sf::ConvexShape(convex);
	drawQueue[queueSize].convex->setScale(widthScale, heightScale);
	drawQueue[queueSize].convex->setPosition(widthScale * drawQueue[queueSize].convex->getPosition().x, heightScale* drawQueue[queueSize].convex->getPosition().y);
	queueSize++;
}