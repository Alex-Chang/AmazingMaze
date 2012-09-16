
/******************************************************************
* @FileName: Application.h
* @Brief   : 
* @Author  : jianqifeihong
* @DateTime: 2011-6-26 21:03:19
******************************************************************/

#include "stdafx.h"
#include "resourceload.h"
#include "controller.h"

using namespace std;
using namespace OIS;
using namespace Ogre;
using namespace OgreBites;


/* an macro that write log message into .log file. */
#define LOG(logMsg) LogManager::getSingleton().logMessage(logMsg)

/*
	
*/
class OgreApplicationBase : public FrameListener, WindowEventListener, KeyListener, MouseListener, SdkTrayListener, ResourceLoadListener
{
public:
	/* 
		construct function, will call all base class's construct functions. 
		initialise itself's all member varialbles.
		set all pointers to null.
	*/
	OgreApplicationBase();

	/*
		do 3 jobs:
		setup system: call setup() so setup the system.
		message loop: call Root::renderOneFrame() in a loop.
		cleaning up : call destroyScene() to do some cleaning work.
	*/
	void go();

	/*
		destruct function. do 3 jobs:
		delete mpTrayManager and mpCameraMan.
		detach WindowEventListner from this class and close window.
		delete Root.
	*/
	~OgreApplicationBase();
protected:
	//*********************************************************************
	// Method   : setup
	// Access   : protected 
	// Returns  : bool
	// Brief    : do too much work. create root, config, create window,
	//			  initialise input, locate resource, create scene manager,
	//			  create all listeners, camera and viewports, load resources,
	//			  create scene, load all algorithms, setup GUI, etc.
	//			  if all these work is done, return true. or return false.
	//*********************************************************************
	bool setup();


	//*********************************************************************
	// Method   : createRoot
	// Access   : protected 
	// Returns  : bool
	// Brief    : load file plugins_d.cfg or plugins.cfg 
	//			  (according to app mode 'Debug' or 'Release')
	//			  and load all plugins ,then create the only Root object.
	//			  if all plugins is loaded, return true. or return false.
	//*********************************************************************
	bool createRoot();


	//*********************************************************************
	// Method   : configure
	// Access   : protected 
	// Parameter: bool bShowDialog -default set by 'false'
	// Returns  : bool -if success ,return true. or return false.
	// Brief    : if param 'bShowDialog' is true, then show config dialog.
	//			  if param is false, autolly config by config file.
	//			  if failed to config by config file, then show config dialog.
	//*********************************************************************
	bool configure(bool bShowDialog = false);


	// TODO: no use. delete setupInput() from Application.
	bool setupInput();


	//*********************************************************************
	// Method   : createCamera
	// Access   : protected 
	// Returns  : void
	// Brief    : create camera, initialise it, and create camera man.
	//*********************************************************************
	void createCamera();


	//*********************************************************************
	// Method   : createFrameListener
	// Access   : protected 
	// Returns  : void
	// Brief    : create frame listener, frame state panel and details panel.
	//*********************************************************************
	void createFrameListener();


	//*********************************************************************
	// Method   : createResourceListener
	// Access   : protected 
	// Returns  : void
	// Brief    : load font. create and show two progress bars. create resource load listener.
	//*********************************************************************
	void createResourceListener();


	//*********************************************************************
	// Method   : createViewports
	// Access   : protected 
	// Returns  : void
	// Brief    : create viewport according to camera and initialise it.
	//*********************************************************************
	void createViewports();


	//*********************************************************************
	// Method   : locateResource
	// Access   : protected 
	// Returns  : void
	// Brief    : load file 'resource_d.cfg' or 'resource.cfg'(according to app mode 'Debug' or 'Release')
	//			  and then add all resources' location(filesystem or pack) in this config file.
	//*********************************************************************
	void locateResource();


	//*********************************************************************
	// Method   : loadResource
	// Access   : protected 
	// Returns  : void
	// Brief    : load all resources according to locations added by function locationResources()
	//			  and update two progress bars at the same time.
	//*********************************************************************
	void loadResource();


	//*********************************************************************
	// Method   : destroyScene
	// Access   : protected 
	// Returns  : void
	// Brief    : do some work to clean the scene.
	//*********************************************************************
	void destroyScene();


	//*********************************************************************
	// Method   : initialiseInput
	// Access   : protected 
	// Returns  : void
	// Brief    : create keyboard and mouse input objects and add input event listener to the window.
	//*********************************************************************
	void initialiseInput();


	//*********************************************************************
	// Method   : createScene
	// Access   : protected 
	// Returns  : void
	// Brief    : create outer scene(sky, plants, terrain, all models).
	//*********************************************************************
	virtual void createScene();


	//*********************************************************************
	// Method   : setupGUI
	// Access   : virtual protected 
	// Returns  : void
	// Brief    : setup all wigets needed in application.
	//*********************************************************************
	virtual void setupGUI();


	//*********************************************************************
	// Method   : shutdown
	// Access   : virtual protected 
	// Returns  : void
	// Brief    : do some cleaning work after cleaning scene.
	//*********************************************************************
	virtual void shutdown();

	
	//*********************************************************************
	// Method   : updateStatus
	// Access   : virtual protected 
	// Brief    : show some status information for every frame.
	// Returns  : void
	//*********************************************************************
	virtual void updateStatus();

	/* frame event handle functions */
	virtual bool frameStarted(const FrameEvent& evt)	{return true;}
	virtual bool frameRenderingQueued(const FrameEvent& evt);
	virtual bool frameEnded(const FrameEvent& evt)		{return true;}

	/* window event handle functions */
	virtual void windowResized(RenderWindow* rw);
	virtual void windowMoved(RenderWindow* rw)			{}
	virtual bool windowClosing(RenderWindow* rw)		{return true;}
	virtual void windowClosed(RenderWindow* rw);
	//virtual void windowFocusChange(RenderWindow* rw);

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
protected:

	// the pointer to the only one scene manager
	SceneManager* mpSceneManager;

	// the pointer to the only one Root object
	Root* mpRoot;

	// the pointer to the only one tray manager
	SdkTrayManager* mpTrayManager;

	// the pointer to the render window
	RenderWindow* mpWindow;

	// the pointer to the input manager
	InputManager* mpInputManager;

	// the pointer to the mouse object
	Mouse* mpMouse;

	// the pointer to the keyboard object
	Keyboard* mpKeyboard;

	// the pointer to the camera man
	CameraController* mpCameraController;

	// the pointer to the camera
	Camera* mpCamera;

	// the pointer to the detail panel
	ParamsPanel* mpDetailPanel;

	// the pointer to the progress bar (specify that how many group loaded)
	ProgressBar* mpLoadGroupProgressBar;

	// the pointer to the progress bar (specify that the loading progress in current group)
	ProgressBar* mpLoadFileProgressBar;

	// specify whether the system will shutdown. if hit 'ESC', this will be true.
	bool mbShutdown;
};