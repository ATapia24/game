#include "stdafx.h"
#include "WindowMgr.h"


WindowMgr::WindowMgr(sf::RenderWindow& window, const float _NATIVE_WIDTH, const float _NATIVE_HEIGHT)
{
	windowPtr = &window;
	NATIVE_WIDTH = _NATIVE_WIDTH;
	NATIVE_HEIGHT = _NATIVE_HEIGHT;
	widthScale = window.getSize().x / _NATIVE_WIDTH;
	heightScale = window.getSize().y / _NATIVE_HEIGHT;
}


//DRAW
void WindowMgr::draw()
{
	sortDrawQueue();

	windowPtr->clear();

	//draw
	for (unsigned int i = 0; i<drawQueue.size(); i++)
	{
		switch (drawQueue[i].type)
		{
			case 1:
				windowPtr->draw(*drawQueue[i].sprite);
				break;
			case 2:
				windowPtr->draw(*drawQueue[i].text);
				break;
			case 3:
				windowPtr->draw(*drawQueue[i].rectangle);
				break;
			case 4:
				windowPtr->draw(*drawQueue[i].circle);
				break;
			case 5:
				windowPtr->draw(*drawQueue[i].convex);
				break;
		}
	}

	windowPtr->display();

	//clear queue
	drawQueue.clear();
}


/* 
ADD FUNCTIONS desc.
1 set pointer
2 set object scale
3 set position scale
4 set data type
5 set layer
6 add to draw queue
*/

//ADD - Sprite
void WindowMgr::add(sf::Sprite& sprite, int layer)
{
	queueType data;
	data.sprite = &sprite;
	data.sprite->setScale(widthScale, heightScale);
	data.sprite->setPosition((data.sprite->getPosition().x * widthScale), (data.sprite->getPosition().y * heightScale));
	data.type = 1;
	data.layer = layer;
	drawQueue.push_back(data);
}

//ADD - Text
void WindowMgr::add(sf::Text& text, int layer)
{
	queueType data;
	data.text = &text;
	data.text->setScale(widthScale, heightScale);
	data.text->setPosition((data.text->getPosition().x * widthScale), (data.text->getPosition().y * heightScale));
	data.type = 2;
	data.layer = layer;
	drawQueue.push_back(data);
}

//ADD - Rectangle
void WindowMgr::add(sf::RectangleShape& rectangle, int layer)
{
	queueType data;
	data.rectangle = &rectangle;
	data.rectangle->setScale(widthScale, heightScale);
	data.rectangle->setPosition((data.rectangle->getPosition().x * widthScale), (data.rectangle->getPosition().y * heightScale));
	data.type = 3;
	data.layer = layer;
	drawQueue.push_back(data);
}

//ADD - Circle
void WindowMgr::add(sf::CircleShape& circle, int layer)
{
	queueType data;
	data.circle = &circle;
	data.circle->setScale(widthScale, heightScale);
	data.circle->setPosition((data.circle->getPosition().x * widthScale), (data.circle->getPosition().y * heightScale));
	data.type = 4;
	data.layer = layer;
	drawQueue.push_back(data);
}

//ADD - Convex
void WindowMgr::add(sf::ConvexShape& convex, int layer)
{
	queueType data;
	data.convex = &convex;
	data.convex->setScale(widthScale, heightScale);
	data.convex->setPosition((data.convex->getPosition().x * widthScale), (data.convex->getPosition().y * heightScale));
	data.type = 5;
	data.layer = layer;
	drawQueue.push_back(data);
}

//SORT DRAW QUEUE
void WindowMgr::sortDrawQueue()
{
	queueType tmp;

	for (unsigned int i = 0; i < drawQueue.size(); i++)
	{
		for (unsigned int j = 0; j < drawQueue.size(); j++)
		{
			if (drawQueue[i].layer > drawQueue[j].layer)
			{
				tmp = drawQueue[i];
				drawQueue[i] = drawQueue[j];
				drawQueue[j] = tmp;
			}
		}
	}
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
}
