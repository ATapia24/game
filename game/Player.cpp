#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	spawnPointX = 0;
	spawnPointY = 0;
	spawned = 0;
	moveable = 1;

	//tmp
	player_body.load(sprite, "assets/player.png", 8, 16, 32);
	
	//weapon
	weapon.setScale(3, 3);
	texture.loadFromFile("assets/player.png");
	texture.setSmooth(true);
	hitbox.setFillColor(sf::Color::Magenta);
	
	//stats
	walkSpeed = 8;
	jumpStrength = 4;
	direction = Direction::RIGHT;

	sprite.setOrigin(sf::Vector2f(hitbox.getSize().x / 2, hitbox.getSize().y / 2));
	viewOffsetY = 400;
	
	//tmp
	hitbox.setRotation(0);
}


Player::~Player()
{
}


//UPDATE
void Player::update()
{
	if (spawned)
	{
		//input();
		updateMovement();
		//updateAnimations();
		//updateCamera();
	}
}

//DRAW
void Player::draw()
{
	if (spawned)
	{
		//window->addWorld(sprite);
		window->addWorld(hitbox);
	}
}
//UPDATE MOVEMENT
void Player::updateMovement()
{
	//mouse rotation - reset on full rotation (radians)
	float rotation = body->GetAngle() + ((600 - (float)sf::Mouse::getPosition().x) * -0.001f);
	//sf::Mouse::setPosition(sf::Vector2i(600, 600));
	rotation > globals::PI2 ? rotation = 0: rotation;
	rotation < 0 ? rotation = globals::PI2 : rotation;
	//update pos/rot
	body->SetTransform(body->GetPosition(), body->GetAngle());
	//del^^body->SetTransform(body->GetPosition(), rotation); 
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

//START CONTACT
void Player::startContact(Entity* entity)
{
	onFloor = 1;
	entity->getSprite().setColor(sf::Color::Red);
}

//END CONTACT
void Player::endContact(Entity* entity)
{
	onFloor = 0;
	entity->getSprite().setColor(sf::Color::White);
}

//WALK FORWARD
void Player::walkForward()
{
	float angle = body->GetAngle();
	b2Vec2 vector = walkSpeed * b2Vec2(sin(angle), cos(angle));
	body->SetLinearVelocity(vector);
}

//STOP WALK FORWARD
void Player::stopWalkForward()
{
	float angle = body->GetAngle();
	b2Vec2 vector = -walkSpeed * b2Vec2(sin(angle), cos(angle));
	body->SetLinearVelocity(vector);
}

//WALK RIGHT
void Player::walkRight()
{
	float velChange = walkSpeed - body->GetLinearVelocity().x;
	float impulse = body->GetMass() * velChange;
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), 1);
	direction = Direction::RIGHT;
	state = PlayerState::walking_right;
}

//STOP WALK RIGHT
void Player::stopWalkRight()
{
	float velChange = -body->GetLinearVelocity().x;
	float impulse = body->GetMass() * velChange;
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), 1);
	state = PlayerState::standing_right;
}

//WALK LEFT
void Player::walkLeft()
{
	float velChange = -walkSpeed - body->GetLinearVelocity().x;
	float impulse = body->GetMass() * velChange;
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), 1);
	direction = Direction::LEFT;
	state = PlayerState::walking_left;
}

//STOP WALK LEFT
void Player::stopWalkLeft()
{
	float velChange = -body->GetLinearVelocity().x;
	float impulse = body->GetMass() * velChange;
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), 1);
	state = PlayerState::standng_left;
}

//JUMP
void Player::jump()
{

}

//INPUT
void Player::input()
{
	//forward
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		walkForward();
	}

	/*
	//left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		walkLeft();
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direction == Direction::LEFT)
	{
		stopWalkLeft();
	}

	//right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		walkRight();
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction == Direction::RIGHT)
	{
		stopWalkRight();
	}

	//jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onFloor)
	{
		jump();
	}
	*/
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