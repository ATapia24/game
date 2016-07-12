#pragma once

#include "Stage.h"
#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>
#include "StageManager.h"
#include "WindowMgr.h"
#include "MenuList.h"
#include "MenuSelect.h"
#include "AnimatedBackground.h"

class StageMainMenu : public Stage
{
private:
	MenuSelect menu;
	AnimatedBackground background;
public:
	StageMainMenu();
	~StageMainMenu();
	StageMainMenu(StageManager* stageManager, WindowMgr* _window);
	void load();
	void update();
	void draw();
};

