#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "NativePosition.h"
#include "WindowMgr.h"

class MenuList
{
protected:
	WindowMgr *window;

	struct Line
	{
		std::string *string;
		sf::Text text;
		NativePosition linePosition;
		float lineHeight;
	};

	std::vector<Line> lines;
	std::vector<std::string*> staticStrings;

	unsigned int layer;
	//pos/spacing
	NativePosition menuPosition;
	float lineHeight;
	float xlineOffset, yLineOffset;
	float leftPadding, topPadding;
	float topSpacing, leftSpacing;

	//font
	sf::Font font;
	float fontSize;

public:
	MenuList(WindowMgr* _window);
	MenuList();
	~MenuList();
	void setWindow(WindowMgr* _window);
	virtual void load();
	void draw();
	void add(std::string& string);
	void add(std::string & string, float _lineHeight);
	void addStatic(std::string string);
	void addStatic(std::string string, float _lineHeight);
	void setLayer(int _layer);
	void setPosition(float _x, float _y);
	void setMargins(float _topPadding, float _leftPadding, float _topSpacing, float _leftSpacing);
	void setFontSize(float _fontSize);
	void setLineHeight(float _lineHeight);
	void recalculateLine();
	sf::Text& getLine(int line);
};

