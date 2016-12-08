#ifndef TIMER_H
#define TIMER_H

#include <ctime>

class Timer
{
private:
	clock_t begin, end, current;
public:
	void start();
	void stop();
	float getDelta_ms();
	long int getTimeInt();
	float getTimeDec();
	float reset_ms();
	Timer();
	~Timer();
};

#endif