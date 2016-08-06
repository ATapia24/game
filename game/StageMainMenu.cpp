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
		//bg
		background.load("Assets/image1.png", 270, 200, 134);
		background.setWindow(*window);
		
		//menu
		menu.setWindow(window);
		menu.load();
		menu.setDimensions(1, 4, 200, 20);
		menu.setPosition(200, 200);
		menu.addStatic("Start");
		menu.addStatic("Settings");
		menu.addStatic("Dev Mode");
		menu.addStatic("Editor");
		menu.updateSelected();
		
		//input
		up.set(sf::Keyboard::Up, KeyType::SINGLE);
		down.set(sf::Keyboard::Down, KeyType::SINGLE);
		select.set(sf::Keyboard::Return, KeyType::SINGLE);
}

//UNLOAD
void StageMainMenu::unload()
{
	menu.clear();
}

//UPDATE
void StageMainMenu::update()
{
	if (up.getValue())
	{
		menu.indexDown();
	}
	else if (down.getValue())
	{
		menu.indexUp();
	}
	else if (select.getValue())
	{
		switch (menu.getSelectedIndex())
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
	}

	background.update();
	
}

//DRAW
void StageMainMenu::draw()
{
	background.draw();
	menu.draw();
}