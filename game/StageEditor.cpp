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
	//gridTexture.loadFromFile("assets/strike.jpg");
	gridTexture.setRepeated(true);
	background.setTexture(gridTexture);

	zoomSpeed = 0.01f;
	zoomAmount = 1;
	viewSpeed = 10.f;
	viewSpeedOffset = view->getSize().x / window->getWindow()->getSize().x * viewSpeed;

	//tmp
	dragTypeIndex = 0;
	updateDragType();

	MAX_OBJECTS = 10000;
	objects = new EditorObject[MAX_OBJECTS];
	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		objects[i].rectangle.setFillColor(sf::Color::White);
		objects[i].rectangle.setPosition(0, 0);
		objects[i].rectangle.setSize(sf::Vector2f(0, 0));
	}

	objectIndex = 0;
	n_objects = 0;


	background.setPosition(0, 0);
	background.setTextureRect(sf::IntRect(0, 0, 6000, 6000));

	//menu
	menu.setWindow(window);
	menu.load();
	menu.setFontSize(25);
	menu.setPosition(10, 200);
	menu.setDimensions(1, 5, 140, 30);
	menu.setSpacing(10, 10);
	menu.enableBackgrounds(1, 0);
	menu.addStatic("Editor Menu");
	modeString = "kek";
	menu.add(modeString);
	menu.add(dragTypeString);

	modeIndex = 0;
	modeUpdate();

	//keys
	modeKey.set(sf::Keyboard::Tab, KeyType::SINGLE);
	objectIndexUpKey.set(sf::Keyboard::Key::G, KeyType::SINGLE);
	objectIndexDownKey.set(sf::Keyboard::Key::T, KeyType::SINGLE);
	deleteKey.set(sf::Keyboard::Delete, KeyType::SINGLE);
	dragLeftKey.set(sf::Keyboard::Num1, KeyType::SINGLE);
	dragRightKey.set(sf::Keyboard::Num2, KeyType::SINGLE);
	keyZoomIn.set(sf::Keyboard::R, KeyType::REPEATED);
	keyZoomOut.set(sf::Keyboard::F, KeyType::REPEATED);
	keyZoomReset.set(sf::Keyboard::C, KeyType::SINGLE);
	keyRotateLeft.set(sf::Keyboard::Q, KeyType::REPEATED);
	keyRotateRight.set(sf::Keyboard::E, KeyType::REPEATED);
	keyRotateReset.set(sf::Keyboard::X, KeyType::SINGLE);
	keyMoveUp.set(sf::Keyboard::W, KeyType::REPEATED);
	keyMoveDown.set(sf::Keyboard::S, KeyType::REPEATED);
	keyMoveLeft.set(sf::Keyboard::A, KeyType::REPEATED);
	keyMoveRight.set(sf::Keyboard::D, KeyType::REPEATED);

	loadTextures();
}

//LOAD TEXTURES
void StageEditor::loadTextures()
{
	std::vector<std::string> files = misc::getFileNames("assets");
	for (unsigned int i = 0; i < files.size(); i++)
	{
		//std::cout << misc::getFileType(files[i]) << std::endl;
	}
}

//UPDATE
void StageEditor::update()
{
	generalInput();

	switch (mode)
	{
	case PLACE:
		placeUpdate();
		break;
	case PAN:
		panUpdate();
		break;
	case TRANSFORM:
		transformUpdate();
		break;
	default:
		break;
	}
}

void StageEditor::placeUpdate()
{

	placeInput();

	if (dragging)
		updateDrag();
}

void StageEditor::placeInput()
{
	//left mouse click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !dragging)
	{
		startDrag();
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && dragging)
	{
		endDrag();
	}

	//drag left and right
	if (dragLeftKey.getValue())
		dragTypeLeft();
	else if (dragRightKey.getValue())
		dragTypeRight();
}

void StageEditor::panUpdate()
{
	panInput();
}

