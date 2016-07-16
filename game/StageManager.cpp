#include "stdafx.h"
#include "StageManager.h"


StageManager::StageManager(){}
StageManager::~StageManager(){}

StageManager::StageManager(WindowMgr* _window)
{
	window = _window;
	load();
}

//LOAD
void StageManager::load()
{
	stagesSize = 0;
	globals::debug.add(currentStageString);
}

//UPDATE
void StageManager::update()
{
	currentStage->update();
}

//DRAW
void StageManager::draw()
{
	currentStage->draw();
}

//CHANGE STAGE
void StageManager::changeStage(std::string stageName)
{
	bool found=0;

	for (int i = 0; i < globals::N_STAGES; i++)
	{
		if (stages[i] != NULL && (stages[i]->getStageName() == stageName))
		{
			currentStage->unload();
			currentStage = stages[i];
			currentStage->load();
			currentStageString = "Stage: " + currentStage->getStageName();
			std::cout << "Loading stage \"" << currentStage->getStageName() << "\"\n";
			i = globals::N_STAGES;
			found = 1;
		}
	}

	if (!found)
		std::cout << "Stage \"" << stageName << "\" not found.\n";
}

//ADD STAGE
void StageManager::addStage(Stage* stage, int index)
{
	//set index
	stages[stagesSize] = stage;

	//set first stage
	if (stagesSize == 0)
	{
		currentStage = stages[stagesSize];
		currentStage->load();
		currentStageString = "Stage: " + currentStage->getStageName();
	}
	stagesSize++;
}