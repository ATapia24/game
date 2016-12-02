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

	window->setMouseVisible(1);
	gridTexture.loadFromFile("assets/grid_white.png", sf::IntRect(0, 0, 1920, 1080));
	gridTexture.setRepeated(true);
	background.setTexture(gridTexture);
	background.setColor(sf::Color(255, 255, 255, 100));

	zoomSpeed = 0.01f;
	zoomAmount = 1;
	viewSpeed = 10.f;
	viewSpeedOffset = view->getSize().x / window->getWindow()->getSize().x * viewSpeed;

	//tmp
	dragTypeIndex.set(0, ObjType::N_TYPES-1, 1);
	updateDragType();

	objects = new EditorObject[MAX_OBJECTS];
	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		objects[i].rectangle.setFillColor(sf::Color::White);
		objects[i].rectangle.setPosition(0, 0);
		objects[i].rectangle.setSize(sf::Vector2f(0, 0));
		objects[i].textureName = "none";
	}

	objectIndex.set(0, MAX_OBJECTS-1, 1);
	n_objects = 0;


	width = 2000;
	height = 2000;
	background.setPosition(0, 0);
	background.setTextureRect(sf::IntRect(0, 0, 6000, 6000));

	loadTextures();
	textureIndex.set(0, textureList.size()-1, 1);
	texture = textureList[textureIndex.getIndex()]->texture;
	
	//menu
	menu.setWindow(window);
	menu.load();
	menu.setFontSize(25);
	menu.setPosition(10, 200);
	menu.setDimensions(1, 5, 150, 100);
	menu.setSpacing(10, 10);
	menu.enableBackgrounds(1, 0);
	menu.addStatic("Editor Menu");
	menu.add(modeString);
	menu.add(texture);
	menu.add(dragTypeString);
	menu.calculatePosition();

	modeIndex.set(0, 2, 1);
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
	textureLeftKey.set(sf::Keyboard::Left, KeyType::SINGLE);
	textureRightKey.set(sf::Keyboard::Right, KeyType::SINGLE);
	keyShift.set(sf::Keyboard::LShift, KeyType::REPEATED);
	keyLeft.set(sf::Keyboard::Left, KeyType::REPEATED);
	keyRight.set(sf::Keyboard::Right, KeyType::REPEATED);
	keyDown.set(sf::Keyboard::Down, KeyType::REPEATED);
	keyUp.set(sf::Keyboard::Up, KeyType::REPEATED);
	keyControl.set(sf::Keyboard::LControl, KeyType::REPEATED);
	keySave.set(sf::Keyboard::S, KeyType::REPEATED);

	button.set(window, CHECK_BOX, sf::Vector2f(500, 500), sf::Vector2f(100, 100));
}

//LOAD TEXTURES
void StageEditor::loadTextures()
{
	textureMgr.addFolder("test");
	textureMgr.loadTextures();
	textureList = textureMgr.getTextures();
}

