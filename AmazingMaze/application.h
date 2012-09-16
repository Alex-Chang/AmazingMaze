
/******************************************************************
* @FileName: Application.h
* @Brief   : 
* @Author  : jianqifeihong
* @DateTime: 2011-6-26 21:03:19
******************************************************************/

#include "stdafx.h"
#include "controller.h"
#include "ogre_application.h"


class Application : public OgreApplicationBase
{
public:
	/* 
		construct function, will call all base class's construct functions. 
		initialise itself's all member varialbles.
		set all pointers to null.
	*/
	Application();

	/*
		destruct function. do 3 jobs:
		delete mpTrayManager and mpCameraMan.
		detach WindowEventListner from this class and close window.
		delete Root.
	*/
	~Application();
protected:
	//*********************************************************************
	// Method   : createScene
	// Access   : protected 
	// Returns  : void
	// Brief    : create outer scene(sky, plants, terrain, all models).
	//*********************************************************************
	void createScene();


	//*********************************************************************
	// Method   : setupGUI
	// Access   : virtual protected 
	// Returns  : void
	// Brief    : setup all wigets needed in application.
	//*********************************************************************
	virtual void setupGUI();

	
	//*********************************************************************
	// Method   : updateStatus
	// Access   : virtual protected 
	// Brief    : show some status information for every frame.
	// Returns  : void
	//*********************************************************************
	virtual void updateStatus();

	/* frame event handle functions */
	virtual bool frameRenderingQueued(const FrameEvent& evt);

	/* keyboard event handle functions */
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual bool keyPressed(const OIS::KeyEvent &arg);

	/* mouse event handle functions */
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, MouseButtonID id);

	/* tray event handle functions */
	virtual void checkBoxToggled(CheckBox* box);
	virtual void itemSelected(SelectMenu* menu);
	virtual void sliderMoved(OgreBites::Slider* slider);
	virtual void labelHit(Label* label);
	virtual void buttonHit(OgreBites::Button* button);
};