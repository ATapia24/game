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
	window->getWindow()->setMouseCursorVisible(FALSE);
	world = new b2World(b2Vec2(0, 0));
	world->SetContactListener(this);
	player.setName("player");
	player.getSprite().setScale(3, 3);
	player.getHitbox().setSize(sf::Vector2f(25, 25));
	player.initialize(window, world, 1.f, 0.3f, 10.f, -31.875f);
	player.spawn();
	bgText.loadFromFile("assets/strike.jpg");
	bg.setPosition(0, 0);
	bg.setSize(sf::Vector2f((float)bgText.getSize().x * 10, (float)bgText.getSize().y* 10));
	bg.setTexture(&bgText);
	menu.setWindow(window);
	menu.load();
	menu.setDimensions(2, 5, 200, 20);
	menu.enableBackgrounds(1, 1);
	menu.setSpacing(10, 10);
	menu.setPosition(500 , 500);
	menu.addStatic("ONE");
	menu.addStatic("TWO");
	menu.addStatic("THREE");
	menu.addStatic("FOUR");
	menu.addStatic("FIVE");
	menu.addStatic("SIX");
	menu.updateSelected();
	menuUp.set(sf::Keyboard::Up, KeyType::SINGLE);
	menuDown.set(sf::Keyboard::Down, KeyType::SINGLE);
	textures.addFolder("test");
	textures.loadTextures();
	objects = map.loadFile("editor.txt", textures.getTextures());

	wall.getHitbox().setSize(sf::Vector2f(20, 1400));
	wall.initialize(window, world, 1, 1, 1000, 400);
	wall.spawn();

	std::cout << wall.getBody()->GetPosition().x << ' ' << wall.getBody()->GetPosition().y << std::endl;

}

//UNLOAD
void StageDev::unload()
{
	delete world;
	menu.clear();
}

//UPDATE
void StageDev::update()
{
	
	player.update();
	world->Step(1.0f / 65.f, 8, 3);

	if (menuUp.getValue())
	{
		menu.indexDown();
	}else if(menuDown.getValue())
	{
		menu.indexUp();
	}

	//MISC
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		stageManager->changeStage("Main Menu");
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
		window->setResolution(1920, 1080, 1, 0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
		window->setResolution(1280, 720, 1, 0);

}

//DRAW
void StageDev::draw()
{
	window->addWorld(bg);
	//menu.draw();

	for (unsigned int i = 0; i < objects.size(); i++)
		window->addWorld(objects[i]->rectangle);

	wall.draw();

	player.draw();
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