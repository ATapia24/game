#include "stdafx.h"
#include "MenuList.h"


MenuList::MenuList(WindowMgr* _window)
{
	window = _window;
	load();
}

MenuList::MenuList()
{
	load();
}

//LOAD
void MenuList::load()
{
	font.loadFromFile("assets/font.ttf");
	menuPosition.set(0, 0);
	topPadding = 0;
	leftPadding = 0;
	topSpacing = 0;
	leftSpacing = 0;
	fontSize = 12;
	lineHeight = fontSize * 1.5f;
}


MenuList::~MenuList()
{
	std::cout << "Menu decon\n";
}


//DRAW
void MenuList::draw()
{
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		lines[i].text.setString(*lines[i].string);
		lines[i].text.setPosition(lines[i].linePosition.get());
		window->addGui(lines[i].text);
	}


}


//ADD - Dynamic
void MenuList::add(std::string& string)
{
	Line temp;
	temp.string = &string;
	temp.text.setFont(font);
	temp.lineHeight = lineHeight;
	lines.push_back(temp);
	recalculateLine();
}

//ADD - Dynamic w/ line height
void MenuList::add(std::string & string, float _lineHeight)
{
	Line temp;
	temp.string = &string;
	temp.text.setFont(font);
	temp.lineHeight = _lineHeight;
	lines.push_back(temp);
	recalculateLine();
}

//ADD - Static
void MenuList::addStatic(std::string string)
{
	//store
	std::string* tmp = new std::string;
	*tmp = string;
	staticStrings.push_back(tmp);

	Line temp;
	temp.string = staticStrings[staticStrings.size() - 1];	
	temp.text.setFont(font);
	temp.lineHeight = lineHeight;
	lines.push_back(temp);
	recalculateLine();


}

//ADD - Static w/ line height
void MenuList::addStatic(std::string string, float _lineHeight)
{
	//store
	std::string* tmp = new std::string;
	*tmp = string;
	staticStrings.push_back(tmp);

	Line temp;
	temp.string = staticStrings[staticStrings.size() - 1];
	temp.text.setFont(font);
	temp.lineHeight = _lineHeight;
	lines.push_back(temp);
	recalculateLine();

}

//SET LAYER
void MenuList::setLayer(int _layer)
{
	layer = _layer;
}

//SET POSITION
void MenuList::setPosition(float _x, float _y)
{
	menuPosition.set(_x, _y);
}

//SET MARGINS
void MenuList::setMargins(float _leftPadding, float _topPadding, float _leftSpacing, float _topSpacing)
{
	leftPadding = _leftPadding;
	topPadding = _topPadding;
	leftSpacing = _leftSpacing;
	topSpacing = _topSpacing;
}

//SET WINDOW
void MenuList::setWindow(WindowMgr* _window)
{
	window = _window;
}

//SET FONT SIZE
void MenuList::setFontSize(float _fontSize)
{
	fontSize = _fontSize;
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		lines[i].text.setCharacterSize((unsigned int)fontSize);
	}
}

//GET TEXT
sf::Text& MenuList::getLine(int line)
{
	return lines[line].text;
}

//SET LINE HEIGHT
void MenuList::setLineHeight(float _lineHeight)
{
	lineHeight = _lineHeight;
}

//RECALULATE LINE
void MenuList::recalculateLine()
{
	//calculate position and font size
	int index = lines.size() - 1;
	lines[index].linePosition.set((menuPosition.x() + leftPadding) , menuPosition.y() + topPadding + ((lines[index].lineHeight + topSpacing) * index));
	lines[index].text.setPosition(lines[index].linePosition.get());
	lines[index].text.setCharacterSize((unsigned int)fontSize);
}
