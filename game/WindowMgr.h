#pragma once

#include <SFML\Graphics.hpp>

//WINDOW MGR CLASS
class WindowMgr
{

private:
	sf::RenderWindow *windowPtr;
	float NATIVE_WIDTH, NATIVE_HEIGHT;
	float widthScale, heightScale;

	struct queueType
	{
		short int type;
		int layer;
		sf::Sprite* sprite;
		sf::Text* text;
		sf::RectangleShape* rectangle;
		sf::CircleShape* circle;
		sf::ConvexShape* convex;
		sf::Image* image;
	} data;

	const long int MAX_DRAW_SIZE = 1000000;
	unsigned int queueSize;
	queueType *drawQueue;

public:
	WindowMgr::WindowMgr(sf::RenderWindow& window, const float _NATIVE_WIDTH, const float _NATIVE_HEIGHT);
	void setResolution(int width, int height, bool fullscreen, bool border);
	void add(sf::Sprite& sprite, int layer);
	void add(sf::Text& text, int layer);
	void add(sf::RectangleShape& rectangle, int layer);
	void add(sf::CircleShape& circle, int layer);
	void add(sf::ConvexShape& convex, int layer);
	void draw();
	sf::RenderWindow* getWindow();
};