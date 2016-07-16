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
	view->setRotation(0);
	view->setCenter(0, 0);


	gridTexture.loadFromFile("assets/grid_green.png", sf::IntRect(0, 0, 1920, 1080));
	gridTexture.setRepeated(true);
	background.setTexture(gridTexture);

	zoomSpeed = 0.01f;
	zoomAmount = 1;
	viewSpeed = 10.f;
	viewSpeedOffset = view->getSize().x / window->getWindow()->getSize().x * viewSpeed;

	//tmp
	objects = new Object[10000];
	for (int i = 0; i < 100; i++)
	{
		objects[i].rectangle.setFillColor(sf::Color::White);
		objects[i].rectangle.setPosition(0, 0);
		objects[i].rectangle.setSize(sf::Vector2f(0, 0));
	}

	currentRect = 0;
	n_rect = 0;

	dragRect.setFillColor(sf::Color::Green);
	dragRect.setPosition(0, 0);
	dragRect.setSize(sf::Vector2f(100, 100));

	background.setPosition(0, 0);
	background.setTextureRect(sf::IntRect(0, 0, 6000, 6000));
	background.setColor(sf::Color::Green);

	//menu
	menu.setWindow(window);
	menu.setPosition(0, 200);
	menu.setMargins(3, -1, 1, 4);
	menu.setFontSize(25);
	menu.addStatic("Editor Menu");


	//tmp //float y = (((float)-sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) + (view->getSize().y / 2) - view->getCenter().y) / window->getScale().y;
	//x = ((((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x) / 32.f;
	//y = ((((float)-sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) + (view->getSize().y / 2) - view->getCenter().y) / window->getScale().y) / 32.f;


}

//UPDATE
void StageEditor::update()
{

	menu.update();

	input();

	if (dragging)
		updateDrag();

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		float zoom = 1.f - zoomSpeed;
		zoomAmount = zoomAmount * (zoom);
		view->zoom(zoom);
		viewSpeedOffset = view->getSize().x / window->getWindow()->getSize().x * viewSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		float zoom = 1.f + zoomSpeed;
		zoomAmount = zoomAmount * (zoom);
		view->zoom(zoom);
		viewSpeedOffset = view->getSize().x / window->getWindow()->getSize().x * viewSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		view->zoom(1.f / zoomAmount);
		zoomAmount = 1.f;
	}

	//left mouse click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !dragging)
	{
		startDrag();
	}else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && dragging)
	{
		endDrag();
	}
}

//UPDATE DRAG
void StageEditor::updateDrag()
{
	//calculate size based on rect and mouse position
	float x = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x - objects[currentRect].rectangle.getPosition().x;
	float y = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y - objects[currentRect].rectangle.getPosition().y;
	objects[currentRect].rectangle.setSize(sf::Vector2f(x, y));
}

//START DRAG
void StageEditor::startDrag()
{
	//set rect position to mouse pos
	float x = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x;
	float y = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y;
	objects[currentRect].rectangle.setPosition(x, y);
	objects[currentRect].rectangle.setFillColor(sf::Color::Red);
	n_rect++;
	dragging = 1;
}

//END DRAG
void StageEditor::endDrag()
{

	sf::RectangleShape* rect = &objects[currentRect].rectangle;
	
	//adjust for negative size
	if (rect->getPosition().x < 0)
	{
		rect->setPosition(rect->getPosition().x + rect->getSize().x, rect->getPosition().y);
		rect->setSize(sf::Vector2f(-rect->getSize().x, rect->getSize().y));
	}
	if (rect->getPosition().y < 0)
	{
		rect->setPosition(rect->getPosition().x, rect->getPosition().y + rect->getSize().y);
		rect->setSize(sf::Vector2f(rect->getSize().x, -rect->getSize().y));
	}

	rect->setFillColor(sf::Color::White);
	currentRect++;
	dragging = 0;
}

//DRAW
void StageEditor::draw()
{
	window->addWorld(background);
	window->addWorld(dragRect);
	for (int i = 0; i < n_rect; i++)
	{
		window->addWorld(objects[i].rectangle);
	}

	menu.draw();
}

//UNLOAD
void StageEditor::unload()
{

}