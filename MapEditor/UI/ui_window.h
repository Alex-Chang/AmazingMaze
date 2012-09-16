
#pragma once

#include "../enumerations.h"
#include "ui_widget.h"

class Window : public Widget
{
	friend class Win32Application;
public:
	Window(std::string className, std::string windowTitle);

	void show() const;

protected:
	virtual void draw() const;

	virtual void mouseMove(int x, int y);

	virtual void keyDown(int key);

	virtual void closing(bool& close);

	virtual void destroy();

	virtual HRESULT winProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	void createWin32Window(std::string className, std::string windowTitle);

protected:
	HWND mhWnd;
};