void StageEditor::panInput()
{
	float angle = view->getRotation();

	//up and down
	if (keyMoveUp.getValue())
		view->move(sf::Vector2f(sin(angle * globals::DEG2RAD) * viewSpeedOffset, -cos(angle * globals::DEG2RAD) * viewSpeedOffset));
	else if (keyMoveDown.getValue())
		view->move(sf::Vector2f(-sin(angle * globals::DEG2RAD) * viewSpeedOffset, cos(angle * globals::DEG2RAD) * viewSpeedOffset));

	//left and right
	if (keyMoveLeft.getValue())
		view->move(sf::Vector2f(-cos(angle * globals::DEG2RAD) * viewSpeedOffset, -sin(angle * globals::DEG2RAD) * viewSpeedOffset));
	else if (keyMoveRight.getValue())
		view->move(sf::Vector2f(cos(angle * globals::DEG2RAD) * viewSpeedOffset, sin(angle * globals::DEG2RAD) * viewSpeedOffset));

	//rotate
	if (keyRotateLeft.getValue())
		view->setRotation(window->getWorldView()->getRotation() - 1.f);
	else if (keyRotateRight.getValue())
		view->setRotation(window->getWorldView()->getRotation() + 1.f);
	else if (keyRotateReset.getValue())
		rotateReset();

	//zoom out and in
	if (keyZoomIn.getValue())
		zoomIn();
	else if (keyZoomOut.getValue())
		zoomOut();
	else if (keyZoomReset.getValue())
		zoomReset();
}

void StageEditor::transformUpdate()
{
	transformInput();
}

void StageEditor::transformInput()
{
	
}

//INPUT
void StageEditor::generalInput()
{
	//change editor mode
	if (modeKey.getValue())
		modeIndexUp();

	//back
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde))
		stageManager->changeStage("Main Menu");

	//object index up and down
	if (objectIndexUpKey.getValue())
		objectIndexUp();
	else if (objectIndexDownKey.getValue())
		objectIndexDown();

	//delete object
	if (deleteKey.getValue())
		deleteObject(objectIndex);

	/*

	int tmp = 3;
	//tmp up and down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		objects[objectIndex].shrinkTop(tmp);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		objects[objectIndex].shrinkBottom(tmp);
	}

	//tmp object left or right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		objects[objectIndex].rotateLeft(tmp);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		objects[objectIndex].rotateRight(tmp);
	}*/
}

//MODE UPDATE
void StageEditor::modeUpdate()
{
	switch(modeIndex)
	{
	case Mode::PAN:
		mode = Mode::PAN;
		modeString = "Pan";
		break;

	case Mode::PLACE:
		mode = Mode::PLACE;
		modeString = "Place";
		break;
	case Mode::TRANSFORM:
		mode = Mode::PLACE;
		modeString = "Transform";
		break;
	}

	menu.update();
}

//MODE INDEX UP
void StageEditor::modeIndexUp()
{
	modeIndex < 2 ? modeIndex++ : modeIndex = 0;
	modeUpdate();
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
	view->zoom(1.f / zoomAmount);
	zoomAmount = 1.f;
}

//ROTATE RESET
void StageEditor::rotateReset()
{
	view->setRotation(0.f);
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
		/*float x1 = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x - objects[objectIndex].circle.getPosition().x;
		float y1 = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y - objects[objectIndex].circle.getPosition().y;
		float x2 = objects[objectIndex].circle.getPosition().x + objects[objectIndex].circle.getRadius() / window->getScale().x;
		float y2 = objects[objectIndex].circle.getPosition().y + objects[objectIndex].circle.getRadius() / window->getScale().y;
		float radius = sqrt(pow(x2 - x1, 2.f) + pow(y2 - y1, 2.f));
		std::cout << radius << std::endl;
		objects[objectIndex].circle.setRadius(radius);*/
		break;
	}
}

