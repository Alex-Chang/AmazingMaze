
class Button : public Widget
{
public:
	virtual void draw();

public:
	void setNormalImage(Image* image);

	void setMouseOverImage(Image* image);

	void setMouseClickImage(Image* image);
};
