#include "Apps.h"
#include <iomanip>
#include <sstream>


Apps::Apps() :wnd(800, 800, L"s"), timer()
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> rl(0.0f, 3.14f * 2);

	for (size_t i = 0; i < 1; i++)
	{
		
		boxs.push_back(std::make_unique<Box>(wnd.GHS(), rng, rl, rl, rl, rl));

	}
}

int Apps::Go()
{
	while (true)
	{
	
		if (const auto r = Window::ProcessMessge())
		{
			return *r;
		}

		doFream();
	}

}

void Apps::doFream()
{
	const float c = sin(timer.peek()/1000000000) / 2.0f + 0.5f;
	const float a = timer.peek();
	wnd.GHS().clearColor(0.07f, 0.0, 0.12f);
	wnd.GHS().draTrigger(timer.peek() / 1000000000);
	for (auto& b : boxs)
	{
	//	b->update(a);
		//b->drawCall(wnd.GHS());
	}
	wnd.GHS().swapBuffer();
}
