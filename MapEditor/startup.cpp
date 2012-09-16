
#include "stdafx.h"
#include "UI/ui_window.h"
#include "win32_application.h"


int CALLBACK WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	{
		Window win(string("MapEditor"), string("Map Editor"));
		win.show();
		
		Win32Application::go();
	}

	return 0;
}