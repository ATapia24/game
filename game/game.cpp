#include "stdafx.h"
#include <windows.h>
#include <SFML/Graphics.hpp>
#include "globals.h"
#include "GameManager.h"
#include "WindowMgr.h"
#include "Debug.h"
#include "misc.h"
#include "SFML\Network.hpp"
#include "Timer.h"

using namespace globals;

int main()
{
	/*
	std::string i;
	std::cin >> i;
	sf::IpAddress ip(i);
	sf::TcpSocket socket;
	char type, mode;
	std::cin >> type;
	std::string text = "Connect to: ";

	if (type == 's')
	{
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
		text += "Server\n";
	}
	else if(type == 'c')
	{
		socket.connect(ip, 2000);
		text += "Client\n";
	}

	socket.send(text.c_str(), text.length() + 1);
	
	char buffer[2000];
	size_t recieved;
	socket.receive(buffer, sizeof(buffer), recieved);
	std::cout << buffer << std::endl;

	system("pause");
	*/

	//console
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 1283, 0, 645, 1080, 0);

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