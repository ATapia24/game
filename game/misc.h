#ifndef MISC_H
#define MISC_H

#include <string>
#include <sstream>
#include <vector>
#include "dirent.h"

namespace misc
{
	std::string floatToString(float num);
	std::string intToString(int num);
	std::string doubleToString(double num);
	std::vector<std::string> getFileNames(std::string path);
	std::string getFileType(std::string filename);
	bool isLetter(const char c);
}

#endif
