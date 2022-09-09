#ifndef __TIMER__H__
#define __TIMER__H__
#include <chrono>


class Timer
{
public:
	Timer()  ;
	float mark();
	float peek() const ;

private:
	std::chrono::steady_clock::time_point tp;
};

#endif // !__TIMER__H__
