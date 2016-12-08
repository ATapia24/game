#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Animation.h"
#include "KeyManager.h"
#include "Holdable.h"
#include <cmath>

class Player : public Entity
{

private:
	sf::Sprite weapon;
	Holdable gun;

	float walkSpeed;
	float sprintSpeed;

	//tmp
	Key_M fire, fire2;
	
	//input
	Key keySprint;
	Key keyForward, keyBackward;
	Key keyLeft, keyRight;
	bool m_forward, m_backward, m_left, m_right;
	b2Vec2 forwardVel, backwardVel, leftVel, rightVel;

	//animations
	Animation walk_right, walk_left, stand_right, stand_left;
	Animation lmg_right, lmg_left;
	Animation player_body;
	float viewOffsetY;

	//sensors
	b2Body* screenBody;
	b2BodyDef* screenBodyDef;
	b2PolygonShape* screenShape;
	b2FixtureDef* screenFixture;


	sf::Vector2f screenCenter;
public:
	Player();
	~Player();
	void initialize(WindowMgr* _window, b2World* _world, float density, float friction, float x, float y);
	void update();
	void draw();
	void updateMovement();
	void updateCamera();

	//movement
	void input();
	void walkForward();
	void stopWalkForward();
	void walkBackward();
	void stopWalkBackwards();
	void walkRight();
	void walkLeft();
	void stopWalkRight();
	void stopWalkLeft();
	void diagonalAdjust();
	void sprintAdjust(b2Vec2& vect);

	void startContact(Entity* entity);
	void endContact(Entity* entity);
};

#endif