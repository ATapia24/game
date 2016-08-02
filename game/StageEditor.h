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
#include "MenuSelect.h"
#include "misc.h"
#include "NativePosition.h"
#include "Entity.h"
#include "MenuSelect.h"
#include "dirent.h"
#include "EditorObject.h"

struct Object
{
	ObjType type;
	sf::Sprite sprite;
	sf::RectangleShape rectangle;
	sf::CircleShape circle;
};

class StageEditor : public Stage
{
private:
	sf::Sprite background;
	sf::Texture gridTexture;
	EditorObject* objects;
	int MAX_OBJECTS;
	int objectIndex, n_objects;
	void objectIndexUp();
	void objectIndexDown();
	void objectIndexUpdate(int lastIndex);
	bool objectIndexUpRel;
	bool objectIndexDownRel;
	void deleteObject(int index);
	bool objectDeleteRel;

	MenuSelect menu;

	Object dragType;
	short int dragTypeIndex;
	std::string dragTypeString;
	void updateDragType();
	void dragTypeLeft();
	void dragTypeRight();
	bool dragTypeLeftRel;
	bool dragTypeRightRel;
	void drawObjects();

	float viewSpeed, viewSpeedOffset;
	float zoomSpeed, zoomAmount;
	b2World* world;
	sf::View* view;
	void input();

	//zoom
	void zoomIn();
	void zoomOut();
	void zoomReset();
	void rotateReset();
	
	//drag
	bool dragging;
	void startDrag();
	void endDrag();
	void updateDrag();

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

