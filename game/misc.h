#ifndef MISC_H
#define MISC_H

#include <string>
#include <sstream>
#include <vector>
#include "SFML\Graphics.hpp"
#include "dirent.h"
#include <cmath>
#include <iostream>
#include "Box2D\Box2D.h"

//RESOLUTION
#define NATIVE_WIDTH 1920
#define NATIVE_HEIGHT 1080

//STAGES
#define N_STAGES 10

//math
#define PI 3.14159265359f
#define PI2 6.28318530718f
#define PIh 1.57079632679f
#define PId4 0.78539816339f
#define PI3d4 2.35619449019f
#define PI5d4 3.92699081699f
#define PI7d4 5.49778714378f
#define RAD2DEG 57.2957795131f
#define DEG2RAD 0.01745329251f
#define PT2PIX 1.333333333333333f
#define PIX2PT 0.75f
#define PHYS_SCALE 32.f

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
	float lineAngle(const sf::Vector2f centerpoint, const sf::Vector2f endpoint);
	float lineAngle(const  b2Vec2 centerpoint, const b2Vec2 endpoint);
	sf::Vector2f midpoint(const sf::Vector2f a, const sf::Vector2f b);
	sf::Vector2f pointLocation(const sf::Vector2f point, const float angle, const float distance);
	bool intersects(const sf::Vector2f p1, const sf::Vector2f p2, const sf::Vector2f p3, const sf::Vector2f p4);
	int random(int min, int max);
	bool inPolygon(sf::Vector2f point, sf::Vector2f poly[], const int n_points);
}

#endif
