#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <SFML\System\Thread.hpp>
#include <thread>

//WINDOW MGR CLASS
class WindowMgr
{

private:
	sf::RenderWindow *windowPtr;
	sf::View guiView;
	sf::View worldView;
	float NATIVE_WIDTH, NATIVE_HEIGHT;
	float widthScale, heightScale;
	
	struct queueType
	{
		short int type;
		sf::Sprite* sprite;
		sf::Text* text;
		sf::RectangleShape* rectangle;
		sf::CircleShape* circle;
		sf::ConvexShape* convex;
	};

	const long int MAX_DRAW_SIZE = 1000000;
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
	void draw();
	sf::RenderWindow* getWindow();
	sf::View* getWorldView() { return &worldView; };
	sf::View* getGuiView() { return &guiView; };
};