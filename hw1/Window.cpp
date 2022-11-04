#include "Window.h"

#include <sstream>
#include "resource.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"

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
    wc.hIcon = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));
    wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));

    RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
    UnregisterClass(WindowClassName, getInstance());
}

void Window::setTitle(const std::string& title)
{
    if (SetWindowTextA(hWdn, title.c_str()))
    {
        LAST_EXCPRTION();
    }
}

Graphics& Window::GHS()
{
    return *gps;
}

Window::Window(int width, int height, const LPCWSTR name) 
    : width(width), height(height)
{
    count++;
    RECT rect;
    BOOL status;
    rect.left = 100;
    rect.right = rect.left + width;
    rect.top = 100;
    rect.bottom = rect.top + height;

  
    status = AdjustWindowRect(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU, false);
    if (status == 0)
    {
        throw LAST_EXCPRTION();
    }
     hWdn = CreateWindowEx(0, WindowClass::getName(),name, WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
        rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, WindowClass::getInstance(), this);
     
     gps = std::make_unique<Graphics>(hWdn);

     if (hWdn == nullptr)
     {
         throw LAST_EXCPRTION();
     }

     ImGui_ImplWin32_Init(hWdn);
     
     ShowWindow(hWdn, SW_SHOW);
}

Window::~Window()
{
    if (count == 0)
    {
    ImGui_ImplWin32_Shutdown();

    }
    UnregisterClass(WindowClass::getName(), WindowClass::getInstance());
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

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT Window::HandleMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    switch (uMsg)
    {
    case WM_CLOSE:
        if(--count == 0)
            PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        if (ImGui::GetIO().WantCaptureKeyboard)
        {
            break;
        }
        if (!(lParam &0x40000000) || kbd.repateIsEnble())
        {
            kbd.PressureKey(static_cast<unsigned char>(wParam));
        }
        break;
    case WM_KEYUP:
    case WM_SYSKEYUP:
        if (ImGui::GetIO().WantCaptureKeyboard)
        {
            break;
        }
        kbd.ReleaseKey(static_cast<unsigned char>(wParam));
        break;
    case WM_KILLFOCUS:
        kbd.clearStates();
        break;
    case WM_MOUSEMOVE:
    {
        const POINTS p = MAKEPOINTS(lParam);
        if (p.x >= 0 && p.x <= width && p.y >= 0 && p.y <= height)
        {
            m.onMove(p.x, p.y);
            if (!m.isInWindow())
            {
                SetCapture(hWdn);
                m.onInside(p.x, p.y);
            }
        }
        else
        {
            if (wParam & (MK_LBUTTON | MK_RBUTTON))
            {
                m.onMove(p.x, p.y);
            }
            else
            {
                ReleaseCapture();
                m.onOutside(p.x, p.y);
            }
        }
        break;
    }
    case WM_MOUSEWHEEL:
    {
        const int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
        const POINTS p = MAKEPOINTS(lParam);
        m.onWheelDelta(p.x, p.y, zDelta);
        break;
    }
    case WM_RBUTTONDOWN:
    {
        const POINTS p = MAKEPOINTS(lParam);
        m.onRPressure(p.x, p.y);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        const POINTS p = MAKEPOINTS(lParam);
        m.onLPressure(p.x, p.y);
        SetForegroundWindow(hWdn);
        break;
    }
    case WM_RBUTTONUP:
    {
        const POINTS p = MAKEPOINTS(lParam);
        m.onRRelease(p.x, p.y);
        break;
    }
    case WM_LBUTTONUP:
    {
        const POINTS p = MAKEPOINTS(lParam);
        m.onLRelease(p.x, p.y);
        break;
    }
    case WM_CHAR:
    {
        if (ImGui::GetIO().WantCaptureKeyboard)
        {
            break;
        }
        kbd.OnChar(wParam);
        break;
    }

    default:
        break;
    }

    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

Window::Exception::Exception(int line, const char* file, LRESULT lr) noexcept
    : BaseException(line, file),
        lr(lr)
{
}

const char* Window::Exception::what() const noexcept
{
    std::ostringstream ss;
    ss << getType() << std::endl << std::hex
        << "ErrorCode: " << getErrorCode() << std::endl
         << "ErrorInfo: " << getErrorInfo() << std::endl
        << getOriginString() << std::endl;

    whatBuffer = ss.str();
    return whatBuffer.c_str();;
}

const char* Window::Exception::getType() const noexcept
{
    return "Windwo Exception";
}

const LRESULT Window::Exception::getErrorCode() const noexcept
{
    return lr;
}

const std::string Window::Exception::getErrorInfo() const noexcept
{
    return TranslateError(lr);
}

const std::string Window::Exception::TranslateError(LRESULT lr) noexcept
{
    char* lpBuffer = nullptr;
    DWORD size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, lr, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), reinterpret_cast<LPTSTR>(&lpBuffer), 0, nullptr);

    if (size == 0)
    {
        return "Unkown Error Type";
    }

    std::string errorString = lpBuffer;
    LocalFree(lpBuffer);

    return errorString;
}

std::optional<int> Window::ProcessMessge() noexcept
{
    MSG msg;
  
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            return {msg.wParam};
        }
        TranslateMessage(&msg);

        DispatchMessageW(&msg);
    }

  
    return {};
  
}
