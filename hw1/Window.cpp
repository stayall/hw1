#include "Window.h"


Window::WindowClass Window::WindowClass::S_WndClass;
int  Window::count = 0;

const LPCWSTR Window::WindowClass::getName() noexcept
{
	return WindowClassName;
}

HINSTANCE Window::WindowClass::getInstance() noexcept
{
	return S_WndClass.hInst;
}

Window::WindowClass::WindowClass() noexcept : hInst(GetModuleHandle(nullptr))
{
    WNDCLASSEX wc;
    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = MsgSetUp;
    wc.lpszClassName = WindowClassName;
    wc.style = CS_OWNDC;
    wc.hInstance = getInstance();
    wc.hbrBackground = nullptr;

    RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
    UnregisterClass(WindowClassName, getInstance());
}

Window::Window(int width, int height, const LPCWSTR name) noexcept
    : width(width), height(height)
{
    count++;
    RECT rect;
    rect.left = 100;
    rect.right = rect.left + width;
    rect.top = 100;
    rect.bottom = rect.top + height;

    AdjustWindowRect(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU, false);

     hWdn = CreateWindowEx(0, WindowClass::getName(),name, WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
        rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, WindowClass::getInstance(), this);
     
     ShowWindow(hWdn, SW_SHOW);
}

Window::~Window()
{
    DestroyWindow(hWdn);
}

LRESULT __stdcall Window::MsgSetUp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    if (uMsg == WM_NCCREATE)
    {
        Window *pWnd = reinterpret_cast<Window *>(reinterpret_cast<CREATESTRUCTA*>(lParam)->lpCreateParams);

        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG>(pWnd));
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG>(MsgFact));
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT __stdcall Window::MsgFact(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    Window* pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    return pWnd->HandleMsg(hWnd, uMsg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (uMsg)
    {
    case WM_CLOSE:
        if(--count == 0)
            PostQuitMessage(0);
        break;
    default:
        break;
    }

    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}
