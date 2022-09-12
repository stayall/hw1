#include "Timer.h"


Timer::Timer()
{
	tp = std::chrono::steady_clock::now();
}

float Timer::mark()
{
	std::chrono::steady_clock::time_point last = tp;
	tp = std::chrono::steady_clock::now();
	std::chrono::duration<float> freamtime =  tp - last;
	return freamtime.count();
}

float Timer::peek() const 
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - tp).count();
}