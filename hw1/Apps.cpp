#include "Apps.h"
#include <iomanip>
#include <sstream>


Apps::Apps() :wnd(800, 600, L"s"), timer()
{
	

	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (auto i = 0; i < 80; i++)
	{
		boxes.push_back(std::make_unique<Box>(
			wnd.GHS(), rng, adist,
			ddist, odist, rdist
			));
	}
	wnd.GHS().setProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
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
	const float a = timer.peek() /1000 ;
	wnd.GHS().clearColor(0.07f, 0.0, 0.12f);
	//wnd.GHS().draTrigger(timer.peek() / 1000000000, wnd.m.getX() /400.0f - 1, -wnd.m.getY() / 300.0f + 1);
	//wnd.GHS().draTrigger(timer.peek() / 1000000000, 0, 0);
	for (auto& b : boxes)
	{
		b->update(a);
		b->drawCall(wnd.GHS());
	}
	wnd.GHS().swapBuffer();
}
