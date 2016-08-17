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
	walkSpeed = 8;
	jumpStrength = 4;

	//input
	keyForward.set(sf::Keyboard::W, KeyType::REPEATED);
	keyBackward.set(sf::Keyboard::S, KeyType::REPEATED);
	keyLeft.set(sf::Keyboard::A, KeyType::REPEATED);
	keyRight.set(sf::Keyboard::D, KeyType::REPEATED);
	reset.set(sf::Mouse::Button::Left, KeyType::REPEATED);

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
	}
}
//UPDATE MOVEMENT
void Player::updateMovement()
{
	//tmp reset pos
	if (reset.getValue())
		body->SetTransform(b2Vec2(0, 0), 0);

	if (m_forward && m_left)
	{
	}

	body->SetLinearVelocity(forwardVel + backwardVel + leftVel + rightVel);
	std::cout << body->GetLinearVelocity().Length() << ' ' << body->GetLinearVelocity().x << ' ' << body->GetLinearVelocity().y << '\n';

	//mouse rotation - reset on full rotation (radians)
	float rotation = body->GetAngle() + ((600 - (float)sf::Mouse::getPosition().x) * -0.001f);
	sf::Mouse::setPosition(sf::Vector2i(600, 500));
	rotation > globals::PI2 ? rotation = 0: rotation;
	rotation < 0 ? rotation = globals::PI2 : rotation;
	
	//update pos/rot
	body->SetTransform(body->GetPosition(), rotation); 
	hitbox.setPosition(body->GetPosition().x * 32, -body->GetPosition().y * 32);
	sprite.setPosition(hitbox.getPosition());
	hitbox.setRotation(body->GetAngle() * globals::RAD2DEG);
	sprite.setRotation(hitbox.getRotation());
}

//UPDATE CAMERA
void Player::updateCamera()
{
	//calculate pos: x = offset * sin(rotation), y = offset * cos(rotation)
	window->getWorldView()->setCenter(sf::Vector2f((hitbox.getPosition().x  + (viewOffsetY * sin(hitbox.getRotation() * globals::DEG2RAD)))* window->getScale().x, ((hitbox.getPosition().y) - (viewOffsetY * cos(hitbox.getRotation() * globals::DEG2RAD))) * window->getScale().y));
	window->getWorldView()->setRotation(body->GetAngle() * globals::RAD2DEG);
}

//WALK FORWARD
void Player::walkForward()
{
	m_forward = 1;
	float angle = body->GetAngle();
	b2Vec2 vector = walkSpeed * b2Vec2(sin(angle), cos(angle));
	forwardVel = vector;
	//body->SetLinearVelocity(vector);
}

//STOP WALK FORWARD
void Player::stopWalkForward()
{
	m_forward = 0;
	//body->SetLinearVelocity(body->GetLinearVelocity() - forwardVel);
	forwardVel.SetZero();
}

//WALK BACKWARDS
void Player::walkBackward()
{
	m_backward = 1;
	float angle = body->GetAngle() + globals::PI;
	b2Vec2 vector = walkSpeed * b2Vec2(sin(angle), cos(angle));
	backwardVel = vector;
	//body->SetLinearVelocity(vector);
}

//STOP WALK BACKWARDS
void Player::stopWalkBackwards()
{
	m_backward = 0;
	//body->SetLinearVelocity(body->GetLinearVelocity() - backwardVel);
	backwardVel.SetZero();
}

//WALK RIGHT
void Player::walkRight()
{
	m_right = 1;
	float angle = body->GetAngle() + globals::PIh;
	b2Vec2 vector = walkSpeed * b2Vec2(sin(angle), cos(angle));
	rightVel = vector;
	//body->SetLinearVelocity(vector);
}

//STOP WALK RIGHT
void Player::stopWalkRight()
{
	m_right = 0;
	//body->SetLinearVelocity(body->GetLinearVelocity() - rightVel);
	rightVel.SetZero();
}

//WALK LEFT
void Player::walkLeft()
{
	m_left = 1;
	float angle = body->GetAngle() - globals::PIh;
	b2Vec2 vector = walkSpeed * b2Vec2(sin(angle), cos(angle));
	leftVel = vector;
	//body->SetLinearVelocity(vector);
}

//STOP WALK LEFT
void Player::stopWalkLeft()
{
	m_left = 0;
	//body->SetLinearVelocity(body->GetLinearVelocity() - leftVel);
	leftVel.SetZero();
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
	//sprite.setTextureRect(sf::IntRect(0, 0, (int)(hitbox.getSize().x / sprite.getScale().x, hitbox.getSize().y / sprite.getScale().y));
	originOffsetX = hitbox.getSize().x / 2;
	originOffsetY = hitbox.getSize().y / 2;
	hitbox.setOrigin(originOffsetX, originOffsetY);
	sprite.setOrigin(originOffsetX / sprite.getScale().x, originOffsetY / sprite.getScale().y);

	//def
	bodyDef = new b2BodyDef();
	//bodyDef->fixedRotation = true;
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
	fixtureDef->shape = this->shape;

	//properties
	fixtureDef->density = density;
	fixtureDef->friction = friction;
	body->CreateFixture(this->fixtureDef);
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