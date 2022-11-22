#include "Keybord.h"
#include <optional>

bool KeyBord::IsPressureKey(unsigned char code) const noexcept
{
	return keybordStates[code];
}

bool KeyBord::keyIsEmpty() const noexcept
{
	return keybuffer.empty();
}

KeyBord::Event KeyBord::readKey() noexcept
{
	if (keybuffer.size() > 0u)
	{
		Event e =  keybuffer.front();
		keybuffer.pop();
		return e;
	};

	return Event();
}

void KeyBord::flushKeyBuffer() noexcept
{
	clear(keybuffer);
}

bool KeyBord::charIsEmpty() const noexcept
{
	return charbuffer.empty();
}

char KeyBord::readChar() noexcept
{
	if (charbuffer.size() > 0u)
	{
		char e = charbuffer.front();
		charbuffer.pop();
		return e;
	};

	return 0u;
}

void KeyBord::flushCharBuffer() noexcept
{
	clear(charbuffer);
}

void KeyBord::flush() noexcept
{
	clear(keybuffer);
	clear(charbuffer);
}

void KeyBord::enableRepate() noexcept
{
	autoRepetEnable = true;
}

void KeyBord::disenableRepate() noexcept
{
	autoRepetEnable = false;

}

bool KeyBord::repateIsEnble() const noexcept
{
	return autoRepetEnable;
}

void KeyBord::PressureKey(unsigned char code) noexcept
{
	keybordStates[code] = true;
	keybuffer.push(Event(Event::States::Pressure, code));
	TrimBuffer(keybuffer);

}

void KeyBord::ReleaseKey(unsigned char code) noexcept
{
	keybordStates[code] = false;
	keybuffer.push(Event(Event::States::Release, code));
	TrimBuffer(keybuffer);
}

void KeyBord::OnChar(char c) noexcept
{
	charbuffer.push(c);
	TrimBuffer(keybuffer);
}

void KeyBord::clearStates() noexcept
{
	keybordStates.reset();
}
