#pragma once

#include <ctime>

class Timer
{
private:
	clock_t begin, end, current;
public:
	void start();
	void stop();
	float getDelta_ms();
	int getTimeInt();
	float getTimeDec();
	float reset_ms();
	Timer();
	~Timer();
};
