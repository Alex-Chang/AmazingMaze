
#include <Windows.h>
#include <algorithm>
#include <map>
#include "Win32Window.h"

class Win32Application
{
public:
	Win32Application();

	void go();

protected:
	static HRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

	friend class Window;

protected:
	HINSTANCE mInstance;

	HWND mWinHandle;

	bool mbExit;
};
