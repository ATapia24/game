#pragma once

#include <SFML\Graphics.hpp>
#include "WindowMgr.h"
#include "Timer.h"

class AnimatedBackground
{

private:
	WindowMgr *window;
	sf::Sprite image;
	sf::Texture texture;
	std::string filename;
	int n_frames;
	int height, width;
	int xFrame, yFrame;
	Timer timer;
	int frameCount;
public:
	void load(std::string _filename, int _n_frames, int w, int h);
	void update();
	void draw();
	void setWindow(WindowMgr &_window);
	AnimatedBackground();
	~AnimatedBackground();
};

