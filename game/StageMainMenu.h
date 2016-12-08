#ifndef STAGEMAINMENU_H
#define STAGEMAINMENU_H

#include "Stage.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "StageManager.h"
#include "WindowMgr.h"
#include "MenuList.h"
#include "AnimatedBackground.h"
#include "KeyManager.h"

class StageMainMenu : public Stage
{
private:
	MenuList menu;
	Key up, down, select;
	AnimatedBackground background;
public:
	StageMainMenu();
	~StageMainMenu();
	StageMainMenu(StageManager* stageManager, WindowMgr* _window);
	void load();
	void unload();
	void update();
	void draw();
};

#endif