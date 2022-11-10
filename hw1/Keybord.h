#ifndef  __KEYBORD__H__
#define __KEYBORD__H__

#include <queue>
#include <bitset>
#include "Mouse.h"

class KeyBord
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class States
		{
			Pressure,
			Release,
			Invaild
		};

	public:
		Event() noexcept
			: state(States::Invaild), code(0u) {};
		Event(States state, unsigned char code) noexcept
			: state(state), code(code) {};

		bool IsPressure() const noexcept
		{
			return state == States::Pressure;
		}
		bool IsRelease() const noexcept
		{
			return state == States::Release;
		}
		bool IsInvaild() const noexcept
		{
			return state == States::Invaild;
		}

		const unsigned char getState() const noexcept
		{
			return code;
		}

		

	private:
		States state;
		unsigned char code;
	};

public:
	KeyBord() = default;
	KeyBord(const KeyBord&) = delete;
	KeyBord& operator=(const KeyBord&) = delete;

public:

	bool IsPressureKey(unsigned char code) const noexcept;
	
	bool keyIsEmpty() const noexcept;

	Event readKey() noexcept;
	void flushKeyBuffer() noexcept;


	bool charIsEmpty() const noexcept;
	char readChar()  noexcept;
	void flushCharBuffer() noexcept;


	void flush() noexcept;
	
	
private:
	void enableRepate() noexcept;
	void disenableRepate() noexcept;
	bool repateIsEnble() const noexcept;

	void PressureKey(unsigned char code) noexcept;
	void ReleaseKey(unsigned char code) noexcept;
	void OnChar(char c) noexcept;
	void clearStates() noexcept;
	template<typename T>
	static void TrimBuffer(std::queue<T> &q) noexcept;
	template<typename T>
	static void clear(std::queue<T> &q) noexcept;
	
private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	std::bitset<nKeys> keybordStates;
	std::queue<Event> keybuffer;
	std::queue<char> charbuffer;

	bool autoRepetEnable = false;


};

#endif // ! __KEYBORD__H__

template<typename T>
inline void KeyBord::TrimBuffer(std::queue<T> &q) noexcept
{
	if (q.size() > bufferSize)
	{
		q.pop();
	}
}

template<typename T>
inline void KeyBord::clear(std::queue<T> &q) noexcept
{
	std::queue<T> empty;
	std::swap(empty, q);
}
