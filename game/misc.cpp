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