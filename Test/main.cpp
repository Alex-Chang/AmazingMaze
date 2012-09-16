
#include "Win32Window.h"



int CALLBACK WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	Window window("classname1", "window 1");
	window.show();

	//Window window2("classname1", "window 2");
	//window2.show();

	return 0;
}