#include "GameManager.h"

GameManager::GameManager(){}
GameManager::~GameManager(){}

GameManager::GameManager(WindowMgr& _window)
{
	window = &_window;
	load();
}

//LOAD
void GameManager::load()
{
	stageManager = new StageManager(window);

	//stages
	stageMainMenu = new StageMainMenu(stageManager, window);
	stageDev = new StageDev(stageManager, window);
	stageEditor = new StageEditor(stageManager, window);

	//go str8 to dev mode
	stageManager->changeStage("Dev");
}

//UPDATE
void GameManager::update()
{
	stageManager->update();
}

//DRAW
void GameManager::draw()
{
	stageManager->draw();

	//debug always on top
	globals::debug.update();
	window->draw();
}
