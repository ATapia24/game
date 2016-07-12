#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "StageManager.h"
#include "WindowMgr.h"
#include "globals.h"
#include "Debug.h"
#include "Stage.h"
#include "StageMainMenu.h"
#include "StageDev.h"

class Stage;

class GameManager
{
private:
	WindowMgr* window;
	StageManager* stageManager;
	void load();

	//stages
	StageMainMenu* stageMainMenu;
	StageDev* stageDev;

public:
	GameManager();
	GameManager(WindowMgr& _window);
	void update();
	void draw();
	~GameManager();
};

