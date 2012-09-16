
#include "Win32Window.h"
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "Win32Application.h"

Window::Window(char* name, char* title)
: mbExit(false)
{
	createWindow(name, title);

	MSG msg;
	while (!mbExit)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			draw();
		}
	}

	DestroyWindow(mWinHandle);
}

Window::~Window()
{
	mbExit = true;
}

void Window::show()
{
	ShowWindow(mWinHandle, SW_SHOWNORMAL);

	UpdateWindow(mWinHandle);
}

bool Window::registerWindow(const std::string& className)
{
	static std::vector<std::string> registeredClasses;

	if (std::find(registeredClasses.begin(), registeredClasses.end(), className) != registeredClasses.end())
	{
		return true;
	}

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

	ATOM ret = RegisterClass(&wc);

	return ret != 0 ? (registeredClasses.push_back(className), true) : false;
}

bool Window::createWindow(char* classname, char* windowtitle)
{
	mInstance = GetModuleHandle(NULL);

	registerWindow(classname);

	mWinHandle = CreateWindowEx(0, classname, windowtitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, mInstance, this);

	if(!mWinHandle) return false;

	ShowWindow(mWinHandle, SW_SHOWNORMAL);
	UpdateWindow(mWinHandle);

	return true;
}

void Window::mouseMove(int x, int y)
{
	OutputDebugString("mouse move");
}

void Window::draw() const
{
	//OutputDebugString("draw");
}

HRESULT Window::winProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MOUSEMOVE:		mouseMove(0, 0);				break;
	case WM_PAINT:			draw();							break;
	case WM_CLOSE:			mbExit = true;					break;
	default:				return 0;			    		break;
	}

	return 0;
}