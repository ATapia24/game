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

enum ObjType
{
	RECTANGLE,
	CIRCLE
};
struct Object
{
	ObjType type;
	sf::RectangleShape rectangle;
	sf::CircleShape circle;
};

class StageEditor : public Stage
{
private:
	sf::Sprite background;
	sf::Texture gridTexture;
	sf::RectangleShape dragRect;
	Object* objects;
	int currentRect, n_rect;

	MenuSelect menu;
	

	float viewSpeed, viewSpeedOffset;
	float zoomSpeed, zoomAmount;
	b2World* world;
	sf::View* view;
	void input();
	bool dragging;
	
	void startDrag();
	void endDrag();
	void updateDrag();
public:
	StageEditor();
	~StageEditor();
	StageEditor(StageManager* stageManager, WindowMgr* _window);
	void load();
	void unload();
	void update();
	void draw();
};

