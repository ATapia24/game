#include "Solid.h"


Solid::Solid()
{
	moveable = 0;
	type = EntityType::SOLID;
}


Solid::~Solid()
{
}

//LOAD
void Solid::initialize(WindowMgr* _window, b2World* _world, float density, float friction, float x, float y)
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
	hitbox.setFillColor(sf::Color(200, 200, 200, 255));
	bodyDef = new b2BodyDef();

	//static
	this->bodyDef->type = b2_staticBody;

	//pos
	spawnPointX = x;
	spawnPointY = y;
	hitbox.setPosition(x, y);
	sprite.setPosition(x, y);

	//def
	bodyDef->position.Set(x / PHYS_SCALE, y / -PHYS_SCALE);
	body = world->CreateBody(bodyDef);
	body->SetUserData(this);

	//shape
	shape = new b2PolygonShape();
	shape->SetAsBox(originOffsetX / PHYS_SCALE, originOffsetY / PHYS_SCALE);

	//fixture
	fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->filter.categoryBits = EntityType::SOLID;
	fixtureDef->filter.maskBits = EntityType::PROJECTILE | EntityType::SCREEN | EntityType::PLAYER;
	body->CreateFixture(fixtureDef);

	std::cout << hitbox.getPosition().x << ' ' << hitbox.getPosition().y << '\n';
}