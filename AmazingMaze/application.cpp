
/******************************************************************
* @FileName: Application.cpp
* @Brief   : 
* @Author  : jianqifeihong
* @DateTime: 2011-6-26 21:13:25
******************************************************************/

#include "stdafx.h"
#include "application.h"
#include "config.h"

#define	FRAME_INTERNAL	1000

//////////////////////////////////////////////////////////////////////////
Application::Application(void) : OgreApplicationBase()
{

}

//////////////////////////////////////////////////////////////////////////
Application::~Application(void)
{

}


//////////////////////////////////////////////////////////////////////////
bool Application::frameRenderingQueued(const FrameEvent& evt)
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

void Application::updateStatus()
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
void Application::createScene()
{
	mpSceneManager->setShadowColour(ColourValue(0,0,0));
}

//////////////////////////////////////////////////////////////////////////
// Add by JianQiFeiHong
void Application::setupGUI()
{
	// clean all GUIs here
	mpTrayManager->destroyWidget(mpLoadGroupProgressBar);
	mpTrayManager->destroyWidget(mpLoadFileProgressBar);
}

//////////////////////////////////////////////////////////////////////////
bool Application::keyPressed( const KeyEvent &arg )
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
bool Application::keyReleased( const KeyEvent &arg )
{
	mpCameraController->injectKeyUp(arg);
	return true;
}


//////////////////////////////////////////////////////////////////////////
bool Application::mouseMoved( const MouseEvent &arg )
{
	if (mpTrayManager->injectMouseMove(arg)) return true;

	if (arg.state.buttonDown(MB_Right))
		mpCameraController->injectMouseMove(arg);

	return true;
}

bool Application::mousePressed( const MouseEvent &arg, MouseButtonID id )
{
	if (mpTrayManager->injectMouseDown(arg, id)) return true;

	return true;
}

bool Application::mouseReleased( const MouseEvent &arg, MouseButtonID id )
{
	if (mpTrayManager->injectMouseUp(arg, id)) return true;

	return true;
}

/* tray event handle functions */
void Application::checkBoxToggled(CheckBox* box){}
void Application::itemSelected(SelectMenu* menu){}
void Application::sliderMoved(OgreBites::Slider* slider){}
void Application::labelHit(Label* label){}
void Application::buttonHit(OgreBites::Button* button){}