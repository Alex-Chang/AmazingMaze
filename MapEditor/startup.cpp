
#include "stdafx.h"
#include "Widgets/ui.h"
#include "Widgets/win32_application.h"


int CALLBACK WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	{
		alex::ui::Window win(string("MapEditor"), string("Map Editor"));
		win.show();
		
		alex::ui::Win32Application::go();
	}

	return 0;
}