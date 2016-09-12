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
#include "TextureManager.h"
#include "Index.h"
#include "Map.h"
#include "GUI_Button.h"

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
	Map map;
	sf::Sprite background;
	sf::Texture gridTexture;
	unsigned int width, height;
	const int GRID_SIZE = 25;
	EditorObject* objects;
	const int MAX_OBJECTS = 10000;
	int n_objects;
	Index objectIndex;
	Key objectIndexUpKey;
	Key objectIndexDownKey;
	void objectIndexUpdate(int lastIndex);
	void deleteObject(int index);
	Key deleteKey;
	Key keyControl;
	Key keySave;

	MenuList menu;

	//mode
	Mode mode;
	Index modeIndex;
	std::string modeString;
	Key modeKey;
	void modeUpdate();
	void placeUpdate();
	void panUpdate();
	void transformUpdate();
	void placeInput();
	void panInput();
	void transformInput();

	//drag
	Object dragType;
	Index dragTypeIndex;
	std::string dragTypeString;
	void updateDragType();
	void drawObjects();
	Key dragLeftKey;
	Key dragRightKey;

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

	//texture
	Index textureIndex;
	Key textureLeftKey;
	Key textureRightKey;
	sf::Texture texture;
	TextureManager textureMgr;
	std::vector<Texture*> textureList;

	//transform
	Key keyShift;
	Key keyUp;
	Key keyDown;
	Key keyLeft;
	Key keyRight;
	GUI_Button button;

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

