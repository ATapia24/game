#include "Animation.h"


Animation::Animation()
{
}


Animation::~Animation()
{
}


//LOAD
void Animation::load(sf::Sprite& _sprite, std::string _filename, int _n_frames, int w, int h)
{
	sprite = &_sprite;
	parent = nullptr;
	filename = _filename;
	texture.loadFromFile(filename);
	n_frames = _n_frames;
	width = w;
	height = h;
	directionOffset = 0;
	xFrame = 0;
	yFrame = 0;
	frameSpeed = 75;
	timer.start();
	frameCount = 0;
	n_frames < 4 ? col = n_frames : col = 4;

	row = (n_frames / col) - 1;
}

//LOAD W/ DIRECTION OFFSET
void Animation::load(sf::Sprite& _sprite, std::string _filename, int _n_frames, int w, int h, int _directionOffset)
{
	sprite = &_sprite;
	parent = nullptr;
	filename = _filename;
	texture.loadFromFile(filename);
	n_frames = _n_frames;
	width = w;
	height = h;
	directionOffset = _directionOffset;
	xFrame = 0;
	yFrame = 0;
	frameSpeed = 75;
	timer.start();
	frameCount = 0;
	n_frames < 4 ? col = n_frames : col = 4;

	row = (n_frames / col) - 1;
}

//LOAD W/ PARENT
void Animation::load(sf::Sprite& _sprite, sf::Sprite& _parent, std::string _filename, int _n_frames, int w, int h)
{
	sprite = &_sprite;
	parent = &_parent;
	filename = _filename;
	texture.loadFromFile(filename);
	n_frames = _n_frames;
	width = w;
	height = h;
	directionOffset = 0;
	xFrame = 0;
	yFrame = 0;
	frameSpeed = 75;
	timer.start();
	frameCount = 0;
	n_frames < 4 ? col = n_frames : col = 4;

	row = (n_frames / col) - 1;
}

//LOAD W/ PARENT & DIRECTION OFFSET
void Animation::load(sf::Sprite& _sprite, sf::Sprite& _parent, std::string _filename, int _n_frames, int w, int h, int _directionOffset)
{
	sprite = &_sprite;
	parent = &_parent;
	filename = _filename;
	texture.loadFromFile(filename);
	n_frames = _n_frames;
	width = w;
	height = h;
	directionOffset = _directionOffset;
	xFrame = 0;
	yFrame = 0;
	frameSpeed = 75;
	timer.start();
	frameCount = 0;
	n_frames < 4 ? col = n_frames : col = 4;

	row = (n_frames / col) - 1;
}

//UPDATE
void Animation::update(sf::Sprite& s, int start, int end)
{


}