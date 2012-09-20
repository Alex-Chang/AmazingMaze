
#pragma once

#include "../stdafx.h"
#include "../Events/mouse_buttons.h"
#include "../Events/key_event_arguments.h"
#include "ui_widget.h"
#include "../Events/key_event_arguments.h"

namespace alex
{
	namespace ui
	{
		class Window : public Widget
		{
			friend class Win32Application;
		public:
			Window(std::string className, std::string windowTitle);

			void show() const;

		protected:
			virtual void draw() const;

			virtual void mouseMove(int x, int y);

			virtual void keyDown(events::KeyEventArg e);

			virtual void closing(bool& close);

			virtual void destroy();

			virtual LRESULT winProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		private:
			void createWin32Window(std::string className, std::string windowTitle);

		protected:
			HWND mhWnd;
		};
	}
}