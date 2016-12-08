#include "WindowMgr.h"

//CONSTRUCTOR
WindowMgr::WindowMgr(sf::RenderWindow& window, const float _NATIVE_WIDTH, const float _NATIVE_HEIGHT)
{
	//window
	windowPtr = &window;
	nativeWidth = _NATIVE_WIDTH;
	nativeHeight = _NATIVE_HEIGHT;
	widthScale = window.getSize().x / nativeWidth;
	heightScale = window.getSize().y / nativeHeight;
	setResolution(1280, 720, 0, 1);
	fullscreen = 0;
	
	//queues setup
	guiQueue = new queueType[MAX_DRAW_SIZE];
	worldQueue = new queueType[MAX_DRAW_SIZE];
	guiSize = 0;
	worldSize = 0;
}

//DECONSTRUCTOR
WindowMgr::~WindowMgr()
{
	delete[] guiQueue;
	delete[] worldQueue;
}

//DRAW
void WindowMgr::draw()
{
	windowPtr->clear();

	//world
	windowPtr->setView(worldView);
	for (unsigned int i = 0; i<worldSize; i++)
	{
		switch (worldQueue[i].type)
		{
		case 1:
			windowPtr->draw(*worldQueue[i].sprite, worldQueue[i].blendMode);
			delete worldQueue[i].sprite;
			break;
		case 2:
			windowPtr->draw(*worldQueue[i].text, worldQueue[i].blendMode);
			delete worldQueue[i].text;
			break;
		case 3:
			windowPtr->draw(*worldQueue[i].rectangle, worldQueue[i].blendMode);
			delete worldQueue[i].rectangle;
			break;
		case 4:
			windowPtr->draw(*worldQueue[i].circle, worldQueue[i].blendMode);
			delete worldQueue[i].circle;
			break;
		case 5:
			windowPtr->draw(*worldQueue[i].convex, worldQueue[i].blendMode);
			delete worldQueue[i].convex;
			break;
		case 6:
			windowPtr->draw(*worldQueue[i].vertexArray, worldQueue[i].blendMode);
			delete worldQueue[i].vertexArray;
			break;
		}
	}

	//gui
	windowPtr->setView(guiView);
	for (unsigned int i = 0; i<guiSize; i++)
	{
		switch (guiQueue[i].type)
		{
		case 1:
			windowPtr->draw(*guiQueue[i].sprite, guiQueue[i].blendMode);
			delete guiQueue[i].sprite;
			break;
		case 2:
			windowPtr->draw(*guiQueue[i].text, guiQueue[i].blendMode);
			delete guiQueue[i].text;
			break;
		case 3:
			windowPtr->draw(*guiQueue[i].rectangle, guiQueue[i].blendMode);
			delete guiQueue[i].rectangle;
			break;
		case 4:
			windowPtr->draw(*guiQueue[i].circle, guiQueue[i].blendMode);
			delete guiQueue[i].circle;
			break;
		case 5:
			windowPtr->draw(*guiQueue[i].convex, guiQueue[i].blendMode);
			delete guiQueue[i].convex;
			break;
		}
	}

	windowPtr->display();

	//clear queue
	guiSize = 0;
	worldSize = 0;
}

//GET WINDOW
sf::RenderWindow* WindowMgr::getWindow()
{
	return windowPtr;
}

//SET RESOLUTION
void WindowMgr::setResolution(int width, int height, bool _fullscreen, bool border)
{
	//calculate new scales
	widthScale = width / nativeWidth;
	heightScale = height / nativeHeight;

	//set resolution
	windowPtr->create(sf::VideoMode(width, height), "Game", (_fullscreen ? sf::Style::Fullscreen : (border ? sf::Style::Titlebar : sf::Style::None)));
	windowPtr->setPosition(sf::Vector2i(0, 0));
	windowPtr->setFramerateLimit(65);
	fullscreen = _fullscreen;

	//mouse
	windowPtr->setMouseCursorVisible(mouseVisible);

	guiView.reset((sf::FloatRect(0, 0, (float)width, (float)height)));
	worldView.reset((sf::FloatRect(0, 0, (float)width, (float)height)));

}

