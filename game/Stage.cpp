#include "stdafx.h"
#include "Stage.h"


Stage::Stage(){}
Stage::~Stage(){}

Stage::Stage(StageManager* _stageManager, WindowMgr* _window)
{
	stageManager = _stageManager;
	window = _window;
}

//LOAD
void Stage::load()
{

}

//UNLOAD
void Stage::unload()
{

}

//UPDATE
void Stage::update()
{

}

//DRAW
void Stage::draw()
{

}

//GET STAGE NAME
std::string Stage::getStageName()
{
	return stageName;
}