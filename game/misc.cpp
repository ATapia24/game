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