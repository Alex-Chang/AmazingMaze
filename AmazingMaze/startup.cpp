
#include "stdafx.h"
#include "Application.h"

INT32 WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	Application app;

	try
	{
		app.go();
	}
	catch(Ogre::Exception &e)
	{
		MessageBox(NULL, e.getFullDescription().c_str(), "OGRE ERROR", MB_OK);
	}
	catch (std::exception* e)
	{
		MessageBox(NULL, e->what(), "SYSTEM ERROR", MB_OK);
	}
}