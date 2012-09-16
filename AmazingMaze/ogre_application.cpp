
/******************************************************************
* @FileName: Application.cpp
* @Brief   : 
* @Author  : jianqifeihong
* @DateTime: 2011-6-26 21:13:25
******************************************************************/

#include "stdafx.h"
#include "ogre_application.h"
#include "config.h"

#define	FRAME_INTERNAL	1000

//////////////////////////////////////////////////////////////////////////
OgreApplicationBase::OgreApplicationBase(void)
:mpRoot(NULL),
mpCamera(NULL),
mpSceneManager(NULL),
mpWindow(NULL),
mpTrayManager(NULL),
mpCameraController(NULL),
mpDetailPanel(NULL),
mpInputManager(NULL),
mpLoadGroupProgressBar(NULL),
mpMouse(NULL),
mpKeyboard(NULL),
mbShutdown(false)
{

}

//////////////////////////////////////////////////////////////////////////
OgreApplicationBase::~OgreApplicationBase(void)
{

	if (mpTrayManager != NULL)
	{
		delete mpTrayManager;
		mpTrayManager = NULL;
	}
	if (mpCameraController != NULL)
	{
		delete mpCameraController;
		mpCameraController = NULL;
	}

	//Remove the Window listener from this class
	WindowEventUtilities::removeWindowEventListener(mpWindow, this);
	windowClosed(mpWindow);
	delete mpRoot;
	mpRoot = NULL;
}

//////////////////////////////////////////////////////////////////////////
bool OgreApplicationBase::configure(bool bShowDialog /*= false*/)
{
	LOG("*********************** Configuring ***********************");
	if (bShowDialog)
	{
		return mpRoot->showConfigDialog();
	}
	else
	{
		if(!mpRoot->restoreConfig())
		{
			return mpRoot->showConfigDialog();
		}
	}
	LOG("\n");
	return true;
}

//////////////////////////////////////////////////////////////////////////
void OgreApplicationBase::initialiseInput()
{
	LOG("********************* Initializing OIS ********************");
	ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mpWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mpInputManager = InputManager::createInputSystem( pl );

	mpKeyboard = static_cast<Keyboard*>(mpInputManager->createInputObject( OISKeyboard, true ));
	mpMouse = static_cast<Mouse*>(mpInputManager->createInputObject( OISMouse, true ));

	mpMouse->setEventCallback(this);
	mpKeyboard->setEventCallback(this);

	//Set initial mouse clipping size
	windowResized(mpWindow);

	//Register as a Window listener
	WindowEventUtilities::addWindowEventListener(mpWindow, this);
	mpMouse->capture();
	LOG("\n");
}

//////////////////////////////////////////////////////////////////////////
void OgreApplicationBase::createFrameListener()
{
	mpTrayManager = new SdkTrayManager("InterfaceName", mpWindow, mpMouse, this);
	mpTrayManager->showFrameStats(TL_BOTTOMLEFT);

	// create a params panel for displaying sample details
	StringVector items;
	items.push_back("cam.pX");
	items.push_back("cam.pY");
	items.push_back("cam.pZ");
	items.push_back("");
	items.push_back("cam.oW");
	items.push_back("cam.oX");
	items.push_back("cam.oY");
	items.push_back("cam.oZ");
	items.push_back("");
	items.push_back("Pos.X");
	items.push_back("Pos.Y");
	items.push_back("Pos.Z");
	items.push_back("");
	items.push_back("For.X");
	items.push_back("For.Y");
	items.push_back("For.Z");
	items.push_back("");
	items.push_back("Voc.X");
	items.push_back("Voc.Y");
	items.push_back("Voc.Z");
	items.push_back("Speed");

	mpDetailPanel = mpTrayManager->createParamsPanel(TL_TOPRIGHT, "DetailsPanel", 200, items);

	mpRoot->addFrameListener(this);
}
//////////////////////////////////////////////////////////////////////////
void OgreApplicationBase::destroyScene()
{

}

//////////////////////////////////////////////////////////////////////////
void OgreApplicationBase::createCamera()
{
	// Create the camera
	mpCamera = mpSceneManager->createCamera("MainCamera");

	mpCamera->setNearClipDistance(5);
	mpCamera->setFarClipDistance(10000);

	// create a default camera controller
	mpCameraController = new CameraController(mpCamera);
}

