#include "Timer.h"


Timer::Timer()
{

}


Timer::~Timer()
{
}


//START
void Timer::start()
{
	begin = std::clock();
}

//STOP
void Timer::stop()
{
	end = std::clock();
}


//GET DELTA - MILLISECONDS
float Timer::getDelta_ms()
{
	return float(end - begin) / CLOCKS_PER_SEC;
}

//RESET - MILLISECONDS
float Timer::reset_ms()
{
	float d = float(end - begin) / CLOCKS_PER_SEC;
	start();
	return d;
}


//GET TIME - MILLISECONDS
long int Timer::getTimeInt()
{
	return std::clock() - begin;
}

//GET TIME - MILLISECONDS
float Timer::getTimeDec()
{
	return (float)(std::clock() - begin) / CLOCKS_PER_SEC;
}