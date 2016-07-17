#include "stdafx.h"
#include "StageDev.h"

StageDev::StageDev(){}
StageDev::~StageDev(){}

StageDev::StageDev(StageManager* _stageManager, WindowMgr* _window)
{
	stageManager = _stageManager;
	window = _window;
	stageName = "Dev";
	stageManager->addStage(this, 0);
}

//LOAD
void StageDev::load()
{
	world = new b2World(b2Vec2(0, -0));
	world->SetContactListener(this);
	
	player.setName("player");
	player.getSprite().setScale(3, 3);
	player.getHitbox().setSize(sf::Vector2f(25, 25));
	player.initialize(window, world, 1.f, 0.3f, 30.f, -31.875f);
	player.spawn();

	
	bgText.loadFromFile("assets/strike.jpg");
}

//UPDATE
void StageDev::update()
{
	player.update();

	world->Step(1.0f / 65.f, 8, 3);
	
	//MISC
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
	{
		stageManager->changeStage("Main Menu");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
	{
		window->setResolution(1920, 1080, 1, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
	{
		window->setResolution(1280, 720, 1, 0);
	}

	float xRatio = window->getWindow()->getSize().x / globals::NATIVE_WIDTH;
	float yRatio = window->getWindow()->getSize().y / globals::NATIVE_HEIGHT;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		player.getBody()->SetTransform(b2Vec2((sf::Mouse::getPosition(*window->getWindow()).x / 32.f) / xRatio, (-sf::Mouse::getPosition(*window->getWindow()).y / 32.f) / yRatio), 0.f);
		player.getBody()->SetLinearVelocity(b2Vec2(0, 0));
	}
}

//DRAW
void StageDev::draw()
{
	player.draw();
}

//UNLOAD
void StageDev::unload()
{
	delete world;
}

//BEGIN CONTACT
void StageDev::BeginContact(b2Contact* contact)
{
	Entity* a = static_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* b = static_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());


	//a collisions
	switch (a->getType())
	{
	case EntityType::PLAYER:
		static_cast<Player*>(a)->startContact(b);
		break;
	
	case EntityType::FLOOR:
		static_cast<Floor*>(a)->startContact(b);
		break;
	
	default:
			break;
	}

	//b collisions
	switch (b->getType())
	{
	case EntityType::PLAYER:
		static_cast<Player*>(b)->startContact(a);
		break;

	case EntityType::FLOOR:
		static_cast<Floor*>(b)->startContact(a);
		break;

	default:
		break;
	}

}

//END CONTACT
void StageDev::EndContact(b2Contact* contact)
{
	Entity* a = static_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* b = static_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());


	//a collisions
	switch (a->getType())
	{
	case EntityType::PLAYER:
		static_cast<Player*>(a)->endContact(b);
		break;

	case EntityType::FLOOR:
		static_cast<Floor*>(a)->endContact(b);
		break;

	default:
		break;
	}

	//b collisions
	switch (b->getType())
	{
	case EntityType::PLAYER:
		static_cast<Player*>(b)->endContact(a);
		break;

	case EntityType::FLOOR:
		static_cast<Floor*>(b)->endContact(a);
		break;

	default:
		break;
	}
}