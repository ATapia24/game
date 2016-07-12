#ifndef GLOBALS_H
#define GLOBALS_H

#include "stdafx.h"
#include "Debug.h"
#include <string>

namespace globals
{
	extern Debug debug;

	//RESOLUTION
	const float NATIVE_WIDTH = 1920;
	const float NATIVE_HEIGHT = 1080;
	
	//STAGES
	const int N_STAGES = 10;

	//TEXT INPUT
	extern std::string textBuffer;
}

#endif // !GLOBALS_H
