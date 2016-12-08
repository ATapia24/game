#include "Entity.h"


Entity::Entity()
{
	spawnPointX = 0;
	spawnPointY = 0;
	spawned = 0;
	moveable = 1;
	killed = 0;
	onScreen = 0;
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
	sprite.setTextureRect(sf::IntRect(0, 0, (int)(hitbox.getSize().x / sprite.getScale().x), (int)(hitbox.getSize().y / (int)sprite.getScale().y)));
	originOffsetX = hitbox.getSize().x / 2;
	originOffsetY = hitbox.getSize().y / 2;
	hitbox.setOrigin(originOffsetX, originOffsetY);
	sprite.setOrigin(originOffsetX / sprite.getScale().x, originOffsetY / sprite.getScale().y);
	bodyDef = new b2BodyDef();
	
	//dynamic or static
	if (moveable)
		bodyDef->type = b2_dynamicBody;
	else
		bodyDef->type = b2_staticBody;

	//pos
	spawnPointX = x;
	spawnPointY = y;
	bodyDef->position.Set(spawnPointX, spawnPointY);

	//def
	bodyDef->position.Set(x / PHYS_SCALE, y / PHYS_SCALE);
	body = world->CreateBody(bodyDef);
	body->SetUserData(this);

	//shape
	shape = new b2PolygonShape();
	shape->SetAsBox(originOffsetX / 32, originOffsetY / 32);

	//fixture
	fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;

	//properties
	if (moveable)
	{
		fixtureDef->density = density;
		fixtureDef->friction = friction;
	}

	body->CreateFixture(fixtureDef);
}

//UPDATE
void Entity::update()
{
	if (spawned)
	{
		input();

		hitbox.setPosition(body->GetPosition().x * PHYS_SCALE, -body->GetPosition().y * PHYS_SCALE);
		sprite.setPosition(hitbox.getPosition());
		hitbox.setRotation(body->GetAngle() * RAD2DEG);
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

	if (spawned && onScreen)
	{
		window->addWorld(hitbox);
		//window->addWorld(sprite);
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
	bodyDef->position.Set(spawnPointX, -spawnPointY);
}

//kill
void Entity::kill()
{
	spawned = 0;
	killed = 1;
}

//WAS KILLED
bool Entity::wasKilled()
{
	return killed;
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