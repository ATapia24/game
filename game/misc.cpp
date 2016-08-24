#include "stdafx.h"
#include "misc.h"

//FLOAT -> STRING
std::string misc::floatToString(float num)
{
	std::ostringstream string;
	string << num;
	return string.str();
}

//INT -> STRING
std::string misc::intToString(int num)
{
	std::ostringstream string;
	string << num;
	return string.str();
}

//DOUBLE -> STRING
std::string misc::doubleToString(double num)
{
	std::ostringstream string;
	string << num;
	return string.str();
}

//GET FILE NAMES
std::vector<std::string> misc::getFileNames(std::string path)
{
	DIR *dpdf;
	struct dirent *epdf;
	std::vector<std::string> vector;

	dpdf = opendir(path.c_str());

	if (dpdf != NULL) {
		while (epdf = readdir(dpdf)) {
			vector.push_back(std::string(epdf->d_name));
		}
	}

	return vector;
}

std::string misc::getFileType(std::string filename)
{
	if (filename.length() < 4)
	{
		return "folder";
	}
	else
	{
		return filename.substr(filename.length() - 3, 3);
	}
}

//IS LETTER
bool misc::isLetter(const char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return true;
	else
		return false;
}

//EXTRACT BETWEEN
std::string misc::extractBetween(std::string string, char token)
{
	int start, end;
	bool found = 0;

	for (int i = 0; i < string.size(); i++)
	{
		if (string[i] == token)
		{
			if (found)
			{
				end = i;
				return string.substr(start+1, end - start - 1);
			}
			else
			{
				start = i;
				found = 1;
			}
		}
	}

	if(found)
	return string.substr(start + 1, string.size() - start - 1);

	return "";
}

//EXTRACT BETWEEN REPLACE
std::string misc::extractBetween(std::string& string, char token, char replace)
{
	int start, end;
	bool found = 0;

	for (int i = 0; i < string.size(); i++)
	{
		if (string[i] == token)
		{
			if (found)
			{
				end = i;
				return string.substr(start + 1, end - start - 1);
			}
			else
			{
				start = i;
				found = 1;
				string[i] = replace;
			}
		}
	}

	if (found)
		return string.substr(start + 1, string.size() - start - 1);

	return "";
}

//DISTANCE
float misc::distance(const sf::Vector2f a, const sf::Vector2f b)
{
	return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));
}

//MIDPOINT
sf::Vector2f misc::midpoint(const sf::Vector2f a, const sf::Vector2f b)
{
	return sf::Vector2f( ((a.x + b.x) / 2), ((a.y + b.y) / 2));
}

//INTERSECTS
bool misc::intersects(const sf::Vector2f a, const sf::Vector2f b, const sf::Vector2f c, const sf::Vector2f d)
{
	float den = ((d.y - c.y)*(b.x - a.x) - (d.x - c.x)*(b.y - a.y));
	float num1 = ((d.x - c.x)*(a.y - c.y) - (d.y - c.y)*(a.x - c.x));
	float num2 = ((b.x - a.x)*(a.y - c.y) - (b.y - a.y)*(a.x - c.x));
	float u1 = num1 / den;
	float u2 = num2 / den;

	if (u1 <0 || u1 > 1 || u2 < 0 || u2 > 1)
		return 0;
	return 1;
}

//RANDOM
int misc::random(int min, int max)
{
	return rand() % max + min;
}

//GET LINE ANGLE
float misc::lineAngle(const sf::Vector2f centerpoint, const sf::Vector2f endpoint)
{
	return ((atan2f((-centerpoint.y + endpoint.y), (centerpoint.x - endpoint.x)))) + PI;
}

//POINT LOCATION
sf::Vector2f misc::pointLocation(const sf::Vector2f point, const float angle, const float distance)
{
	return sf::Vector2f(point.x + distance * cos(angle), point.y + -distance * sin(angle));
}

//IN POLYGON
/*bool misc::inPolygon(sf::Vector2f p0, sf::Vector2f p[], const int sides)
{
	size_t n = 4;
	bool result = false;
	for (size_t i = 0; i < n; ++i) {
		size_t j = (i + 1) % n;
		if (
			// Does p0.y lies in half open y range of edge.
			// N.B., horizontal edges never contribute
			((p[j].y <= p0.y && p0.y < p[i].y) ||
			(p[i].y <= p0.y && p0.y < p[j].y)) &&
			// is p to the left of edge?
				(p0.x < p[j].x + (p[i].x - p[j].x) * (p0.y - p[j].y) /
			(p[i].y - p[j].y))
			)
			result = !result;
	}
	return result;
}*/

//IN POLYGON
bool misc::inPolygon(sf::Vector2f p, sf::Vector2f poly[], const int sides)
{
	int   i, j = sides - 1;
	bool  oddNodes = 0;

	for (i = 0; i<sides; i++)
	{
		if ((poly[i].y< p.y && poly[j].y >= p.y || poly[j].y< p.y && poly[i].y >= p.y) && (poly[i].x <= p.x || poly[j].x <= p.x))
			oddNodes ^= (poly[i].x + (p.y - poly[i].y) / (poly[j].y - poly[i].y)*(poly[j].x - poly[i].x)<p.x);
		j = i;
	}

	return oddNodes;
}

//GET AREA POINTS
std::vector<sf::Vector2f> misc::getAreaPoints(const sf::RectangleShape shape, const float resolustion, const bool sides)
{
	std::vector<sf::Vector2f> points;
	sf::Vector2f p;
	
	//get number of point
	int xPoints = shape.getSize().x / resolustion;
	int yPoints = shape.getSize().y / resolustion;
	int xpos = shape.getPosition().x;
	int ypos = shape.getPosition().y;
	int wOffset = shape.getSize().x / 2;
	int hOffset = shape.getSize().y / 2;

	//corners
	sf::Vector2f p1(xpos - wOffset, ypos - hOffset);
	sf::Vector2f p2(xpos + wOffset, ypos - hOffset);
	sf::Vector2f p3(xpos + wOffset, ypos + hOffset);
	sf::Vector2f p4(xpos - wOffset, ypos + hOffset);
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);


	//side 1
	float a1 = lineAngle(p1, p2);
	float a2 = lineAngle(p1, p4);
	float d1 = distance(p1, p2);
	float d2 = distance(p1, p4);
	int n1 = (d1 / resolustion) + 1;
	int n2 = (d2 / resolustion) + 1;

	for (int i = 0; i < n1; i++)
		for (int j = 0; j < n2; j++)
			points.push_back(sf::Vector2f(pointLocation(pointLocation(p1, a2, resolustion  * j+1), a1, resolustion * i+1)));

	return points;
}