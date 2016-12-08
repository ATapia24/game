#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "StageManager.h"
#include "WindowMgr.h"
#include "globals.h"
#include "Debug.h"
#include "Stage.h"
#include "StageMainMenu.h"
#include "StageDev.h"
#include "StageEditor.h"

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
	StageEditor* stageEditor;

public:
	GameManager();
	GameManager(WindowMgr& _window);
	void update();
	void draw();
	~GameManager();
};

#endif