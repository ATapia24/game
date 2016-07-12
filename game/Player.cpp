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
}


Player::~Player()
{
}

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

//UPDATE
void Player::update()
{
	if (spawned)
	{
		input();
		hitbox.setPosition(body->GetPosition().x * 32, -body->GetPosition().y * 32);
		sprite.setPosition(hitbox.getPosition());
		hitbox.setRotation(body->GetAngle() * -57.29578f);
		sprite.setRotation(hitbox.getRotation());
		updateAnimations();
	}
}

//DRAW
void Player::draw()
{
	if (spawned)
	{
		window->add(sprite, 0);
		//weapon.setPosition(sf::Vector2f(sprite.getPosition().x - originOffsetX - 5, sprite.getPosition().y - originOffsetY));
		window->add(weapon, 0);
	}
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

//INPUT
void Player::input()
{
	//left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		walkLeft();
	}else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direction == Direction::LEFT)
	{
		stopWalkLeft();
	}

	//right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		walkRight();
	}else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction == Direction::RIGHT)
	{
		stopWalkRight();
	}

	//jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onFloor)
	{
		jump();
	}
}

//WALK RIGHT
void Player::walkRight()
{
	direction = Direction::RIGHT;
	float velChange = walkSpeed - body->GetLinearVelocity().x;
	float impulse = body->GetMass() * velChange;
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), 1);
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
	direction = Direction::LEFT;
	float velChange = -walkSpeed - body->GetLinearVelocity().x;
	float impulse = body->GetMass() * velChange;
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), 1);
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
	float impulse = body->GetMass() * jumpStrength;
	body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), 1);
}

//INITIALIZE
void Player::initialize(WindowMgr* _window, b2World* _world, float density, float friction, float x, float y)
{
	window = _window;
	world = _world;
	type = EntityType::PLAYER;

	//size and origin setup
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, hitbox.getSize().x / sprite.getScale().x, hitbox.getSize().y / sprite.getScale().y));
	originOffsetX = hitbox.getSize().x / 2;
	originOffsetY = hitbox.getSize().y / 2;
	hitbox.setOrigin(originOffsetX, originOffsetY);
	sprite.setOrigin(originOffsetX / sprite.getScale().x, originOffsetY / sprite.getScale().y);

	//def
	bodyDef = new b2BodyDef();
	bodyDef->fixedRotation = true;
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

	//player_body.load(sprite, "assets/player.png", 4, 16, 32);
}