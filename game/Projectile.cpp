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
		hitbox.setRotation(body->GetAngle() * globals::RAD2DEG);
	}
}

//SPAWN
void Projectile::spawn(float angle, b2Vec2 pos)
{
	spawned = 1;
	body->SetTransform(pos, angle);
	body->SetLinearVelocity(speed * b2Vec2(sin(angle), cos(angle)));

	//tmp
	time.start();
	fixtureDef->filter.maskBits = 0x0000;
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

	//shape
	shape = new b2PolygonShape();
	shape->SetAsBox(originOffsetX / 32, originOffsetY / 32);

	//fixture
	fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;

	//properties
	fixtureDef->density = density;
	fixtureDef->friction = 5;
	body->CreateFixture(fixtureDef);
}
