#include "stdafx.h"
#include "ViewBlocker.h"

ViewBlocker::ViewBlocker()
{
	blockers = new Blocker[max_blockers];
	n_blockers = 0;
	d = 9000;
	containsMovables = 0;
}


ViewBlocker::~ViewBlocker()
{
	delete [] blockers;
}

//UPDATE
void ViewBlocker::update()
{
	center = misc::pointLocation(player->getHitbox().getPosition(), PIh, player->getHitbox().getSize().y / 2);

	//check for new center or roatation or movables
	if (center != lastCenter || player->getHitbox().getRotation() != lastRotation || containsMovables)
		for (unsigned int i = 0; i < n_blockers; i++)
			if(blockers[i].entity->isOneScreen())
				calculateBlocker(blockers[i]);

	//set last
	lastCenter = center;
	lastRotation = player->getHitbox().getRotation();
}

//DRAW
void ViewBlocker::draw()
{
	//draw if on screen
	for (unsigned int i = 0; i <n_blockers; i++)
		if (blockers[i].entity->isOneScreen())
			window->addWorld(blockers[i].shape);
}

//CALCULATE BLOCKER
void ViewBlocker::calculateBlocker(Blocker& blocker)
{

	sf::RectangleShape* hb = &blocker.entity->getHitbox();
	float widthOff = hb->getSize().x / 2;
	float heightOffset = hb->getSize().y / 2;
	sf::Vector2f pos = hb->getPosition();

	//get points
	sf::Vector2f p[4];
	p[0] = sf::Vector2f(pos.x - widthOff, pos.y - heightOffset);
	p[1] = sf::Vector2f(pos.x + widthOff, pos.y - heightOffset);
	p[2] = sf::Vector2f(pos.x - widthOff, pos.y + heightOffset);
	p[3] = sf::Vector2f(pos.x + widthOff, pos.y + heightOffset);


	//sort
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (misc::distance(p[i], center) < misc::distance(p[j], center))
			{
				sf::Vector2f tmp = p[i];
				p[i] = p[j];
				p[j] = tmp;
			}
		}
	}

	//set point
	blocker.shape.setPoint(0, p[1]);

	//set endpoint
	float angle = misc::lineAngle(center, p[1]);
	blocker.shape.setPoint(3, misc::pointLocation(p[0], angle, d));

	//set point and endpoint - determine whethere to use p0 or p2
	if (misc::intersects(center, p[2], p[0], p[1]))
	{
		blocker.shape.setPoint(1, p[0]);
		angle = misc::lineAngle(center, p[0]);
		blocker.shape.setPoint(2, misc::pointLocation(p[0], angle, d));
	}
	else
	{
		blocker.shape.setPoint(1, p[2]);
		angle = misc::lineAngle(center, p[2]);
		blocker.shape.setPoint(2, misc::pointLocation(p[2], angle, d));
	}
}

//SET CENTER
void ViewBlocker::set(Entity& _player, WindowMgr* _window, b2World* _world)
{
	player = &_player;
	window = _window;
	world = _world;
	center = player->getHitbox().getPosition();
}

//ADD OBJECT
void ViewBlocker::addObject(Entity& entity)
{

	blockers[n_blockers].entity = &entity;
	blockers[n_blockers].shape.setFillColor(sf::Color(0, 0, 0, 100));
	blockers[n_blockers].shape.setPointCount(4);
	blockers[n_blockers].shape.setPosition(sf::Vector2f(0, 0));
	n_blockers++;
}