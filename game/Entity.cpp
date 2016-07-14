#include "stdafx.h"
#include "Entity.h"


Entity::Entity()
{
	
	spawnPointX = 0;
	spawnPointY = 0;
	spawned = 0;
	moveable = 1;
}


Entity::~Entity()
{
	unload();
}

Entity::Entity(WindowMgr* _window)
{
	window = _window;
}

//LOAD
void Entity::initialize(WindowMgr* _window, b2World* _world, float density, float friction, float x, float y)
{
	window = _window;
	world = _world;

	//size and origin setup
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, hitbox.getSize().x / sprite.getScale().x, hitbox.getSize().y / sprite.getScale().y));
	originOffsetX = hitbox.getSize().x / 2;
	originOffsetY = hitbox.getSize().y / 2;
	hitbox.setOrigin(originOffsetX, originOffsetY);
	sprite.setOrigin(originOffsetX / sprite.getScale().x, originOffsetY / sprite.getScale().y);

	this->bodyDef = new b2BodyDef();
	
	//dynamic or tsatic
	if (moveable)
	{
		this->bodyDef->type = b2_dynamicBody;
	}
	else
	{
		this->bodyDef->type = b2_staticBody;
	}

	//def
	spawnPointX = x;
	spawnPointY = y;
	this->bodyDef->position.Set(spawnPointX, spawnPointY);
	this->body = this->world->CreateBody(this->bodyDef);
	body->SetUserData(this);

	//shape
	this->shape = new b2PolygonShape();
	this->shape->SetAsBox(originOffsetX / 32, originOffsetY / 32);

	//fixture
	this->fixtureDef = new b2FixtureDef();
	this->fixtureDef->shape = this->shape;

	//properties
	if (moveable)
	{
		this->fixtureDef->density = density;
		this->fixtureDef->friction = friction;
		this->body->CreateFixture(this->fixtureDef);
	}
	else
	{
		this->body->CreateFixture(this->shape, 0);
	}

}

//UPDATE
void Entity::update()
{
	if (spawned)
	{
		input();

		hitbox.setPosition(body->GetPosition().x * 32, -body->GetPosition().y * 32);
		sprite.setPosition(hitbox.getPosition());
		hitbox.setRotation(body->GetAngle() * -57.29578f);
		sprite.setRotation(hitbox.getRotation());
	}
}

//START CONTACT
void Entity::startContact(Entity* entity)
{

}

//END CONTACT
void Entity::endContact(Entity* entity)
{

}


void Entity::updateAnimations()
{

}

//DRAW
void Entity::draw()
{
	if (spawned)
	{
		window->addWorld(hitbox);
		window->addWorld(sprite);
	}
}

//INPUT
void Entity::input()
{

}

//GET SPRITE
sf::Sprite& Entity::getSprite()
{
	return sprite;
}

//GET TEXTURE
sf::Texture& Entity::getTexture()
{
	return texture;
}

//WALK RIGHT
void Entity::walkRight()
{

}

//STOP WALK RIGHT
void Entity::stopWalkRight()
{

}

//WALK LEFT
void Entity::walkLeft()
{

}

//STOP WALK LEFT
void Entity::stopWalkLeft()
{

}

//SPAWN
void Entity::spawn()
{
	spawned = 1;
	bodyDef->position.Set(spawnPointX, spawnPointY);
}

//kill
void Entity::kill()
{
	spawned = 0;
}

//IS ALIVE
bool Entity::isAlive()
{
	return spawned;
}

//IS MOVEABLE
bool Entity::isMoveable()
{
	return moveable;
}

//SET MOVEABLE
void Entity::setMoveable(bool _moveable)
{
	moveable = _moveable;
}

//SET NAME
void Entity::setName(std::string _name)
{
	name = _name;
}

//GET NAME
std::string Entity::getName()
{
	return name;
}

//UNLOAD
void Entity::unload()
{
	delete bodyDef;
	delete shape;
	delete fixtureDef;
}