//////////////////////////////////////////////////////////////////////////
void OgreApplicationBase::createViewports()
{
	// Create one viewport, entire window
	Viewport* vp = mpWindow->addViewport(mpCamera);
	vp->setBackgroundColour(ColourValue(0,0,0));

	// Alter the camera aspect ratio to match the viewport
	float width = vp->getActualWidth(), height = vp->getActualHeight();
	mpCamera->setAspectRatio(width / height);
}
//////////////////////////////////////////////////////////////////////////
void OgreApplicationBase::locateResource()
{
	// Load resource paths from config file
	ConfigFile cf;
#ifdef _DEBUG
	cf.load("resources_d.cfg");
#else
	cf.load("resources.cfg");
#endif


	// Go through all sections & settings in the file
	ConfigFile::SectionIterator seci = cf.getSectionIterator();

	String secName, typeName, archName;

	LOG("******************* declaring resources *******************");

	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		ConfigFile::SettingsMultiMap *settings = seci.getNext();
		ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}
	LOG("\n");
}
//////////////////////////////////////////////////////////////////////////
void OgreApplicationBase::createResourceListener()
{
	FontManager::getSingleton().getByName("SdkTrays/Caption")->load();
	mpLoadGroupProgressBar = mpTrayManager->createProgressBar(TL_CENTER, "LoadGroupProgressBar", "Loading group, please wait...", 700, 300);//TODO:alter the length of group progress bar
	mpLoadFileProgressBar  = mpTrayManager->createProgressBar(TL_CENTER, "LoadFilesProgressBar", "Loading files, please wait...", 700, 300);//TODO:alter the length of file progress bar
	mpLoadGroupProgressBar->show();
	mpLoadFileProgressBar->show();
	bind(mpWindow, mpLoadGroupProgressBar, mpLoadFileProgressBar);
	ResourceGroupManager::getSingleton().addResourceGroupListener(this);
}
//////////////////////////////////////////////////////////////////////////
void OgreApplicationBase::loadResource()
{
	LOG("******************** Loading Resources ********************");
	ResourceGroupManager::getSingleton().initialiseResourceGroup("Popular");
	ResourceGroupManager::getSingleton().initialiseResourceGroup("General");
	mpLoadGroupProgressBar->setProgress(1);
	ResourceGroupManager::getSingleton().removeResourceGroupListener(this);
	mpWindow->update();

	LOG("\n");

	// load config
	ConfigManager::getsingleton().initialise("universe.cfg");
}
//////////////////////////////////////////////////////////////////////////
void OgreApplicationBase::go()
{
	if (!setup())
		return;

	mpRoot->startRendering();

	// clean up
	destroyScene();
}

