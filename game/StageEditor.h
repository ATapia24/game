#pragma once
#include "Stage.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <SFML\Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <stdio.h>
#include <time.h>
#include <typeinfo>

#include "StageManager.h"
#include "WindowMgr.h"
#include "MenuList.h"
#include "misc.h"
#include "dirent.h"
#include "EditorObject.h"
#include "KeyManager.h"
#include "Timer.h"
#include "TextInputManager.h"

struct Object
{
	ObjType type;
	sf::Sprite sprite;
	sf::RectangleShape rectangle;
	sf::CircleShape circle;
};

enum Mode
{
	PLACE,
	PAN,
	TRANSFORM,
};

class StageEditor : public Stage
{
private:
	sf::Sprite background;
	sf::Texture gridTexture;
	EditorObject* objects;
	int MAX_OBJECTS;
	int objectIndex, n_objects;
	Key objectIndexUpKey;
	Key objectIndexDownKey;
	void objectIndexUp();
	void objectIndexDown();
	void objectIndexUpdate(int lastIndex);
	void deleteObject(int index);
	Key deleteKey;

	MenuList menu;

	//mode
	Mode mode;
	short int modeIndex;
	std::string modeString;
	Key modeKey;
	void modeIndexUp();
	void modeUpdate();
	bool modeRel;
	void placeUpdate();
	void panUpdate();
	void transformUpdate();
	void placeInput();
	void panInput();
	void transformInput();

	//drag
	Object dragType;
	short int dragTypeIndex;
	std::string dragTypeString;
	void updateDragType();
	void dragTypeLeft();
	void dragTypeRight();
	bool dragTypeLeftRel;
	bool dragTypeRightRel;
	void drawObjects();
	Key dragLeftKey;
	Key dragRightKey;
	Key textureLeftKey;
	Key textureRightKey;
	std::vector<sf::Texture*> textures;

	float viewSpeed, viewSpeedOffset;
	float zoomSpeed, zoomAmount;
	sf::View* view;
	void generalInput();

	//zoom
	void zoomIn();
	void zoomOut();
	void zoomReset();
	void rotateReset();
	Key keyMoveUp, keyMoveDown;
	Key keyMoveLeft, keyMoveRight;
	Key keyZoomIn;
	Key keyZoomOut;
	Key keyZoomReset;
	Key keyRotateLeft;
	Key keyRotateRight;
	Key keyRotateReset;
	
	//drag
	bool dragging;
	void startDrag();
	void endDrag();
	void updateDrag();

	//tmp
	TextInputManager textInput;
	std::string textString;
	sf::Texture texture;
	sf::Texture red, green;

	void loadTextures();
public:
	StageEditor();
	~StageEditor();
	StageEditor(StageManager* stageManager, WindowMgr* _window);
	void load();
	void unload();
	void update();
	void draw();
};

