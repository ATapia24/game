#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Map.h"
#include <cmath>
#include "globals.h"

enum PlayerState
{
	walking_left,
	walking_right,
	standng_left,
	standing_right
};

class Player : public Entity {

private:
	PlayerState state;
	sf::Sprite weapon;
	Map* map;

	float walkSpeed;
	float jumpStrength;
	bool onFloor;
	
	//input
	bool q_rel, a_rel, d_rel, b_c, q_rel2, a_rel2, d_rel2, b_c2;

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
	void setMap(Map& _map) { map = &_map; };

	//movement
	void input();
	void walkForward();
	void stopWalkForward();
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

