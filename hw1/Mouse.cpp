#include "Mouse.h"

#include <Windows.h>

#define XX(L) \
inline bool Mouse::Event::is##L() const noexcept \
{ \
return state == States::##L;\
}

XX(LPressure);
XX(RPressure);
XX(LRelease);
XX(RRelease);
XX(Move);
XX(RollDown);
XX(RollUp);
XX(Inside);
XX(Outside);
XX(Invaild);

#undef XX;

int Mouse::Event::getX() const noexcept
{
	return x;
}

int Mouse::Event::getY() const noexcept
{
	return y;
}

Mouse::Event::States Mouse::Event::getState() const noexcept
{
	return state;
}

std::pair<int, int> Mouse::Event::getPos() const noexcept
{
	return std::pair<int, int>(x, y);
}

bool Mouse::Event::rightIsPressured() const noexcept
{
	return rightPressured;
}

bool Mouse::Event::leftIsPressured() const noexcept
{
	return leftPressured;
}

std::pair<int, int> Mouse::getPos() const noexcept
{
	return std::pair<int, int>(x, y);
}

int Mouse::getX() const noexcept
{
	return x;
}

int Mouse::getY() const noexcept
{
	return y;
}

bool Mouse::rightIsPressured() const noexcept
{
	return rightPressured;
}

bool Mouse::leftIsPressured() const noexcept
{
	return leftPressured;
}

bool Mouse::isInWindow() const noexcept
{
	return inWindow;
}

bool Mouse::isEmepty() const noexcept
{
	return mouseEvent.empty();
}

Mouse::Event Mouse::readEvent() noexcept
{
	if (mouseEvent.size() > 0)
	{
		Mouse::Event e =  mouseEvent.front();
		mouseEvent.pop();
		return e;
	}

	return Event();
}

std::optional<Mouse::RawData> Mouse::readRawData() noexcept
{
	if (!rawEvent.empty())
	{
		RawData rd = rawEvent.front();
		rawEvent.pop();
		return { rd };
	}

	return std::nullopt;
}



void Mouse::flush() noexcept
{
	clear(mouseEvent);
}

#define XX(L) \
inline void Mouse::on##L(int _x, int _y)  noexcept \
{ \
	mouseEvent.push(Event(Event::States::##L, *this));\
	TrimBuffer(mouseEvent);\
}



 void Mouse::onLPressure(int _x, int _y)  noexcept
{
	leftPressured = true;
	mouseEvent.push(Event(Event::States::LPressure, *this));
	TrimBuffer(mouseEvent);
}


 void Mouse::onRPressure(int _x, int _y)  noexcept
{
	rightPressured = true;
	mouseEvent.push(Event(Event::States::RPressure, *this));
	TrimBuffer(mouseEvent);
}

 void  Mouse::onLRelease(int _x, int _y)  noexcept
{
	leftPressured = false;
	mouseEvent.push(Event(Event::States::LRelease, *this));
	TrimBuffer(mouseEvent);
}

 void Mouse::onRRelease(int _x, int _y)  noexcept
{
	rightPressured = false;
	mouseEvent.push(Event(Event::States::RRelease, *this));
	TrimBuffer(mouseEvent);
}



 void Mouse::onMove(int _x, int _y)  noexcept 
{ 
	x = _x;
	y = _y;
	mouseEvent.push(Event(Event::States::Move, *this)); 
	TrimBuffer(mouseEvent); 
}

XX(RollDown);
XX(RollUp);
XX(Invaild);

 void Mouse::onOutside(int _x, int _y)  noexcept
{
	inWindow = false;
	mouseEvent.push(Event(Event::States::Outside, *this));
	TrimBuffer(mouseEvent);
}

 void Mouse::onInside(int _x, int _y)  noexcept
{
	inWindow = true;
	mouseEvent.push(Event(Event::States::Inside, *this));
	TrimBuffer(mouseEvent);
}

#undef XX;

void Mouse::addWheelDelta(int addsion) noexcept
{
	wheelDelta += addsion;
}

int Mouse::getWheelDelta() const noexcept
{
	return wheelDelta;
}

void Mouse::onWheelDelta(int x, int y, int delta) noexcept
{
	addWheelDelta(delta);
	if (wheelDelta >= WHEEL_DELTA)
	{
		onRollUp(x, y);
		addWheelDelta(-WHEEL_DELTA);
	}
	else if (wheelDelta <= -WHEEL_DELTA)
	{
		onRollDown(x, y);
		addWheelDelta(WHEEL_DELTA);

	}
}

void Mouse::onInputRawData(int x, int y) noexcept
{
	
	rawEvent.push(RawData{x, y});
	TrimBuffer(rawEvent);
}