//UPDATE
void StageEditor::update()
{
	generalInput();

	switch (mode)
	{
	case PLACE:
		placeUpdate();
		panUpdate();
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

	//std::cout << button.getValue() << '\n';
}

void StageEditor::placeUpdate()
{

	placeInput();

	if (dragging)
		updateDrag();

	if (textureLeftKey.getValue())
	{
		textureIndex.down();
		texture = textureList[textureIndex.getIndex()]->texture;
		menu.update();
	}
	else if (textureRightKey.getValue())
	{
		textureIndex.up();
		texture = textureList[textureIndex.getIndex()]->texture;
		menu.update();
	}
}

void StageEditor::placeInput()
{
	//left mouse click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !dragging)
		startDrag();
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && dragging)
		endDrag();

	//drag left and right
	if (dragLeftKey.getValue())
	{
		dragTypeIndex.down();
		updateDragType();
	}
	else if (dragRightKey.getValue())
	{
		dragTypeIndex.up();
		updateDragType();
	}
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
		view->move(sf::Vector2f(sin(angle *DEG2RAD) * viewSpeedOffset, -cos(angle * DEG2RAD) * viewSpeedOffset));
	else if (keyMoveDown.getValue())
		view->move(sf::Vector2f(-sin(angle * DEG2RAD) * viewSpeedOffset, cos(angle * DEG2RAD) * viewSpeedOffset));

	//left and right
	if (keyMoveLeft.getValue())
		view->move(sf::Vector2f(-cos(angle * DEG2RAD) * viewSpeedOffset, -sin(angle * DEG2RAD) * viewSpeedOffset));
	else if (keyMoveRight.getValue())
		view->move(sf::Vector2f(cos(angle * DEG2RAD) * viewSpeedOffset, sin(angle * DEG2RAD) * viewSpeedOffset));

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
	float transformSpeed = 3;
	//shrink
	if (keyShift.getValue())
	{
		if(keyMoveDown.getValue())
			objects[objectIndex.getIndex()].shrinkBottom(transformSpeed);
	
		if (keyMoveUp.getValue())
			objects[objectIndex.getIndex()].shrinkTop(transformSpeed);

		if (keyMoveRight.getValue())
			objects[objectIndex.getIndex()].shrinkRight(transformSpeed);

		if (keyMoveLeft.getValue())
			objects[objectIndex.getIndex()].shrinkLeft(transformSpeed);

		//rotate
		if (keyRotateLeft.getValue())
			objects[objectIndex.getIndex()].rotateLeft(transformSpeed);
		else if (keyRotateRight.getValue())
			objects[objectIndex.getIndex()].rotateRight(transformSpeed);
	}
	//grow
	else
	{
		if (keyMoveDown.getValue())
			objects[objectIndex.getIndex()].growBottom(transformSpeed);

		if (keyMoveUp.getValue())
			objects[objectIndex.getIndex()].growTop(transformSpeed);

		if (keyMoveLeft.getValue())
			objects[objectIndex.getIndex()].growLeft(transformSpeed);

		if (keyMoveRight.getValue())
			objects[objectIndex.getIndex()].growRight(transformSpeed);
	}

	//move
	if (keyLeft.getValue())
		objects[objectIndex.getIndex()].moveLeft(transformSpeed);
	else if (keyRight.getValue())
		objects[objectIndex.getIndex()].moveRight(transformSpeed);

	if (keyUp.getValue())
		objects[objectIndex.getIndex()].moveUp(transformSpeed);
	else if (keyDown.getValue())
		objects[objectIndex.getIndex()].moveDown(transformSpeed);

}

//GENERAL INPUT
void StageEditor::generalInput()
{
	//change editor mode
	if (modeKey.getValue())
	{
		modeIndex.up();
		modeUpdate();
	}

	//save
	if (keyControl.getValue() && keySave.getValue())
		map.generateFile("editor.txt", objects, n_objects);

	//quit editor
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde))
		stageManager->changeStage("Main Menu");

	//object index up and down
	if (objectIndexUpKey.getValue())
	{
		int lastIndex = objectIndex.getIndex();
		objectIndex.up();
		objectIndexUpdate(lastIndex);
	}
	else if (objectIndexDownKey.getValue())
	{
		int lastIndex = objectIndex.getIndex();
		objectIndex.down();
		objectIndexUpdate(lastIndex);
	}

	//delete object
	if (deleteKey.getValue())
		deleteObject(objectIndex.getIndex());

	button.update();
}

//MODE UPDATE
void StageEditor::modeUpdate()
{
	switch(modeIndex.getIndex())
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
		mode = Mode::TRANSFORM;
		modeString = "Transform";
		break;
	}

	menu.update();
}

//UPDATE DRAG TYPE
void StageEditor::updateDragType()
{
	switch (dragTypeIndex.getIndex())
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

	menu.update();
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

//START DRAG
void StageEditor::startDrag()
{
	//set object position to mouse pos
	float x, y;
	int last = objectIndex.getIndex();
	if (n_objects > 0)
		objectIndex.setIndex(n_objects);

	switch (dragTypeIndex.getIndex())
	{
	case ObjType::RECTANGLE:
		objects[objectIndex.getIndex()].type = ObjType::RECTANGLE;
		x = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x;
		y = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y;
		objects[objectIndex.getIndex()].rectangle.setPosition(x, y);
		break;

	case ObjType::CIRCLE:
		objects[objectIndex.getIndex()].type = ObjType::CIRCLE;
		x = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x;
		y = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y;
		objects[objectIndex.getIndex()].circle.setOrigin(sf::Vector2f(objects[objectIndex.getIndex()].circle.getRadius() / 2, objects[objectIndex.getIndex()].circle.getRadius() / 2));
		objects[objectIndex.getIndex()].circle.setPosition(x, y);
		break;

	case ObjType::STATIC_OBJ:
		objects[objectIndex.getIndex()].type = ObjType::STATIC_OBJ;
		objects[objectIndex.getIndex()].rectangle.setSize(sf::Vector2f(textureList[textureIndex.getIndex()]->texture.getSize().x, textureList[textureIndex.getIndex()]->texture.getSize().y));
		objects[objectIndex.getIndex()].rectangle.setTexture(&textureList[textureIndex.getIndex()]->texture);
		objects[objectIndex.getIndex()].textureName = textureList[textureIndex.getIndex()]->name;
		objects[objectIndex.getIndex()].rectangle.setOrigin(sf::Vector2f((objects[objectIndex.getIndex()].rectangle.getSize().x / 2), (objects[objectIndex.getIndex()].rectangle.getSize().y / 2)));
		x = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x - (objects[objectIndex.getIndex()].rectangle.getSize().x / 2)) / window->getScale().x;
		y = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y;
		objects[objectIndex.getIndex()].rectangle.setPosition(x, y);
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}

	objectIndexUpdate(last);
	objectIndex.setMax(n_objects);
	n_objects++;

	dragging = 1;
}

