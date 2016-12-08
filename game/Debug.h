#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "MenuList.h"
#include "misc.h"
#include "WindowMgr.h"
#include "Timer.h"

class Debug
{

private:
	WindowMgr *window;
	sf::Font font;
	void load();

	MenuList debugMenu;
	
	void updateStrings();
	//menu update speed
	Timer updateTimer;
	int updateSpeed;

	//fps
	void fps();
	float fpsFloat;
	std::string fpsString;
	sf::Clock fpsClock;

	//mouse position
	void mousePosition();
	int mouseX, mouseY;
	std::string mousePositionString;

	//loop time
	void loopLatency();
	Timer loopTimer;
	double loopFloat;
	std::string loopLatencyString;

public:
	Debug(WindowMgr& _window);
	Debug();
	~Debug();
	void setWindowMgr(WindowMgr& _window);
	void update();
	void add(std::string& string);
};

#endif