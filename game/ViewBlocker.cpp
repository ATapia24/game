#include "stdafx.h"
#include "ViewBlocker.h"

ViewBlocker::ViewBlocker()
{
	blockers = new Blocker[max_blockers];
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
	center = misc::pointLocation(player->getHitbox().getPosition(), -player->getBody()->GetAngle() + PIh, player->getHitbox().getSize().y/3);

	//check for new center or roatation or movables
	if (center != lastCenter || player->getHitbox().getRotation() != lastRotation || containsMovables)
	{
		pcount = 0;
		newUpdate = 1;
		for (int i = 0; i < n_blockers; i++)
			if (blockers[i].entity->isOneScreen())
				calculateBlocker(blockers[i]);
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
			va[i] = points[i];
		newUpdate = 0;
	}

	window->addWorld(va, points);
}

//CALCULATE BLOCKER
void ViewBlocker::calculateBlocker(Blocker& blocker)
{
	//get body points
	sf::Vector2f p[4];
	p[0] = sf::Vector2f(blocker.entity->getHitbox().getPosition().x - blocker.widthOffset, blocker.entity->getHitbox().getPosition().y - blocker.heightOffset);
	p[1] = sf::Vector2f(blocker.entity->getHitbox().getPosition().x + blocker.widthOffset, blocker.entity->getHitbox().getPosition().y - blocker.heightOffset);
	p[2] = sf::Vector2f(blocker.entity->getHitbox().getPosition().x - blocker.widthOffset, blocker.entity->getHitbox().getPosition().y + blocker.heightOffset);
	p[3] = sf::Vector2f(blocker.entity->getHitbox().getPosition().x + blocker.widthOffset, blocker.entity->getHitbox().getPosition().y + blocker.heightOffset);

	//sort body points by distance ascending order
	sf::Vector2f tmp;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (misc::distance(p[i], center) < misc::distance(p[j], center))
			{
				tmp = p[i];
				p[i] = p[j];
				p[j] = tmp;
			}
			j == i-1 ? j++ : j;
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

	//setup triangle in points array
	points[0 + pcount] = bp1;
	points[1 + pcount] = tip1;
	points[2 + pcount] = tip2;
	points[3 + pcount] = bp2;
	points[4 + pcount] = bp1;
	points[5 + pcount] = tip2;
	pcount += 6;
}

//IN SHADOW
bool ViewBlocker::inShadow(const Blocker& blocker)
{
	sf::Vector2f poly[4];
	int adj = 0;

	sf::Vector2f p[4];
	float widthOff = blocker.entity->getHitbox().getSize().x / 2;
	float heightOffset = blocker.entity->getHitbox().getSize().y / 2;
	p[0] = sf::Vector2f(blocker.entity->getHitbox().getPosition().x - widthOff, blocker.entity->getHitbox().getPosition().y - heightOffset);
	p[1] = sf::Vector2f(blocker.entity->getHitbox().getPosition().x + widthOff, blocker.entity->getHitbox().getPosition().y - heightOffset);
	p[2] = sf::Vector2f(blocker.entity->getHitbox().getPosition().x - widthOff, blocker.entity->getHitbox().getPosition().y + heightOffset);
	p[3] = sf::Vector2f(blocker.entity->getHitbox().getPosition().x + widthOff, blocker.entity->getHitbox().getPosition().y + heightOffset);

	for (int i = 0; i < n_blockers; i++)
	{
		poly[0] = points[0 + adj];
		poly[0] = points[1 + adj];
		poly[0] = points[2 + adj];
		poly[0] = points[3 + adj];
		adj++;

		for (int j = 0; j < 4; j++)
		{
			if (!misc::inPolygon(p[i], poly, 4))
			{
				return 0;
			}
		}

	}

	std::cout << "in shadow\n";
	return 1;
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
	blockers[n_blockers].widthOffset = entity.getHitbox().getSize().x / 2;
	blockers[n_blockers].heightOffset = entity.getHitbox().getSize().y / 2;
	n_blockers++;
}