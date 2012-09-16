
#pragma once;

#include <Windows.h>
#include <string>

class Window
{
public:
	Window(char* name, char* title);

	void show();

	~Window();

protected:
	virtual	void draw() const;

	virtual void mouseMove(int x, int y);

	//virtual void mouseUp(MouseButton button, int x, int y);

	//virtual void mouseDown(MouseButton button, int x, int y);

	//virtual void mouseWheel(MouseWheelDirection direction);

	virtual HRESULT winProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	bool createWindow(char*, char*);

	static bool registerWindow(const std::string& className);

	friend class Win32Application;

protected:
	HINSTANCE mInstance;

	HWND mWinHandle;

	bool mbExit;
};


