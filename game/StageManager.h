#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "globals.h"
#include "StageManager.h"
#include "WindowMgr.h"
#include "Debug.h"
#include "Stage.h"
#include "misc.h"

class Stage;

class StageManager
{

private:
	WindowMgr* window;
	Stage* stages[N_STAGES], *currentStage;
	int stagesSize;
	std::string currentStageString;
	void load();
public:
	StageManager();
	StageManager(WindowMgr* _window);
	~StageManager();
	void update();
	void draw();
	void changeStage(std::string stageName);
	void addStage(Stage* stage, int index);
};

#endif