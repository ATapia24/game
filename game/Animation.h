#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include "Timer.h"
#include <iostream>

class Animation
{
private:
	sf::Sprite* sprite;
	sf::Texture texture;
	sf::Sprite* parent;
	std::string filename;
	int n_frames;
	int height, width;
	int xFrame, yFrame;
	int directionOffset;
	int col, row;
	Timer timer;
	int frameCount;
	float frameSpeed;

public:
	Animation();
	~Animation();
	void load(sf::Sprite& _sprite, std::string _filename, int _n_frames, int w, int h);
	void load(sf::Sprite& _sprite, std::string _filename, int _n_frames, int w, int h, int _directionOffset);
	void load(sf::Sprite& _sprite, sf::Sprite& parent, std::string _filename, int _n_frames, int w, int h);
	void load(sf::Sprite& _sprite, sf::Sprite& parent, std::string _filename, int _n_frames, int w, int h, int _directionOffset);
	void update(sf::Sprite& s, int start, int end);
};

