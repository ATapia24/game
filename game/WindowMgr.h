#ifndef WINDOWMGR_H
#define WINDOWMGR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "misc.h"
#include <SFML/System/Thread.hpp>
#include <thread>

//WINDOW MGR CLASS
/*enum QueuTypes
{
	SPRITE,
	TEXT,
	RECTANGLE,
	CIRCLE,
	CONVEX,
	VERTEXARRAY
};*/

class WindowMgr
{

private:
	sf::RenderWindow *windowPtr;
	sf::View guiView;
	sf::View worldView;
	float nativeWidth, nativeHeight;
	float widthScale, heightScale;
	bool fullscreen, mouseVisible;
	
	struct queueType
	{
		short int type;
		sf::Sprite* sprite;
		sf::Text* text;
		sf::RectangleShape* rectangle;
		sf::CircleShape* circle;
		sf::ConvexShape* convex;
		sf::VertexArray* vertexArray;
		sf::BlendMode blendMode;
	};

	const long int MAX_DRAW_SIZE = 100000;
	unsigned int guiSize, worldSize;
	queueType *guiQueue, *worldQueue;

public:
	WindowMgr::WindowMgr() {};
	WindowMgr::WindowMgr(sf::RenderWindow& window, const float _NATIVE_WIDTH, const float _NATIVE_HEIGHT);
	void setResolution(int width, int height, bool fullscreen, bool border);
	void addGui(sf::Sprite& sprite);
	void addGui(sf::Text& text);
	void addGui(sf::RectangleShape& rectangle);
	void addGui(sf::CircleShape& circle);
	void addGui(sf::ConvexShape& convex);
	void addWorld(sf::Sprite& sprite);
	void addWorld(sf::Text& text);
	void addWorld(sf::RectangleShape& rectangle);
	void addWorld(sf::CircleShape& circle);
	void addWorld(sf::ConvexShape& convex);
	void addWorld(sf::VertexArray& vertexArray);
	void addWorld(sf::Sprite& sprite, const sf::BlendMode blendMode);
	void draw();
	sf::RenderWindow* getWindow();
	sf::View* getWorldView() { return &worldView; };
	sf::View* getGuiView() { return &guiView; };
	sf::Vector2f getScale() { return sf::Vector2f(widthScale, heightScale); };
	bool isFullscreen() { return fullscreen; };
	void setMouseVisible(bool _mouseVisible);
	bool isMouseVisible();
};

#endif