
#include <windows.h>
#include <WindowsX.h>

#include <map>
#include <list>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// windows
typedef		WNDCLASS	WindowClass;
typedef		MSG			WindowMessage;
typedef		UINT		MessageID;
typedef		WPARAM		FirstParam;
typedef		LPARAM		SecondParam;
typedef		LRESULT		Win32Result;
typedef		HINSTANCE	InstanceHandler;
typedef		HWND		WindowHandler;

// resources
typedef		HBRUSH		BrushHandler;
typedef		UINT		ResourceID;