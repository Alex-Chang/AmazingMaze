
#include "win32_application.h"

class MapApplication : public Win32ApplicationBase
{
protected:
	virtual void draw();

	virtual void mouseMove(int x, int y);

	virtual void mouseDown(MouseButton button, int x, int y);

	virtual void mouseUp(MouseButton button, int x, int y);

	virtual void mouseWheel(MouseWheelDirection direction);
};
