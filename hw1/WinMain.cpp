#include "Window.h"

LRESULT CALLBACK Wndproc(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{

    
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(69);
        break;
    default:
        break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow)
{
  /* const LPCWSTR WndClassName = L"first class";

    WNDCLASSEX wc;
    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = Wndproc;
    wc.lpszClassName = WndClassName;
    wc.style = CS_OWNDC;
    wc.hbrBackground = nullptr;
   
    RegisterClassEx(&wc);

    HWND hwnd = CreateWindowEx(0, WndClassName, L"first window", WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
        400, 200, 400, 500, nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hwnd, SW_SHOW);*/

    Window wnd1(200, 200, L"s");
    Window wnd2(800, 900, L"s");

    MSG msg;
    BOOL result;
    while ((result = GetMessage(&msg, NULL, 0, 0)) > 0)
    {
        TranslateMessage(&msg);

        DispatchMessageW(&msg);
    }

    if (result == -1)
    {
        return -1;
    }
    else
    {
        return msg.wParam;
    }

    return 0;
}