//START DRAG
void StageEditor::startDrag()
{
	//set object position to mouse pos
	float x, y;
	int last = objectIndex;
	if (n_objects > 0)
	{
		objectIndex = n_objects;
	}

	switch (dragTypeIndex)
	{
	case ObjType::RECTANGLE:
		objects[objectIndex].type = ObjType::RECTANGLE;
		x = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x;
		y = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y;
		objects[objectIndex].rectangle.setPosition(x, y);
		break;

	case ObjType::CIRCLE:
		objects[objectIndex].type = ObjType::CIRCLE;
		x = ((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x / window->getScale().x;
		y = ((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y / window->getScale().y;
		objects[objectIndex].circle.setPosition(x, y);
		break;
	
	case ObjType::STATIC_OBJ:
		objects[objectIndex].type = ObjType::RECTANGLE;
		x = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x;
		y = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y;
		objects[objectIndex].rectangle.setPosition(x, y);
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}
	
	objectIndexUpdate(last);
	n_objects++;

	dragging = 1;
}

//OBJECT INDEX UP
void StageEditor::objectIndexUp()
{
	int lastIndex = objectIndex;
	objectIndex++;
	objectIndex == n_objects ? objectIndex = 0 : objectIndex;
	objectIndexUpdate(lastIndex);
}

//OBJECT INDEX DOWN
void StageEditor::objectIndexDown()
{
	int lastIndex = objectIndex;
	objectIndex--;
	objectIndex < 0 ? objectIndex = n_objects - 1 : objectIndex;
	objectIndexUpdate(lastIndex);
}

//DELETE OBJECT
void StageEditor::deleteObject(int index)
{
	if (n_objects > 0)
	{
		int offset = 0;
		for (int i = 0; i < n_objects; i++)
		{
			i == index ? offset++ : offset;
			objects[i] = objects[i + offset];
		}

		n_objects--;
		objectIndex > 0 ? objectIndex-- : objectIndex;
		objectIndexUpdate(-1);
	}
}

//OBJECT INDEX UPDATE *pass -1 to only update current
void StageEditor::objectIndexUpdate(int lastIndex)
{
	sf::Color selectedColor = sf::Color::Red;

	if (lastIndex != -1)
	{
		//update last
		switch (objects[lastIndex].type)
		{
		case ObjType::RECTANGLE:
			objects[lastIndex].rectangle.setFillColor(sf::Color::White);
			break;

		case ObjType::CIRCLE:
			objects[lastIndex].circle.setFillColor(sf::Color::White);
			break;

		case ObjType::STATIC_OBJ:
			objects[lastIndex].rectangle.setFillColor(sf::Color::White);
			break;

		case ObjType::DYNAMIC_OBJ:
			break;
		}
	}

	//update current
	switch (objects[objectIndex].type)
	{
	case ObjType::RECTANGLE:
		objects[objectIndex].rectangle.setFillColor(selectedColor);
		break;

	case ObjType::CIRCLE:
		objects[objectIndex].circle.setFillColor(selectedColor);
		break;

	case ObjType::STATIC_OBJ:
		objects[objectIndex].rectangle.setFillColor(selectedColor);
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}

}

//END DRAG
void StageEditor::endDrag()
{
	switch (dragTypeIndex)
	{
	case ObjType::RECTANGLE:
		sf::RectangleShape* rect = &objects[objectIndex].rectangle;

		//adjust for negative size
		if (rect->getSize().x < 0)
		{
			rect->setPosition(rect->getPosition().x + rect->getSize().x, rect->getPosition().y);
			rect->setSize(sf::Vector2f(-rect->getSize().x, rect->getSize().y));
		}
		if (rect->getSize().y < 0)
		{
			rect->setPosition(rect->getPosition().x, rect->getPosition().y + rect->getSize().y);
			rect->setSize(sf::Vector2f(rect->getSize().x, -rect->getSize().y));
		}
		break;

	//case ObjType::CIRCLE:
		//break;
	}

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
	rotateReset();
	menu.clear();
}