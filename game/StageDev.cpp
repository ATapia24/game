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
	window->getWindow()->setMouseCursorVisible(1);
	world = new b2World(b2Vec2(200, -200));
	world->SetContactListener(this);
	player.setName("player");
	player.getSprite().setScale(3, 3);
	player.getHitbox().setSize(sf::Vector2f(25, 25));
	player.initialize(window, world, 1.f, 0.3f, 20.f, 20.f);
	player.spawn();

	bot.setName("Bot");
	bot.getHitbox().setSize(sf::Vector2f(30, 30));
	bot.getHitbox().setFillColor(sf::Color::Red);
	bot.initialize(window, world, 1, 0, 5, 5);
	bot.spawn();
	waypoint.set(sf::Keyboard::Space, KeyType::SINGLE);

	//bgText.loadFromFile("assets/strike.jpg");
	bg.setFillColor(sf::Color(100, 100, 100, 255));
	bg.setPosition(0, 0);
	bg.setSize(sf::Vector2f(20000, 20000));


	//VB
	vb = new ViewBlocker;
	vb->set(player, window, world);

	n_walls = 1;
	walls = new Solid[n_walls];

	for (int i = 0; i < n_walls; i++)
	{
		if(i < 10)
		walls[i].getHitbox().setSize(sf::Vector2f(500, 1000));
		else
		walls[i].getHitbox().setSize(sf::Vector2f(misc::random(10, 500), misc::random(10, 500)));
		walls[i].initialize(window, world, 1, 1, misc::random(1, 5000), misc::random(1, 5000));
		walls[i].spawn();
		vb->addObject(walls[i]);
		walls[i].setName(misc::intToString(i));
		pathf.addObject(walls[i]);
	}

	textures.addFolder("test");
	textures.loadTextures();
	objects = map.loadFile("Assets/editor.txt", textures.getTextures(), window, world);
	std::cout << "SIZE: " << objects.size() << '\n';
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->spawn();
		pathf.addObject(*objects[i]);
		vb->addObject(*objects[i]);
	}

	pathf.setPathMesh(1000, 1000);
}

//UNLOAD
void StageDev::unload()
{
	delete world;
	delete vb;
}

//UPDATE
void StageDev::update()
{
	if (waypoint.getValue())
	{
		bot.clearWaypoints();
		std::vector<sf::Vector2f> wp = pathf.findPath(bot.getHitbox().getPosition(), player.getHitbox().getPosition());
		if (wp.size() > 0)
		{
			bot.setWaypoints(wp);
			//grid = pathf.getGrid();
			pathf.clearNodes();
		}
	}
	player.update();
	bot.update();
	world->Step(1.0f / 65.f, 8, 3);
	vb->update();

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


	player.draw();
	bot.draw();

	vb->draw();

	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->draw();



	for (int i = 0; i < n_walls; i++)
		walls[i].draw();

	//for(int i=0; i<grid.size(); i++)
	//window->addWorld(grid[i]);

}

//BEGIN CONTACT
void StageDev::BeginContact(b2Contact* contact)
{
	Entity* a = static_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* b = static_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData());

	//check for screen sensor
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if ((int)fixtureUserData == 3)
		b->setOnScreen(true);

	//a collisions
	switch (a->getType())
	{
	case EntityType::PLAYER:
		static_cast<Player*>(a)->startContact(b);
		break;
	
	case EntityType::SOLID:
		static_cast<Solid*>(a)->startContact(b);
		break;
	
	case EntityType::PROJECTILE:
		static_cast<Projectile*>(a)->startContact(b);
		break;

	case EntityType::SCREEN:
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

	case EntityType::SOLID:
		static_cast<Solid*>(a)->startContact(b);
		break;

	case EntityType::PROJECTILE:
		static_cast<Projectile*>(a)->startContact(b);
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

	//check for screen sensor
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if ((int)fixtureUserData == 3)
		b->setOnScreen(false);

	//a collisions
	switch (a->getType())
	{
	case EntityType::PLAYER:
		static_cast<Player*>(a)->endContact(b);
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

	default:
		break;
	}
}