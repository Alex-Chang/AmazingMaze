
#include "stdafx.h"
#include "enumerations.h"
#include "UI/ui_window.h"

#define DeclareEventHandler(EventName, message)\
struct EventName##EventHandler : public EventHandlerBase\
	{\
	EventName##EventHandler()\
		{\
		mHandlerMap[message] = this;\
		}\
		\
		virtual void actionEvent(Window* window, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);\
		\
		static EventName##EventHandler handler;\
	}

#define DefineEventHandler(EventName)\
	Win32Application::EventName##EventHandler Win32Application::EventName##EventHandler::handler;\
	void Win32Application::EventName##EventHandler::actionEvent(Window* window, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)

class Win32Application
{
public:
	static HRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static void go();

	static void exit();

private:
	struct EventHandlerBase;

	static bool mbExit;

	static std::map<UINT, EventHandlerBase*> mHandlerMap;

	static bool handle(Window* window, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	struct EventHandlerBase
	{
		virtual void actionEvent(Window* window, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			DefWindowProc(hWnd, msg, wParam, lParam);
		}
	};


	DeclareEventHandler(MouseMove, WM_MOUSEMOVE);

	DeclareEventHandler(Default, 0);

	DeclareEventHandler(Close, WM_CLOSE);

	DeclareEventHandler(Destroy, WM_DESTROY);

	DeclareEventHandler(KeyDown, WM_KEYDOWN);
};

