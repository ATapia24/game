#include "stdafx.h"
#include "AnimatedBackground.h"


AnimatedBackground::AnimatedBackground()
{
}


AnimatedBackground::~AnimatedBackground()
{
}

void AnimatedBackground::load(std::string _filename, int _n_frames, int w, int h)
{
	filename = _filename;
	texture.loadFromFile(filename);
	image.setTexture(texture);
	image.setPosition(sf::Vector2f(400, 400));
	image.setScale(sf::Vector2f(2, 2));
	n_frames = _n_frames;
	width = w;
	height = h;
	xFrame = 0;
	yFrame = 0;
	timer.start();
	frameCount = 0;
}

void AnimatedBackground::update()
{
	if (timer.getTimeInt() > 16)
	{
		timer.stop();

		if (xFrame < 19)
		{
			xFrame++;
		}
		else
		{

			xFrame = 0;
			yFrame++;
			yFrame > 13 ? yFrame = 0: yFrame;
		}

		image.setTextureRect(sf::IntRect(xFrame * width, yFrame * height, width, height));
		timer.reset_ms();
		if (frameCount < 270)
			frameCount++;
	}
}

void AnimatedBackground::draw()
{
	window->add(image, 0);
}

void AnimatedBackground::setWindow(WindowMgr& _window)
{
	window = &_window;
}
