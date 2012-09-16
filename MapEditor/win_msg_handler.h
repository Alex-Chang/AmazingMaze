
#include "stdafx.h"

class EventManager
{
public:
	struct EventHandler
	{
		virtual void actionEvent(void* fun, WPARAM w, LPARAM l) = 0;
	};

	static std::map<UINT, EventHandler*> FunctionMap;

	static bool winProc(UINT msg, void* fun, WPARAM w, LPARAM l)
	{
		FunctionMap[msg]->actionEvent(fun, w, l);
	}

	

	typedef void (Window::*CloseHandler)();
	struct Close : public EventHandler
	{
		static Close handler;

		Close()
		{
			FunctionMap[WM_CLOSE] = this;
		}

		virtual void actionEvent(void* fun, WPARAM w, LPARAM l)
		{
			//CloseHandler f = (CloseHandler)fun;
			//f();
		}
	};

	typedef void (Window::*MouseMoveFun)(int, int);
	struct MouseMove : public EventHandler
	{
		static MouseMove handler;

		MouseMove()
		{
			FunctionMap[WM_MOUSEMOVE] = this;
		}

		virtual void actionEvent(void* fun, WPARAM w, LPARAM l)
		{
			//int x = GET_X_LPARAM(l), y = GET_Y_LPARAM(l);
			//fun(x, y);
		}
	};
};