//GUI - ADD SPRITE
void WindowMgr::addGui(sf::Sprite& sprite)
{
	guiQueue[guiSize].type = 1;
	guiQueue[guiSize].sprite = new sf::Sprite(sprite);
	guiQueue[guiSize].sprite->setScale(guiQueue[guiSize].sprite->getScale().x, guiQueue[guiSize].sprite->getScale().y);
	guiQueue[guiSize].sprite->setPosition(guiQueue[guiSize].sprite->getPosition().x * widthScale, guiQueue[guiSize].sprite->getPosition().y * heightScale);
	guiQueue[worldSize].blendMode = sf::BlendAlpha;
	guiSize++;
}

//GUI - ADD TEXT
void WindowMgr::addGui(sf::Text& text)
{
	guiQueue[guiSize].type = 2;
	guiQueue[guiSize].text = new sf::Text(text);
	guiQueue[guiSize].text->setScale(widthScale, heightScale);
	guiQueue[guiSize].text->setPosition(guiQueue[guiSize].text->getPosition().x * widthScale, guiQueue[guiSize].text->getPosition().y * heightScale);
	guiQueue[worldSize].blendMode = sf::BlendAlpha;
	guiSize++;
}

//GUI - ADD RECTANGLE
void WindowMgr::addGui(sf::RectangleShape& rectangle)
{
	guiQueue[guiSize].type = 3;
	guiQueue[guiSize].rectangle = new sf::RectangleShape(rectangle);
	guiQueue[guiSize].rectangle->setScale(widthScale, heightScale);
	guiQueue[guiSize].rectangle->setPosition(widthScale * guiQueue[guiSize].rectangle->getPosition().x, heightScale* guiQueue[guiSize].rectangle->getPosition().y);
	guiQueue[worldSize].blendMode = sf::BlendAlpha;
	guiSize++;
}

//GUI - ADD CIRCLE
void WindowMgr::addGui(sf::CircleShape& circle)
{
	guiQueue[guiSize].type = 4;
	guiQueue[guiSize].circle = new sf::CircleShape(circle);
	guiQueue[guiSize].circle->setScale(widthScale, heightScale);
	guiQueue[guiSize].circle->setPosition(widthScale * guiQueue[guiSize].circle->getPosition().x, heightScale* guiQueue[guiSize].circle->getPosition().y);
	guiQueue[worldSize].blendMode = sf::BlendAlpha;
	guiSize++;
}

//GUI - ADD CONVEX
void WindowMgr::addGui(sf::ConvexShape& convex)
{
	guiQueue[guiSize].type = 5;
	guiQueue[guiSize].convex = new sf::ConvexShape(convex);
	guiQueue[guiSize].convex->setScale(widthScale, heightScale);
	guiQueue[guiSize].convex->setPosition(widthScale * guiQueue[guiSize].convex->getPosition().x, heightScale* guiQueue[guiSize].convex->getPosition().y);
	guiQueue[worldSize].blendMode = sf::BlendAlpha;
	guiSize++;
}

//World - ADD SPRITE
void WindowMgr::addWorld(sf::Sprite& sprite)
{
	worldQueue[worldSize].type = 1;
	worldQueue[worldSize].sprite = new sf::Sprite(sprite);
	worldQueue[worldSize].sprite->setScale(widthScale * worldQueue[worldSize].sprite->getScale().x, heightScale* worldQueue[worldSize].sprite->getScale().y);
	worldQueue[worldSize].sprite->setPosition(worldQueue[worldSize].sprite->getPosition().x * widthScale, worldQueue[worldSize].sprite->getPosition().y * heightScale);
	worldQueue[worldSize].blendMode = sf::BlendAlpha;
	worldSize++;
}

