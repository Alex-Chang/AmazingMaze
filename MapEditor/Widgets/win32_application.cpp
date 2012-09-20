
#include "../stdafx.h"
#include "win32_application.h"
#include "ui_window.h"
#include "../Events/keys.h"

//using alex::ui::events;

namespace alex
{
	namespace ui
	{
		bool Win32Application::mbExit = false;

		std::map<UINT, Win32Application::EventHandlerBase*> Win32Application::mHandlerMap;

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

		void Win32Application::exit()
		{
			mbExit = true;
		}

		bool Win32Application::handle(Window* window, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			if (mHandlerMap.find(msg) != mHandlerMap.end())
			{
				return mHandlerMap[msg]->actionEvent(window, hWnd, msg, wParam, lParam), true;
			}
			else
			{
				return false;
			}
		}

		HRESULT WINAPI Win32Application::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			if (msg == WM_CREATE)
			{
				SetWindowLong(hWnd, GWLP_USERDATA, (LONG)((LPCREATESTRUCT)lParam)->lpCreateParams);
				return 0;
			}

			Window* window = (Window*)GetWindowLong(hWnd, GWLP_USERDATA);

			if (window == NULL || !handle(window, hWnd, msg, wParam, lParam))
			{
				if (window == NULL) OutputDebugString("NULL ");

				return DefWindowProc(hWnd, msg, wParam, lParam);
			}

			return 0;
		}

		DefineEventHandler(Default)
		{
			DefWindowProc(hWnd, msg, wParam, lParam);
		}

		DefineEventHandler(Close)
		{
			bool closeWindow = false;
			window->closing(closeWindow);
			if (closeWindow)
			{
				SendMessage(hWnd, WM_DESTROY, wParam, lParam);
			}
		}

		DefineEventHandler(Destroy)
		{
			DestroyWindow(hWnd);
			window->destroy();
		}

		DefineEventHandler(MouseMove)
		{
			window->mouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		}

		DefineEventHandler(KeyDown)
		{
			window->keyDown(alex::ui::events::KeyEventArg(wParam, lParam));
		}

	}
}