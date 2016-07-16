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