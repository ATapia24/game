#pragma once
#include "Entity.h"
#include "Animation.h"
#include "KeyManager.h"
#include <cmath>
#include "globals.h"

enum PlayerState
{
	walking_left,
	walking_right,
	standng_left,
	standing_right
};

class Player : public Entity
{

private:
	PlayerState state;
	sf::Sprite weapon;

	float walkSpeed;
	float jumpStrength;
	bool moved;
	//tmp
	Key_M reset;
	
	//input
	Key keyForward, keyBackward;
	Key keyLeft, keyRight;
	bool m_forward, m_backward, m_left, m_right;
	b2Vec2 forwardVel, backwardVel, leftVel, rightVel;
	//animations
	void updateAnimations();
	Animation walk_right, walk_left, stand_right, stand_left;
	Animation lmg_right, lmg_left;
	Animation player_body;
	float viewOffsetY;

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
	void jump();

	//state
	PlayerState getState() { return state; }
	void setState(PlayerState _state) { state = _state; }

	void startContact(Entity* entity);
	void endContact(Entity* entity);
};

