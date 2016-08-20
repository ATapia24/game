#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	spawnPointX = 0;
	spawnPointY = 0;
	spawned = 0;
	moveable = 1;
	
	//hitbox.setTexture(&texture);
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.25f, 0.25f));
	
	//stats
	walkSpeed = 12;
	sprintSpeed = 1.5;

	//input
	keyForward.set(sf::Keyboard::W, KeyType::REPEATED);
	keyBackward.set(sf::Keyboard::S, KeyType::REPEATED);
	keyLeft.set(sf::Keyboard::A, KeyType::REPEATED);
	keyRight.set(sf::Keyboard::D, KeyType::REPEATED);
	keySprint.set(sf::Keyboard::LShift, KeyType::REPEATED);
	fire.set(sf::Mouse::Button::Left, KeyType::SINGLE);

	sprite.setOrigin(sf::Vector2f(hitbox.getSize().x / 2, hitbox.getSize().y / 2));
	viewOffsetY = 400;
	
	//tmp
	hitbox.setRotation(0);
	m_forward = 0;
	m_backward = 0;
	m_left = 0;
	m_right = 0;

	forwardVel.SetZero();
	backwardVel.SetZero();
	leftVel.SetZero();
	rightVel.SetZero();
}


Player::~Player()
{
}


//UPDATE
void Player::update()
{
	if (spawned)
	{
		input();
		updateMovement();
		gun.update();
		//updateAnimations();
		updateCamera();
	}
}

//DRAW
void Player::draw()
{
	if (spawned)
	{
		window->addWorld(hitbox);
		window->addWorld(sprite);
		gun.draw();
	}
}
//UPDATE MOVEMENT
void Player::updateMovement()
{
	//tmp reset pos
	if (fire.getValue())
		gun.fire(body->GetAngle(), body->GetPosition());


	//movement
	diagonalAdjust();
	body->SetLinearVelocity(forwardVel + backwardVel + leftVel + rightVel);

	//mouse rotation - reset on full rotation (radians)
	float rotation = body->GetAngle() + ((600 - (float)sf::Mouse::getPosition().x) * -0.0005f);
	sf::Mouse::setPosition(sf::Vector2i(600, 500));
	rotation > PI2 ? rotation = 0: rotation;
	rotation < 0 ? rotation = PI2 : rotation;
	
	//update pos/rot
	body->SetFixedRotation(0);
	body->SetTransform(body->GetPosition(), rotation); 
	body->SetFixedRotation(1);
	hitbox.setPosition(body->GetPosition().x * 32, -body->GetPosition().y * 32);
	sprite.setPosition(hitbox.getPosition());
	hitbox.setRotation(body->GetAngle() * RAD2DEG);
	sprite.setRotation(hitbox.getRotation());

}

//UPDATE CAMERA
void Player::updateCamera()
{
	//calculate pos: x = offset * sin(rotation), y = offset * cos(rotation)
	window->getWorldView()->setCenter(sf::Vector2f((hitbox.getPosition().x  + (viewOffsetY * sin(hitbox.getRotation() * DEG2RAD)))* window->getScale().x, ((hitbox.getPosition().y) - (viewOffsetY * cos(hitbox.getRotation() * DEG2RAD))) * window->getScale().y));
	window->getWorldView()->setRotation(body->GetAngle() * RAD2DEG);
}

//WALK FORWARD
void Player::walkForward()
{
	m_forward = 1;
	float angle = body->GetAngle();
	forwardVel = walkSpeed * b2Vec2(sin(angle), cos(angle));
	if (keySprint.getValue())
		sprintAdjust(forwardVel);
}

//STOP WALK FORWARD
void Player::stopWalkForward()
{
	m_forward = 0;
	forwardVel.SetZero();
}

//WALK BACKWARDS
void Player::walkBackward()
{
	m_backward = 1;
	float angle = body->GetAngle() + PI;
	backwardVel = walkSpeed * b2Vec2(sin(angle), cos(angle));
}

//STOP WALK BACKWARDS
void Player::stopWalkBackwards()
{
	m_backward = 0;
	backwardVel.SetZero();
}

//WALK RIGHT
void Player::walkRight()
{
	m_right = 1;
	float angle = body->GetAngle() + PIh;
	b2Vec2 vector = walkSpeed * b2Vec2(sin(angle), cos(angle));
	rightVel = vector;
}

//STOP WALK RIGHT
void Player::stopWalkRight()
{
	m_right = 0;
	rightVel.SetZero();
}

//WALK LEFT
void Player::walkLeft()
{
	m_left = 1;
	float angle = body->GetAngle() - PIh;
	leftVel = walkSpeed * b2Vec2(sin(angle), cos(angle));
}

//STOP WALK LEFT
void Player::stopWalkLeft()
{
	m_left = 0;
	leftVel.SetZero();
}

//DIAGONAL ADJUST
void Player::diagonalAdjust()
{
	if (m_forward)
	{
		if (m_left)
		{
			leftVel.SetZero();
			float angle = body->GetAngle() + PI7d4;
			forwardVel = walkSpeed * b2Vec2(sin(angle), cos(angle));
			if (keySprint.getValue())
				sprintAdjust(forwardVel);
		}
		else if ( m_right)
		{
			rightVel.SetZero();
			float angle = body->GetAngle() + PId4;
			forwardVel = walkSpeed * b2Vec2(sin(angle), cos(angle));
			if (keySprint.getValue())
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
void Player::sprintAdjust(b2Vec2& vect)
{
	vect *= sprintSpeed;
}

//JUMP
void Player::jump()
{

}

//INPUT
void Player::input()
{
	//forward
	if (keyForward.getValue())
		walkForward();
	else if (m_forward && !keyForward.getValue())
		stopWalkForward();

	//backward
	if (keyBackward.getValue())
		walkBackward();
	else if (m_backward && !keyBackward.getValue())
		stopWalkBackwards();

	//left
	if (keyLeft.getValue())
		walkLeft();
	else if (m_left && !keyLeft.getValue())
		stopWalkLeft();

	//right
	if (keyRight.getValue())
		walkRight();
	else if (m_right && !keyRight.getValue())
		stopWalkRight();
}


//INITIALIZE
void Player::initialize(WindowMgr* _window, b2World* _world, float density, float friction, float x, float y)
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
	bodyDef->position.Set(spawnPointX, spawnPointY);
	body = world->CreateBody(bodyDef);
	body->SetUserData(this);

	//shape
	shape = new b2PolygonShape();
	shape->SetAsBox(originOffsetX / 32, originOffsetY / 32);

	//fixture
	fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->filter.categoryBits = EntityType::PLAYER;
	fixtureDef->filter.maskBits = 0x0000;

	//properties
	fixtureDef->density = density;
	fixtureDef->friction = friction;
	body->CreateFixture(fixtureDef);

	gun.load(window, world);
}

//UPDATE ANIMATIONS
void Player::updateAnimations()
{
	switch (state)
	{
	case PlayerState::walking_right:
		player_body.update(sprite, 1, 4);
		break;

	case PlayerState::walking_left:
		player_body.update(sprite, 5, 8);
		break;

	case PlayerState::standing_right:
		player_body.update(sprite, 1, 1);
		break;

	case PlayerState::standng_left:
		player_body.update(sprite, 8, 8);
		break;
	}
}

//START CONTACT
void Player::startContact(Entity* entity)
{
	entity->getSprite().setColor(sf::Color::Red);
}

//END CONTACT
void Player::endContact(Entity* entity)
{
	entity->getSprite().setColor(sf::Color::White);
}