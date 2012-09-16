
#include "../stdafx.h"
#include "ui_window.h"
#include "../win32_application.h"
#include "../win_msg_handler.h"

Window::Window(std::string className, std::string windowTitle)
{
	createWin32Window(className, windowTitle);
}

void Window::show() const
{
	ShowWindow(mhWnd, SW_SHOWNORMAL);

	UpdateWindow(mhWnd);
}

void Window::createWin32Window(std::string className, std::string windowTitle)
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = (WNDPROC)&Win32Application::WinProc;
	wc.lpszClassName = className.c_str();
	wc.lpszMenuName = NULL;
	wc.style = 0;

	RegisterClass(&wc);

	mhWnd = CreateWindowEx(0, className.c_str(), windowTitle.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, wc.hInstance, this);
}

void Window::draw() const
{
	// draw something here
}


HRESULT Window::winProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT: draw(); break;
	default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

void Window::mouseMove(int x, int y)
{
	char szText[20] = {0};
	sprintf_s(szText, 20, "(%d, %d)\t", x, y);
	OutputDebugString(szText);
}

void Window::keyDown(int key)
{
	if (key == VK_ESCAPE)
	{
		SendMessage(mhWnd, WM_DESTROY, 0, 0);
	}
}

void Window::closing(bool& close)
{
	close = MessageBox(mhWnd, "quit ?", "info", MB_YESNO) == IDYES;
}

void Window::destroy()
{
	MessageBox(mhWnd, "destroyed", "info", MB_OK);
	Win32Application::exit();
}

