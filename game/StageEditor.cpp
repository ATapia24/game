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

	//gridTexture.loadFromFile("assets/grid_green.png", sf::IntRect(0, 0, 1920, 1080));
	gridTexture.loadFromFile("assets/strike.jpg");
	gridTexture.setRepeated(true);
	background.setTexture(gridTexture);

	zoomSpeed = 0.01f;
	zoomAmount = 1;
	viewSpeed = 10.f;
	viewSpeedOffset = view->getSize().x / window->getWindow()->getSize().x * viewSpeed;

	//tmp
	dragTypeIndex = 0;
	updateDragType();

	objects = new Object[10000];
	for (int i = 0; i < 100; i++)
	{
		objects[i].rectangle.setFillColor(sf::Color::White);
		objects[i].rectangle.setPosition(0, 0);
		objects[i].rectangle.setSize(sf::Vector2f(0, 0));
	}

	objectIndex = 0;
	n_objects = 0;

	background.setPosition(0, 0);
	background.setTextureRect(sf::IntRect(0, 0, 6000, 6000));
	//background.setColor(sf::Color::Green);

	//menu
	menu.setWindow(window);
	menu.setPosition(0, 200);
	menu.setMargins(3, -1, 1, 4);
	menu.setFontSize(25);
	menu.addStatic("Editor Menu");
	menu.add(dragTypeString);

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
		view->move(sf::Vector2f(-sin(angle * globals::DEG2RAD) * viewSpeedOffset, cos(angle * globals::DEG2RAD) * viewSpeedOffset));
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
		zoomIn();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		zoomOut();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		zoomReset();
	}

	//left mouse click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !dragging)
	{
		startDrag();
	}else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && dragging)
	{
		endDrag();
	}

	//drag left and right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && dragTypeLeftRel)
	{
		dragTypeLeft();
		dragTypeLeftRel = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && dragTypeRightRel)
	{
		dragTypeRight();
		dragTypeRightRel = 0;
	}

	//drag left and right released
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && !dragTypeLeftRel)
	{
		dragTypeLeftRel = 1;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && !dragTypeRightRel)
	{
		dragTypeRightRel = 1;
	}

}


//DRAG TYPE LEFT
void StageEditor::dragTypeLeft()
{
	dragTypeIndex--;
	dragTypeIndex < 0 ? dragTypeIndex = ObjType::N_TYPES-1 : dragTypeIndex;
	updateDragType();
}

//DRAG TYPE RIGHT
void StageEditor::dragTypeRight()
{
	dragTypeIndex++;
	dragTypeIndex == ObjType::N_TYPES ? dragTypeIndex = 0 : dragTypeIndex;
	updateDragType();
}

//UPDATE DRAG TYPE
void StageEditor::updateDragType()
{
	switch (dragTypeIndex)
	{
	case ObjType::RECTANGLE:
		dragTypeString = "Rectangle";
		break;
	case ObjType::CIRCLE:
		dragTypeString = "Circle";
		break;
	case ObjType::STATIC_OBJ:
		dragTypeString = "Static Object";
		break;
	case ObjType::DYNAMIC_OBJ:
		dragTypeString = "Dynamic Object";
		break;
	}
}

//ZOOM IN
void StageEditor::zoomIn()
{
	float zoom = 1.f - zoomSpeed;
	zoomAmount = zoomAmount * (zoom);
	view->zoom(zoom);
	viewSpeedOffset = view->getSize().x / window->getWindow()->getSize().x * viewSpeed;
}

//ZOOM OUT
void StageEditor::zoomOut()
{
	float zoom = 1.f + zoomSpeed;
	zoomAmount = zoomAmount * (zoom);
	view->zoom(zoom);
	viewSpeedOffset = view->getSize().x / window->getWindow()->getSize().x * viewSpeed;
}

//ZOOM RESET
void StageEditor::zoomReset()
{
	view->setRotation(0.f);
	view->zoom(1.f / zoomAmount);
	zoomAmount = 1.f;
}

//UPDATE DRAG
void StageEditor::updateDrag()
{
	//calculate size based on rect and mouse position
	float x, y;
	switch (dragTypeIndex)
	{
	case ObjType::RECTANGLE:
		x = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x - objects[objectIndex].rectangle.getPosition().x;
		y = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y - objects[objectIndex].rectangle.getPosition().y;
		objects[objectIndex].rectangle.setSize(sf::Vector2f(x, y));
		break;

	case ObjType::CIRCLE:
		float x1 = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x - objects[objectIndex].circle.getPosition().x;
		float y1 = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y - objects[objectIndex].circle.getPosition().y;
		float x2 = objects[objectIndex].circle.getPosition().x;
		float y2 = window->getScale().y - objects[objectIndex].circle.getPosition().y;
		float radius = sqrt(pow(x2 - x1, 2.f) + pow(y2 - y1, 2.f));
		objects[objectIndex].circle.setRadius(radius);
		break;
	}
}

//START DRAG
void StageEditor::startDrag()
{
	//set object position to mouse pos
	float x, y;
	switch (dragTypeIndex)
	{
	case ObjType::RECTANGLE:
		objects[objectIndex].type = ObjType::RECTANGLE;
		x = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x;
		y = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y;
		objects[objectIndex].rectangle.setPosition(x, y);
		objects[objectIndex].rectangle.setFillColor(sf::Color::Red);
		break;

	case ObjType::CIRCLE:
		objects[objectIndex].type = ObjType::CIRCLE;
		x = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x;
		y = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y;
		objects[objectIndex].circle.setPosition(x, y);
		objects[objectIndex].circle.setFillColor(sf::Color::Red);
		break;
	
	case ObjType::STATIC_OBJ:
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}

	n_objects++;
	dragging = 1;
}

//END DRAG
void StageEditor::endDrag()
{
	switch (dragTypeIndex)
	{
	case ObjType::RECTANGLE:
		sf::RectangleShape* rect = &objects[objectIndex].rectangle;

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
		break;

	//case ObjType::CIRCLE:
		//break;
	}

	objectIndex++;
	dragging = 0;
}

//DRAW
void StageEditor::draw()
{
	window->addWorld(background);
	drawObjects();
	menu.draw();
}

//DRAW OBJECTS
void StageEditor::drawObjects()
{
	for (int i = 0; i < n_objects; i++)
	{
		switch (objects[i].type)
		{
		case ObjType::RECTANGLE:
			window->addWorld(objects[i].rectangle);
			break;

		case ObjType::CIRCLE:
			window->addWorld(objects[i].circle);
			break;
		}
	}
}

//UNLOAD
void StageEditor::unload()
{
	zoomReset();
}