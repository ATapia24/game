#include "stdafx.h"
#include "ViewBlocker.h"


ViewBlocker::ViewBlocker()
{
}


ViewBlocker::~ViewBlocker()
{
}

//UPDATE
void ViewBlocker::update()
{
	center = player->getHitbox().getPosition();

	for (unsigned int i = 0; i < blockers.size(); i++)
		calculateBlocker(blockers[i]);
}

//DRAW
void ViewBlocker::draw()
{
	for (unsigned int i = 0; i < blockers.size(); i++)
		window->addWorld(blockers[i]->shape);
}

//CALCULATE BLOCKER
void ViewBlocker::calculateBlocker(Blocker* blocker)
{

	sf::RectangleShape* hb = &blocker->entity->getHitbox();
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

	blocker->shape.setPoint(0, p[1]);
	int d = 1920;
	float angle2;
	if (misc::intersects(center, p[2], p[0], p[1]))
	{
		blocker->shape.setPoint(1, p[0]);
		angle2 = ((atan2f((-center.y + p[0].y), (center.x - p[0].x)))) + globals::PI;
		blocker->shape.setPoint(2, sf::Vector2f(p[0].x + d * cos(angle2), p[0].y + -d * sin(angle2)));
	}
	else
	{
		blocker->shape.setPoint(1, p[2]);
		angle2 = ((atan2f((-center.y + p[2].y), (center.x - p[2].x)))) + globals::PI;
		blocker->shape.setPoint(2, sf::Vector2f(p[2].x + d * cos(angle2), p[2].y + -d * sin(angle2)));
	}

	float angle1 = ((atan2f((-center.y + p[1].y), (center.x - p[1].x)))) + globals:: PI;
	blocker->shape.setPoint(3, sf::Vector2f(p[1].x + d * cos(angle1), p[1].y + -d * sin(angle1)));
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
	Blocker* b = new Blocker;
	b->entity = &entity;
	b->shape.setFillColor(sf::Color::White);
	b->shape.setPointCount(4);
	b->shape.setPosition(sf::Vector2f(0, 0));
	blockers.push_back(b);
}