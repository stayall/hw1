#ifndef  __WINDOWS__H__




#include <Windows.h>

class Window
{
private:
	class WindowClass
	{
	public:
		static const LPCWSTR getName() noexcept;
		static  HINSTANCE getInstance() noexcept;

	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass& rhs) = delete;
		WindowClass& operator= (const WindowClass& rhs) = delete;


	private:
		static  constexpr LPCWSTR WindowClassName = L"Window";
		static WindowClass S_WndClass;
		HINSTANCE hInst;
	};

public:
	Window(int width, int height, const LPCWSTR name) noexcept;
	~Window();
	Window(const Window& rhs) = delete;
	Window& operator= (const Window& rhs) = delete;

private:
	static LRESULT WINAPI MsgSetUp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT WINAPI MsgFact(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

private:
	int width, height;
	HWND hWdn;
	static int count;
};

#endif // ! __WINDOWS__H__