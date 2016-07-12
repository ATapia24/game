#pragma once
#include "MenuList.h"

class MenuSelect : public MenuList
{
private:
	void indexUp();
	void indexDown();
	int input();
	int currentIndex, lastIndex;
	bool wrapIndex;
	sf::Color selectColor, nonSelectColor;

	//input
	bool upIndexKeyReleased, downIndexKeyReleased, returnIndexKeyReleased;
public:
	MenuSelect();
	~MenuSelect();
	void load();
	int update();
};