//World - ADD TEXT
void WindowMgr::addWorld(sf::Text& text)
{
	worldQueue[worldSize].type = 2;
	worldQueue[worldSize].text = new sf::Text(text);
	worldQueue[worldSize].text->setScale(widthScale, heightScale);
	worldQueue[worldSize].text->setPosition(widthScale * worldQueue[worldSize].text->getPosition().x, heightScale* worldQueue[worldSize].text->getPosition().y);
	worldQueue[worldSize].blendMode = sf::BlendAlpha;
	worldSize++;
}

//World - ADD RECTANGLE
void WindowMgr::addWorld(sf::RectangleShape& rectangle)
{
	worldQueue[worldSize].type = 3;
	worldQueue[worldSize].rectangle = new sf::RectangleShape(rectangle);
	worldQueue[worldSize].rectangle->setScale(widthScale, heightScale);
	worldQueue[worldSize].rectangle->setPosition(widthScale * worldQueue[worldSize].rectangle->getPosition().x, heightScale* worldQueue[worldSize].rectangle->getPosition().y);
	worldQueue[worldSize].blendMode = sf::BlendAlpha;
	worldSize++;
}

//World - ADD CIRCLE
void WindowMgr::addWorld(sf::CircleShape& circle)
{
	worldQueue[worldSize].type = 4;
	worldQueue[worldSize].circle = new sf::CircleShape(circle);
	worldQueue[worldSize].circle->setScale(widthScale, heightScale);
	worldQueue[worldSize].circle->setPosition(widthScale * worldQueue[worldSize].circle->getPosition().x, heightScale* worldQueue[worldSize].circle->getPosition().y);
	worldQueue[worldSize].blendMode = sf::BlendAlpha;
	worldSize++;
}

//World - ADD CONVEX
void WindowMgr::addWorld(sf::ConvexShape& convex)
{
	worldQueue[worldSize].type = 5;
	worldQueue[worldSize].convex = new sf::ConvexShape(convex);
	worldQueue[worldSize].convex->setScale(widthScale, heightScale);
	worldQueue[worldSize].convex->setPosition(widthScale * worldQueue[worldSize].convex->getPosition().x, heightScale* worldQueue[worldSize].convex->getPosition().y);
	worldQueue[worldSize].blendMode = sf::BlendAlpha;
	worldSize++;
}

//World - ADD VERTEX ARRAY
void WindowMgr::addWorld(sf::VertexArray& vertexArray)
{
	worldQueue[worldSize].type = 6;
	sf::VertexArray v(vertexArray.getPrimitiveType(), vertexArray.getVertexCount());
	v = vertexArray;
	for (int i = 0; i < vertexArray.getVertexCount(); i++)
	{
		v[i] = sf::Vector2f(v[i].position.x * widthScale, v[i].position.y * heightScale);
		v[i].color = vertexArray[i].color;
	}
	worldQueue[worldSize].vertexArray = new sf::VertexArray(v);
	worldSize++;
}

//World - ADD SPRITE w/ blend mode
void WindowMgr::addWorld(sf::Sprite& sprite, const sf::BlendMode blendMode)
{
	worldQueue[worldSize].type = 1;
	worldQueue[worldSize].sprite = new sf::Sprite(sprite);
	worldQueue[worldSize].sprite->setScale(widthScale * worldQueue[worldSize].sprite->getScale().x, heightScale* worldQueue[worldSize].sprite->getScale().y);
	worldQueue[worldSize].sprite->setPosition(worldQueue[worldSize].sprite->getPosition().x * widthScale, worldQueue[worldSize].sprite->getPosition().y * heightScale);
	worldQueue[worldSize].blendMode = blendMode;
	worldSize++;
}

//SET MOUSE VISIBLE
void WindowMgr::setMouseVisible(bool _mouseVisible)
{
	mouseVisible = _mouseVisible;
	windowPtr->setMouseCursorVisible(_mouseVisible);
}

//IS MOUSE VISIBLE
bool WindowMgr::isMouseVisible()
{
	return mouseVisible;
}
