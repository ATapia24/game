#include "stdafx.h"
#include "StageMainMenu.h"

StageMainMenu::StageMainMenu(){}
StageMainMenu::~StageMainMenu(){}

StageMainMenu::StageMainMenu(StageManager* _stageManager, WindowMgr* _window)
{
	window = _window;
	stageManager = _stageManager;
	stageName = "Main Menu";
	stageManager->addStage(this, 0);
}

//LOAD
void StageMainMenu::load()
{
	//menu setup
	if (!loaded)
	{
		background.load("Assets/image1.png", 270, 200, 134);
		background.setWindow(*window);
		//menu.setPosition(200, 200);
		//menu.setWindow(window);
		//menu.addStatic("Start", 45);
		//menu.addStatic("Settings", 45);
		//menu.addStatic("Dev Mode", 45);
		//menu.addStatic("Editor", 45);
		//menu.load();
		//menu.setMargins(2, -1, 1, 4);
		//menu.setFontSize(35);
		loaded = 1;
	}
}

//UPDATE
void StageMainMenu::update()
{
	switch (menu.update())
	{
		case 0:
			stageManager->changeStage("Start");
			break;
		case 1:
			stageManager->changeStage("Settings");
			break;
		case 2:
			stageManager->changeStage("Dev");
			break;
		case 3:
			stageManager->changeStage("Editor");
			break;
	}

	background.update();
}

//DRAW
void StageMainMenu::draw()
{
	background.draw();
	menu.draw();
}