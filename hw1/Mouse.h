#ifndef __MOUSE__H__
#define __MOUSE__H__

#include <queue>



class Mouse
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class States
		{
			LPressure,
			RPressure,
			LRelease,
			RRelease,
			Move,
			RollDown,
			RollUp,
			Inside,
			Outside,
			Invaild
		};
	public:
		Event() noexcept : state(States::Invaild),rightPressured(false), leftPressured(false), x(0), y(0) {}
		Event(States state, const Mouse& m) noexcept 
			:state(state), x(m.getX()), y(m.getY()),
			rightPressured(m.rightIsPressured()), leftPressured(m.leftIsPressured()){}
		States getState() const noexcept;

#define XX(L) \
		bool is##L() const noexcept
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

		int getX() const noexcept;
		int getY() const noexcept;
		std::pair<int, int> getPos() const noexcept;
		bool rightIsPressured() const noexcept;
		bool leftIsPressured() const noexcept;
	private:
		States state;
		bool rightPressured;
		bool leftPressured;
		int x, y;
	};

public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;

	std::pair<int, int> getPos() const noexcept;
	int getX() const noexcept;
	int getY() const noexcept;
	bool rightIsPressured() const noexcept;
	bool leftIsPressured() const noexcept;
	bool isInWindow() const noexcept;
	bool isEmepty() const noexcept;
	Event readEvent() noexcept;
	void flush() noexcept;

private:
#define XX(L) \
		void on##L(int , int)  noexcept
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

	void addWheelDelta(int addsion) noexcept;
	int getWheelDelta() const noexcept;

	void onWheelDelta(int x, int y, int delta) noexcept;
	template<typename T>
	static void TrimBuffer(std::queue<T>& q) noexcept;
	template<typename T>
	static void clear(std::queue<T>& q) noexcept;
	
private:
	static constexpr unsigned int bufferSize = 16u;
	int x, y;
	bool rightPressured = false;
	bool leftPressured = false;
	bool inWindow = false;
	int wheelDelta = 0;
	std::queue<Event> mouseEvent;
};


template<typename T>
inline void Mouse::TrimBuffer(std::queue<T>& q) noexcept
{
	if (q.size() > bufferSize)
	{
		q.pop();
	}
}

template<typename T>
inline void Mouse::clear(std::queue<T>& q) noexcept
{
	std::queue<T> empty;
	std::swap(empty, q);
}

#endif // !__MOUSE__H__



