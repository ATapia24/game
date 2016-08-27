#include "stdafx.h"
#include "Actor.h"


//CONSTRUCTOR
Actor::Actor()
{
	spawnPointX = 0;
	spawnPointY = 0;
	spawned = 0;
	moveable = 1;
	waypointReached = 1;

	m_forward = 0;
	m_backward = 0;
	m_left = 0;
	m_right = 0;

	forwardVel.SetZero();
	backwardVel.SetZero();
	leftVel.SetZero();
	rightVel.SetZero();

	sprintSpeed = 12;
	moveSpeed = 20;
	walkSpeed = 1.2;
}

//DESTRUCTOR
Actor::~Actor()
{
}

//INIT
void Actor::initialize(WindowMgr* _window, b2World* _world, float density, float friction, float x, float y)
{
	window = _window;
	world = _world;
	type = EntityType::PLAYER;

	//size and origin setup
	sprite.setTexture(texture);
	originOffsetX = hitbox.getSize().x / 2;
	originOffsetY = hitbox.getSize().y / 2;
	hitbox.setOrigin(originOffsetX, originOffsetY);
	sprite.setOrigin(originOffsetX / sprite.getScale().x, originOffsetY / sprite.getScale().y);

	//def
	bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	spawnPointX = x;
	spawnPointY = y;
	bodyDef->position.Set(spawnPointX, -spawnPointY);
	body = world->CreateBody(bodyDef);
	body->SetUserData(this);

	//shape
	shape = new b2PolygonShape();
	shape->SetAsBox(originOffsetX / PHYS_SCALE, originOffsetY / PHYS_SCALE);

	//fixture
	fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->filter.categoryBits = EntityType::PLAYER;
	fixtureDef->filter.maskBits = EntityType::SOLID | EntityType::PROJECTILE | EntityType::PLAYER;

	//properties
	fixtureDef->density = density;
	fixtureDef->friction = friction;
	body->CreateFixture(fixtureDef);
}

//UPDATE
void Actor::update()
{
	if (spawned)
		updateMovement();
}

//DRAW
void Actor::draw()
{
	if (spawned)
		window->addWorld(hitbox);

	sf::RectangleShape head;
	head.setSize(sf::Vector2f(5, 5));
	head.setPosition(misc::pointLocation(hitbox.getPosition(), body->GetAngle(), 15));
	head.setRotation(body->GetAngle() * RAD2DEG);
	window->addWorld(head);
}

//UPDATE MOVEMENT
void Actor::updateMovement()
{
	//waypoint
	updateWaypoint();

	//movement
	diagonalAdjust();
	body->SetLinearVelocity(forwardVel + backwardVel + leftVel + rightVel);
	body->SetAngularDamping(10);

	//hitbox and sprite
	hitbox.setPosition(body->GetPosition().x * PHYS_SCALE, -body->GetPosition().y * PHYS_SCALE);
	sprite.setPosition(hitbox.getPosition());
	hitbox.setRotation(body->GetAngle() * -RAD2DEG);
	sprite.setRotation(hitbox.getRotation());
}

//movement
void Actor::input()
{

}

//WALK FORWARD
void Actor::walkForward()
{
	m_forward = 1;
	float angle = body->GetAngle();
	forwardVel = moveSpeed * b2Vec2(cos(body->GetAngle()), sin(body->GetAngle()));
	if (sprinting)
		sprintAdjust(forwardVel);
}

//STOP WALK FORWARD
void Actor::stopWalkForward()
{
	m_forward = 0;
	forwardVel.SetZero();
}

//WALK BACKWARDS
void Actor::walkBackward()
{
	m_backward = 1;
	float angle = body->GetAngle() + PI;
	backwardVel = moveSpeed * b2Vec2(cos(body->GetAngle()), sin(body->GetAngle()));
}

//STOP WALK BACKWARDS
void Actor::stopWalkBackwards()
{
	m_backward = 0;
	backwardVel.SetZero();
}

//WALK RIGHT
void Actor::walkRight()
{
	m_right = 1;
	float angle = body->GetAngle() + PIh;
	b2Vec2 vector = moveSpeed * b2Vec2(cos(body->GetAngle()), sin(body->GetAngle()));
	rightVel = vector;
}

//STOP WALK RIGHT
void Actor::stopWalkRight()
{
	m_right = 0;
	rightVel.SetZero();
}

//WALK LEFT
void Actor::walkLeft()
{
	m_left = 1;
	float angle = body->GetAngle() - PIh;
	leftVel = moveSpeed * b2Vec2(cos(body->GetAngle()), sin(body->GetAngle()));
}

//STOP WALK LEFT
void Actor::stopWalkLeft()
{
	m_left = 0;
	leftVel.SetZero();
}

//SET WAYPOINT
void Actor::setWaypoint(sf::Vector2f _waypoint)
{
	waypoint = _waypoint;
	//startWaypoint();
}

//SET WAYPOINTS
void Actor::setWaypoints(std::vector<sf::Vector2f> _waypoints)
{
	waypointReached = 0;
	waypoints = _waypoints;
	waypoint = waypoints[0];
	startWaypoint();
}



//UPDATE WAYPOINT
void Actor::updateWaypoint()
{
	if (!waypointReached)
	{
		if (misc::distance(waypoint, hitbox.getPosition()) < hitbox.getSize().x / 2)
		{
			if (waypoints.size() <= 1)
			{
				waypointReached = 1;
				stopWalkForward();
				waypoints.clear();
			}
			else
			{
				waypoints.erase(waypoints.begin());
				waypoint = waypoints[0];
				stopWalkForward();
				startWaypoint();
			}
		}
	}
}

//START WAYPOINT
void Actor::startWaypoint()
{
	waypointReached = 0;
	float angle = misc::lineAngle(hitbox.getPosition(), waypoint);
	body->SetTransform(body->GetPosition(), angle);
	walkForward();
}

//CLEAR WAYPOINTS
void Actor::clearWaypoints()
{
	waypointReached = 1;
	waypoints.clear();
}

//DIAGONAL ADJUST
void Actor::diagonalAdjust()
{
	if (m_forward)
	{
		if (m_left)
		{
			leftVel.SetZero();
			float angle = body->GetAngle() + PI7d4;
			forwardVel = walkSpeed * b2Vec2(sin(angle), cos(angle));
			if (sprinting)
				sprintAdjust(forwardVel);
		}
		else if (m_right)
		{
			rightVel.SetZero();
			float angle = body->GetAngle() + PId4;
			forwardVel = walkSpeed * b2Vec2(sin(angle), cos(angle));
			if (sprinting)
				sprintAdjust(forwardVel);
		}
	}
	else if (m_backward)
	{
		if (m_left)
		{
			leftVel.SetZero();
			float angle = body->GetAngle() + PI5d4;
			backwardVel = walkSpeed * b2Vec2(sin(angle), cos(angle));
		}
		else if (m_right)
		{
			rightVel.SetZero();
			float angle = body->GetAngle() + PI3d4;
			backwardVel = walkSpeed * b2Vec2(sin(angle), cos(angle));
		}
	}
}

//SPRINT ADJUST
void Actor::sprintAdjust(b2Vec2& vect)
{

}

//START CONTACT
void Actor::startContact(Entity* entity)
{

}

//END CONTACT
void Actor::endContact(Entity* entity)
{

}

//SET SPEEDS
void Actor::setMovementSpeeds(const float _moveSpeed, const float _sprintSpeed, const float _walkSpeed)
{
	moveSpeed = _moveSpeed;
	sprintSpeed = _sprintSpeed;
	walkSpeed = _walkSpeed;
}
