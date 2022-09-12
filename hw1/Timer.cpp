#include "Timer.h"


Timer::Timer()
{
	tp = std::chrono::steady_clock::now();
}

float Timer::mark()
{
	std::chrono::steady_clock::time_point last = tp;
	tp = std::chrono::steady_clock::now();
	return (tp - last).count();
}

float Timer::peek() const 
{
	return (std::chrono::steady_clock::now() - tp).count();
}