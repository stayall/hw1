#ifndef  __WINDOWS__H__
#define  __WINDOWS__H__

#include <Windows.h>
#include <string>
#include <optional>
#include <memory>


#include "Exception.h"
#include "Keybord.h"
#include "Mouse.h"
#include "Graphics.h"


class Window
{
public:
	class Exception : BaseException
	{
	public:
		Exception(int line, const char* file, LRESULT lr) noexcept;
		~Exception() = default;

		virtual const char* what() const noexcept override;
		virtual const char* getType() const noexcept;
		const LRESULT getErrorCode() const noexcept;
		const std::string getErrorInfo() const noexcept;
		static const std::string TranslateError(LRESULT lr) noexcept;
		

	private:

		LRESULT lr;
	};
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
	Window(int width, int height, const LPCWSTR name) ;
	~Window();
	Window(const Window& rhs) = delete;
	Window& operator= (const Window& rhs) = delete;

	void setTitle(const std::string& title);
	Graphics& GHS();
	static std::optional<int>  ProcessMessge() noexcept;

	void disenableCursor() noexcept;
	void enableCursor() noexcept;

public:
	KeyBord kbd;
	Mouse m;

private:
	static LRESULT WINAPI MsgSetUp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT WINAPI MsgFact(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

	void showCursor();
	void showImGuiCursor();
	void confineCursor();

	void disableCursor();
	void disableImGuiCursor();
	void freeCursor();

private:
	int width, height;
	HWND hWdn;
	std::unique_ptr <Graphics> gps;
	static int count;
	
	bool isShowCursor = false;
	
};


#define CHOWN_EXCRPTION(lr) Window::Exception(__LINE__, __FILE__, lr)
#define LAST_EXCPRTION() Window::Exception(__LINE__, __FILE__, GetLastError())
#define THROW_IF_FILUIED(lr) if(lr != 0) throw  Window::Exception(__LINE__,  __FILE__, lr)

#endif // ! __WINDOWS__H__