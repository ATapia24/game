#ifndef STAGE_H
#define STAGE_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "StageManager.h"
#include "WindowMgr.h"

class StageManager;

class Stage
{

protected:
	WindowMgr* window;
	StageManager* stageManager;
	std::string stageName;
	bool loaded;
public:
	Stage();
	~Stage();
	Stage(StageManager* stageManager, WindowMgr* _window);

	virtual void load();
	virtual void unload();
	virtual void update();
	virtual void draw();
	std::string getStageName();

};

#endif