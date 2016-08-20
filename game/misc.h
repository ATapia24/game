#ifndef MISC_H
#define MISC_H

#include <string>
#include <sstream>
#include <vector>
#include "SFML\Graphics.hpp"
#include "dirent.h"
#include <cmath>

#define PT2PIX 1.333333333333333f
#define PIX2PT 0.75f

namespace misc
{
	std::string floatToString(float num);
	std::string intToString(int num);
	std::string doubleToString(double num);
	std::vector<std::string> getFileNames(std::string path);
	std::string getFileType(std::string filename);
	std::string extractBetween(std::string string, char token);
	std::string extractBetween(std::string& string, char token, char replace);
	bool isLetter(const char c);
	float distance(const sf::Vector2f a, const sf::Vector2f b);
	sf::Vector2f midpoint(const sf::Vector2f a, const sf::Vector2f b);
	bool intersects(const sf::Vector2f p1, const sf::Vector2f p2, const sf::Vector2f p3, const sf::Vector2f p4);
	int random(int min, int max);
}

#endif
