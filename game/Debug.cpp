#include "Debug.h"


Debug::Debug(WindowMgr& _window)
{
	window = &_window;
}

Debug::Debug(){}
Debug::~Debug(){}

void Debug::load()
{
	//menu
	debugMenu.setWindow(window);
	debugMenu.load();
	debugMenu.setDimensions(1, 10, 200, 20);
	debugMenu.setPosition(10, 10);

	//add items
	debugMenu.add(fpsString);
	//debugMenu.add(loopLatencyString);
	debugMenu.add(mousePositionString);
	
		//fast moving #'s update speed
	updateTimer.start();
	updateSpeed = 60;
}

void Debug::updateStrings()
{
	//fast
	if (updateTimer.getTimeInt() > updateSpeed)
	{
		fpsString = "fps : " + misc::floatToString(fpsFloat);
		loopLatencyString = "ms  : " + misc::doubleToString(loopFloat);
		updateTimer.reset_ms();
	}

	//slow
	mousePositionString = "X: " + misc::intToString(mouseX) + " Y: " + misc::intToString(mouseY);
}

//UPDATE
void Debug::update()
{
	//items
	fps();
	//loopLatency();
	mousePosition();

	//strings and draw
	updateStrings();
	
	debugMenu.update();
	debugMenu.draw();
}

//FPS
void Debug::fps()
{
	fpsFloat = 1.f / fpsClock.getElapsedTime().asSeconds();
	fpsClock.restart();
}

//Mouse Position
void Debug::mousePosition()
{
	mouseX = sf::Mouse::getPosition(*window->getWindow()).x;
	mouseY = sf::Mouse::getPosition(*window->getWindow()).y;
}

//LOOP TIMER
void Debug::loopLatency()
{
	loopTimer.stop();
	loopFloat = loopTimer.getTimeDec();
	loopTimer.start();
}


//SET WINDOWMGR
void Debug::setWindowMgr(WindowMgr& _window)
{
	window = &_window;
	load();
}

//ADD
void Debug::add(std::string& string)
{
	debugMenu.add(string);
}