//UPDATE DRAG
void StageEditor::updateDrag()
{
	//calculate size based on rect and mouse position
	float x, y, x1, y1, x2, y2, radius;
	switch (dragTypeIndex.getIndex())
	{
	case ObjType::RECTANGLE:
		objects[objectIndex.getIndex()].type = ObjType::RECTANGLE;
		x = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x - objects[objectIndex.getIndex()].rectangle.getPosition().x;
		y = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y - objects[objectIndex.getIndex()].rectangle.getPosition().y;
		objects[objectIndex.getIndex()].rectangle.setSize(sf::Vector2f(x, y));
		break;

	case ObjType::CIRCLE:
		/*
		x1 = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x - objects[objectIndex.getIndex()].circle.getPosition().x;
		y1 = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y - objects[objectIndex.getIndex()].circle.getPosition().y;
		x2 = objects[objectIndex.getIndex()].circle.getPosition().x + objects[objectIndex.getIndex()].circle.getRadius() / window->getScale().x;
		y2 = objects[objectIndex.getIndex()].circle.getPosition().y + objects[objectIndex.getIndex()].circle.getRadius() / window->getScale().y;
		radius = sqrt(pow(x2 - x1, 2.f) + pow(y2 - y1, 2.f));
		std::cout << radius << std::endl;*/
		x = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x - objects[objectIndex.getIndex()].rectangle.getPosition().x;
		y = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y - objects[objectIndex.getIndex()].rectangle.getPosition().y;
		radius = misc::distance(objects[objectIndex.getIndex()].circle.getPosition(), sf::Vector2f(x, y));
		objects[objectIndex.getIndex()].circle.setRadius(radius);
		objects[objectIndex.getIndex()].circle.setOrigin(sf::Vector2f(objects[objectIndex.getIndex()].circle.getRadius() / window->getScale().x / 2, objects[objectIndex.getIndex()].circle.getRadius() / window->getScale().y / 2));

		break;

	case ObjType::STATIC_OBJ:
		x = (((float)sf::Mouse::getPosition(*window->getWindow()).x * zoomAmount) - (view->getSize().x / 2) + view->getCenter().x) / window->getScale().x;
		y = (((float)sf::Mouse::getPosition(*window->getWindow()).y * zoomAmount) - (view->getSize().y / 2) + view->getCenter().y) / window->getScale().y;
		objects[objectIndex.getIndex()].rectangle.setPosition(x, y);
		break;
	}
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
		objectIndex.down();
		objectIndex.setMax(n_objects - 1);
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
	switch (objects[objectIndex.getIndex()].type)
	{
	case ObjType::RECTANGLE:
		objects[objectIndex.getIndex()].rectangle.setFillColor(selectedColor);
		break;

	case ObjType::CIRCLE:
		objects[objectIndex.getIndex()].circle.setFillColor(selectedColor);
		break;

	case ObjType::STATIC_OBJ:
		objects[objectIndex.getIndex()].rectangle.setFillColor(selectedColor);
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}

}

//END DRAG
void StageEditor::endDrag()
{
	switch (dragTypeIndex.getIndex())
	{
	case ObjType::RECTANGLE:
		sf::RectangleShape* rect = &objects[objectIndex.getIndex()].rectangle;

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

		//set origin
		objects[objectIndex.getIndex()].originUpdate();

		break;

	//case ObjType::CIRCLE:
		//break;
	}

	dragging = 0;
}

//DRAW
void StageEditor::draw()
{
	drawObjects();
	window->addWorld(background);
	menu.draw();
	button.draw();
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
		case ObjType::STATIC_OBJ:
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