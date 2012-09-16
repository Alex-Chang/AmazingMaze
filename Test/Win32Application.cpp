
#include "Win32Application.h"
#include "Win32Window.h"
#include <WindowsX.h>

void Win32Application::go()
{
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
			//draw();
		}
	}
}

HRESULT Win32Application::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_CREATE)
	{
		SetWindowLong(hWnd, GWLP_USERDATA, (LONG)((LPCREATESTRUCT)lParam)->lpCreateParams);
		return 0;
	}

	Window* window = (Window*)GetWindowLong(hWnd, GWLP_USERDATA);

	if (window == NULL) OutputDebugString("NULL ");


	return window != NULL && window->winProc(hWnd, msg, wParam, lParam) ?
		0 :	(OutputDebugString("dfd "), DefWindowProc(hWnd, msg, wParam, lParam));
}