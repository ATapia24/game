#include "stdafx.h"
#include "ViewBlocker.h"

ViewBlocker::ViewBlocker()
{
	blockers = new Blocker[max_blockers];
	n_blockers = 0;
	d = 9000;
	containsMovables = 0;
	points = new sf::Vector2f[10000000];
	pcount = 0;
}


ViewBlocker::~ViewBlocker()
{
	delete[] blockers;
}

//UPDATE
void ViewBlocker::update()
{
	center = misc::pointLocation(player->getHitbox().getPosition(), PIh, player->getHitbox().getSize().y / 2);

	//check for new center or roatation or movables
	if (center != lastCenter || player->getHitbox().getRotation() != lastRotation || containsMovables)
	{
		pcount = 0;
		newUpdate = 1;
		for (int i = 0; i < n_blockers; i++)
		{
			if (blockers[i].entity->isOneScreen())
				calculateBlocker(blockers[i]);
		}
	}

	//set last
	lastCenter = center;
	lastRotation = player->getHitbox().getRotation();
}

//DRAW
void ViewBlocker::draw()
{
	if (newUpdate)
	{
		va.resize(pcount);
		for (int i = 0; i < pcount; i++)
		{
			va[i] = points[i];
			va[i].color = sf::Color::Red;
		}
		newUpdate = 0;
	}

	window->addWorld(va, points);
}

//CALCULATE BLOCKER
void ViewBlocker::calculateBlocker(Blocker& blocker)
{
	//get points
	float widthOff = blocker.entity->getHitbox().getSize().x / 2;
	float heightOffset = blocker.entity->getHitbox().getSize().y / 2;

	//get body points
	sf::Vector2f p[4];
	p[0] = sf::Vector2f(blocker.entity->getHitbox().getPosition().x - widthOff, blocker.entity->getHitbox().getPosition().y - heightOffset);
	p[1] = sf::Vector2f(blocker.entity->getHitbox().getPosition().x + widthOff, blocker.entity->getHitbox().getPosition().y - heightOffset);
	p[2] = sf::Vector2f(blocker.entity->getHitbox().getPosition().x - widthOff, blocker.entity->getHitbox().getPosition().y + heightOffset);
	p[3] = sf::Vector2f(blocker.entity->getHitbox().getPosition().x + widthOff, blocker.entity->getHitbox().getPosition().y + heightOffset);

	//sort body points by distance ascending order
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (misc::distance(p[i], center) < misc::distance(p[j], center))
			{
				sf::Vector2f tmp = p[i];
				p[i] = p[j];
				p[j] = tmp;
			}

	//calc triangle bottom points
	sf::Vector2f bp1, bp2;
	if (misc::intersects(p[0], p[1], center, p[2]))
	{
			bp1 = p[0];
			bp2 = p[1];
	}
	else
	{
		if (misc::intersects(center, p[1], p[0], p[2]))
		{
			bp1 = p[0];
			bp2 = p[2];
		}
		else
		{
			bp1 = p[1];
			bp2 = p[2];
		}
	}

	//calc triangle top points
	sf::Vector2f tip1 = misc::pointLocation(bp1, misc::lineAngle(center, bp1), 60000);
	sf::Vector2f tip2 = misc::pointLocation(bp1, misc::lineAngle(center, bp2), 60000);

	//setup triangle
	points[0 + pcount] = bp1;
	points[1 + pcount] = tip1;
	points[2 + pcount] = tip2;
	points[3 + pcount] = bp2;
	points[4 + pcount] = bp1;
	points[5 + pcount] = tip2;
	pcount += 6;

	//set blocker points (for in shadow function?)
	blocker.points[0] = tip1;
	blocker.points[1] = tip2;
	blocker.points[2] = bp2;
	blocker.points[3] = bp1;

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
	n_blockers++;
}