//////////////////////////////////////////////////////////////////////////
bool OgreApplicationBase::setup()
{
	if (!createRoot() || !configure())
		return false;

	LOG("********************* Initialising OGRE *********************");
	mpWindow = mpRoot->initialise(true, "½£Æð·Éºç");
	LOG("\n");

	initialiseInput();

	locateResource();

	mpSceneManager = mpRoot->createSceneManager(ST_GENERIC, "SceneManager");

	LOG("**************** Loading Essential Resources ****************");
	ResourceGroupManager::getSingleton().initialiseResourceGroup("Essential");
	LOG("\n");

	createFrameListener();
	createResourceListener();

	createCamera();

	createViewports();

	loadResource();

	createScene();

	TextureManager::getSingleton().setDefaultNumMipmaps(5);

	setupGUI();

	windowResized(mpWindow);

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool OgreApplicationBase::createRoot()
{
	String pluginFile;
#ifdef _DEBUG 
	pluginFile = "plugins_d.cfg";
#else
	pluginFile = "plugins.cfg";
#endif

	mpRoot = new Root(pluginFile);

	LOG("\n");
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool OgreApplicationBase::frameRenderingQueued(const FrameEvent& evt)
{
	if(mpWindow->isClosed() || mbShutdown) return false;

	//Need to capture/update each device
	mpKeyboard->capture();
	mpMouse->capture();

	mpTrayManager->frameRenderingQueued(evt);

	if (!mpTrayManager->isDialogVisible())
	{
		mpCameraController->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
		//updateStatus();
	}

	return true;
}

void OgreApplicationBase::updateStatus()
{
	if (mpDetailPanel->isVisible())   // if details panel is visible, then update its contents
	{
		mpDetailPanel->setParamValue(0, StringConverter::toString(mpCamera->getDerivedPosition().x));
		mpDetailPanel->setParamValue(1, StringConverter::toString(mpCamera->getDerivedPosition().y));
		mpDetailPanel->setParamValue(2, StringConverter::toString(mpCamera->getDerivedPosition().z));
		mpDetailPanel->setParamValue(4, StringConverter::toString(mpCamera->getDerivedOrientation().w));
		mpDetailPanel->setParamValue(5, StringConverter::toString(mpCamera->getDerivedOrientation().x));
		mpDetailPanel->setParamValue(6, StringConverter::toString(mpCamera->getDerivedOrientation().y));
		mpDetailPanel->setParamValue(7, StringConverter::toString(mpCamera->getDerivedOrientation().z));
	}
}

//////////////////////////////////////////////////////////////////////////
// Create the scene!
void OgreApplicationBase::createScene()
{
	mpSceneManager->setShadowColour(ColourValue(0,0,0));
}

//////////////////////////////////////////////////////////////////////////
// Add by JianQiFeiHong
void OgreApplicationBase::setupGUI()
{
	// clean all GUIs here
	mpTrayManager->destroyWidget(mpLoadGroupProgressBar);
	mpTrayManager->destroyWidget(mpLoadFileProgressBar);
}

void OgreApplicationBase::shutdown()
{

}

//////////////////////////////////////////////////////////////////////////
bool OgreApplicationBase::keyPressed( const KeyEvent &arg )
{
	switch (arg.key)
	{
	case KC_SYSRQ:
		Root::getSingleton().getAutoCreatedWindow()->writeContentsToTimestampedFile("screenshot", ".jpg");
		break;
	case KC_ESCAPE:
		mbShutdown = true;
		break;
	}

	if (mpTrayManager->isDialogVisible())
		return true;   // don't process any more keys if dialog is up

	mpCameraController->injectKeyDown(arg);

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool OgreApplicationBase::keyReleased( const KeyEvent &arg )
{
	mpCameraController->injectKeyUp(arg);
	return true;
}

//////////////////////////////////////////////////////////////////////////
//Adjust mouse clipping area
void OgreApplicationBase::windowResized(RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const MouseState &ms = mpMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

//////////////////////////////////////////////////////////////////////////
//Unattach OIS before window shutdown (very important under Linux)
void OgreApplicationBase::windowClosed(RenderWindow* rw)
{
	//Only close for window that created OIS (the main window in these demos)
	if( rw == mpWindow )
	{
		if( mpInputManager )
		{
			mpInputManager->destroyInputObject( mpMouse );
			mpInputManager->destroyInputObject( mpKeyboard );
			InputManager::destroyInputSystem(mpInputManager);
			mpInputManager = 0;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
bool OgreApplicationBase::mouseMoved( const MouseEvent &arg )
{
	if (mpTrayManager->injectMouseMove(arg)) return true;

	if (arg.state.buttonDown(MB_Right))
		mpCameraController->injectMouseMove(arg);

	return true;
}

bool OgreApplicationBase::mousePressed( const MouseEvent &arg, MouseButtonID id )
{
	if (mpTrayManager->injectMouseDown(arg, id)) return true;

	return true;
}

bool OgreApplicationBase::mouseReleased( const MouseEvent &arg, MouseButtonID id )
{
	if (mpTrayManager->injectMouseUp(arg, id)) return true;

	return true;
}

/* tray event handle functions */
void OgreApplicationBase::checkBoxToggled(CheckBox* box){}
void OgreApplicationBase::itemSelected(SelectMenu* menu){}
void OgreApplicationBase::sliderMoved(OgreBites::Slider* slider){}
void OgreApplicationBase::labelHit(Label* label){}
void OgreApplicationBase::buttonHit(OgreBites::Button* button){}