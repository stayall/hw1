#ifndef __APPS__H__
#define __APPS__H__
#include "Window.h"
#include "Timer.h"
#include "Box.h"
#include "line.h"
#include <memory>

class Apps
{
public:
	Apps();
	int Go();

private:
	void doFream();

private:
	Window wnd;
	Timer timer;
	std::vector<std::unique_ptr<Box>> boxs;
	std::vector<std::unique_ptr<line>> lines;
};

#endif // !__APPS__H__


