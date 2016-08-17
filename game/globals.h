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

	//math
	const float PI = 3.14159265359f;
	const float PI2 = 6.28318530718f;
	const float PIh = 1.57079632679f;
	const float RAD2DEG = 57.2957795131f;
	const float DEG2RAD = 0.01745329251f;
}

#endif // !GLOBALS_H
