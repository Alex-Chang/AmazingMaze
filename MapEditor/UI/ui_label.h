

#include "shape.h"

class Label : public Widget
{
public:
	virtual void draw();

public:
	void setText(string& text);
};