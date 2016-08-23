#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile()
{
	speed = 50;
	lifetime = 3000;
	hitbox.setSize(sf::Vector2f(5, 5));
	hitbox.setFillColor(sf::Color::Red);
	moveable = 1;
}


Projectile::~Projectile()
{
}

//UPDATE
void Projectile::update()
{
	if (time.getTimeInt() > lifetime)
		kill();
	else if (spawned)
	{
		hitbox.setPosition(sf::Vector2f(body->GetPosition().x * 32, body->GetPosition().y * -32));
		hitbox.setRotation(body->GetAngle() * RAD2DEG);
	}
}

//START CONTACT
void Projectile::startContact(Entity* entity)
{
	entity->getHitbox().setFillColor(sf::Color::Green);
}

//END CONTACT
void Projectile::endContact(Entity* entity)
{
	entity->getHitbox().setFillColor(sf::Color::White);
}

//SPAWN
void Projectile::spawn(float angle, b2Vec2 pos)
{
	spawned = 1;
	body->SetTransform(pos, angle);
	body->SetLinearVelocity(speed * b2Vec2(sin(angle), cos(angle)));
	time.start();
}

//INITIALIZE
void Projectile::initialize(WindowMgr* _window, b2World* _world, float density, float friction, float x, float y)
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
	body->SetBullet(1);

	//shape
	shape = new b2PolygonShape();
	shape->SetAsBox(originOffsetX / 32, originOffsetY / 32);

	//fixture
	fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->filter.categoryBits = EntityType::PROJECTILE;
	fixtureDef->filter.maskBits = EntityType::SCREEN | EntityType::SOLID | EntityType::PROJECTILE;
	fixtureDef->density = density;
	fixtureDef->friction = 5;
	body->CreateFixture(fixtureDef);
}
