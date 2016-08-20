#include "stdafx.h"
#include <windows.h>
#include <SFML/Graphics.hpp>
#include "globals.h"
#include "GameManager.h"
#include "WindowMgr.h"
#include "Debug.h"
#include "misc.h"

using namespace globals;

int main()
{

	//console
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 1283, 0, 640, 1080, 0);

	//window
	sf::RenderWindow screen(sf::VideoMode(1280, 720), "Game");
	screen.setFramerateLimit(2500);
	WindowMgr window(screen, 1920, 1080);

	debug.setWindowMgr(window);
	
	GameManager gameManager(window);
	sf::Event event;


	while (screen.isOpen())
	{
		while (screen.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				screen.close();
			}
		}


		//update
		gameManager.update();
		
		//draw
		gameManager.draw();
	}

	return 0;
}