#pragma once
#include "Entity.h"
class Actor : public Entity
{
private:
	b2Vec2 forwardVel, backwardVel, leftVel, rightVel;
	bool m_forward, m_backward, m_left, m_right;
	float moveSpeed, sprintSpeed, walkSpeed;
	bool walking, sprinting;
	sf::Vector2f waypoint;
	bool waypointReached;
	void startWaypoint();
	void endWaypoint();

public:
	Actor();
	~Actor();
	void initialize(WindowMgr* _window, b2World* _world, float density, float friction, float x, float y);
	void update();
	void draw();
	void updateMovement();

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
	void setWaypoint(sf::Vector2f _waypoint);
	void updateWaypoint();

	//movement speeds
	void setMovementSpeeds(const float _moveSpeed, const float _sprintSpeed, const float _walkSpeed);
	void setMoveSpeed(float _moveSpeed) { moveSpeed = _moveSpeed; };
	void setSprintSpeed(float _sprintSpeed) { sprintSpeed = _sprintSpeed; };
	void setWalkSpeed(float _walkSpeed) { walkSpeed = _walkSpeed; };
	float getMoveSpeed() { return moveSpeed; };
	float getSprintSpeed() { return sprintSpeed; };
	float getWalkSpeed() { return walkSpeed; };

	void startContact(Entity* entity);
	void endContact(Entity* entity);
};

