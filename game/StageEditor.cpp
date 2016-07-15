#include "stdafx.h"
#include "StageEditor.h"


StageEditor::StageEditor()
{
}


StageEditor::~StageEditor()
{
}

StageEditor::StageEditor(StageManager* _stageManager, WindowMgr* _window)
{
	stageManager = _stageManager;
	window = _window;
	view = window->getWorldView();
	stageName = "Editor";
	stageManager->addStage(this, 0);
}

//LOAD
void StageEditor::load()
{
	world = new b2World(b2Vec2(0, -0));
	world->SetContactListener(this);
	view->setRotation(0);
	view->setCenter(0, 0);

	player.setName("player");
	player.getSprite().setScale(2, 2);
	player.getHitbox().setSize(sf::Vector2f(25, 25));
	player.setMap(strike);
	player.initialize(window, world, 1.f, 0.3f, 30.f, -31.875f);
	player.spawn();

	background.setSize(sf::Vector2f(9600, 9600));
	//background.setFillColor(sf::Color::Magenta);
	gridTexture.loadFromFile("assets/grid_green.png", sf::IntRect(0, 0, 20, 20));
	gridTexture.setRepeated(1);
	background.setTexture(&gridTexture);

	zoomSpeed = 0.01f;
	viewSpeed = 10.f;
	viewSpeedOffset = view->getSize().x / window->getWindow()->getSize().x * viewSpeed;

	/*bgText.loadFromFile("assets/strike.jpg");
	strike.getSprite()->setTexture(bgText);
	strike.getSprite()->setScale(5, 5);
	strike.initialize(window, world, 1.0f, 0.3f, 5.f, 5.f);*/
}

//UPDATE
void StageEditor::update()
{
	//strike.update();
	player.update();

	world->Step(1.0f / 65.f, 8, 3);

	input();

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
}

//UPDATE CAMERA
void StageEditor::input()
{
	float angle = view->getRotation();

	//up and down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		view->move(sf::Vector2f(sin(angle * globals::DEG2RAD) * viewSpeedOffset, -cos(angle * globals::DEG2RAD) * viewSpeedOffset));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		view->move(sf::Vector2f(sin(angle * globals::DEG2RAD) * viewSpeedOffset, cos(angle * globals::DEG2RAD) * viewSpeedOffset));
	}

	//left and right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		view->move(sf::Vector2f(-cos(angle * globals::DEG2RAD) * viewSpeedOffset, -sin(angle * globals::DEG2RAD) * viewSpeedOffset));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		view->move(sf::Vector2f(cos(angle * globals::DEG2RAD) * viewSpeedOffset, sin(angle * globals::DEG2RAD) * viewSpeedOffset));
	}

	//rotate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		view->setRotation(window->getWorldView()->getRotation() - 1.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		view->setRotation(window->getWorldView()->getRotation() + 1.f);
	}

	//zoom out and in
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		view->zoom(1.f - zoomSpeed);
		viewSpeedOffset = view->getSize().x / window->getWindow()->getSize().x * viewSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		view->zoom(1.f + zoomSpeed);
		viewSpeedOffset = view->getSize().x / window->getWindow()->getSize().x * viewSpeed;
	}

	//left mouse click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		float x, y;
		if (window->isFullscreen())
		{
			x = ((float)sf::Mouse::getPosition(*window->getWindow()).x / window->getScale().x) / 32.f;
			y = ((float)-sf::Mouse::getPosition(*window->getWindow()).y / window->getScale().y) / 32.f;
		}
		else {
			x = (((float)sf::Mouse::getPosition(*window->getWindow()).x - (view->getSize().x / 2)) / window->getScale().x) / 32.f;
			y = (((float)-sf::Mouse::getPosition(*window->getWindow()).y + (view->getSize().y / 2)) / window->getScale().y) / 32.f;
		}
		player.getBody()->SetTransform(b2Vec2(x, y), view->getRotation());
	}
}

//DRAW
void StageEditor::draw()
{
	window->addWorld(background);
	player.draw();
}

//UNLOAD
void StageEditor::unload()
{
	delete world;
}

//BEGIN CONTACT
void StageEditor::BeginContact(b2Contact* contact)
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
void StageEditor::EndContact(b2Contact* contact)
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