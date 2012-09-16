

#ifndef CameraController_H
#define CameraController_H

#include "stdafx.h"

/*=============================================================================
| Utility class for controlling the camera in samples.
=============================================================================*/
class CameraController
{
public:
	CameraController(Ogre::Camera* cam)
	: mCamera(0)
	, mTarget(0)
	, mOrbiting(false)
	, mZooming(false)
	, mTopSpeed(150)
	, mVelocity(Ogre::Vector3::ZERO)
	, mGoingForward(false)
	, mGoingBack(false)
	, mGoingLeft(false)
	, mGoingRight(false)
	, mGoingUp(false)
	, mGoingDown(false)
	, mFastMove(false)
	{

		setCamera(cam);
		mCamera->setAutoTracking(false);
		mCamera->setFixedYawAxis(true);
	}

	virtual ~CameraController() {}

	/*-----------------------------------------------------------------------------
	| Swaps the camera on our camera man for another camera.
	-----------------------------------------------------------------------------*/
	virtual void setCamera(Ogre::Camera* cam)
	{
		mCamera = cam;
	}

	virtual Ogre::Camera* getCamera()
	{
		return mCamera;
	}

	virtual Ogre::SceneNode* getTarget()
	{
		return mTarget;
	}

	/*-----------------------------------------------------------------------------
	| Sets the camera's top speed. Only applies for free-look style.
	-----------------------------------------------------------------------------*/
	virtual void setTopSpeed(Ogre::Real topSpeed)
	{
		mTopSpeed = topSpeed;
	}

	virtual Ogre::Real getTopSpeed()
	{
		return mTopSpeed;
	}

	/*-----------------------------------------------------------------------------
	| Manually stops the camera
	-----------------------------------------------------------------------------*/
	virtual void manualStop()
	{
		mGoingForward = false;
		mGoingBack = false;
		mGoingLeft = false;
		mGoingRight = false;
		mGoingUp = false;
		mGoingDown = false;
		mVelocity = Ogre::Vector3::ZERO;
	}

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt)
	{
		// build our acceleration vector based on keyboard input composite
		Ogre::Vector3 accel = Ogre::Vector3::ZERO;
		if (mGoingForward) accel += mCamera->getDirection();
		if (mGoingBack) accel -= mCamera->getDirection();
		if (mGoingRight) accel += mCamera->getRight();
		if (mGoingLeft) accel -= mCamera->getRight();
		if (mGoingUp) accel += mCamera->getUp();
		if (mGoingDown) accel -= mCamera->getUp();

		// if accelerating, try to reach top speed in a certain time
		Ogre::Real topSpeed = mFastMove ? mTopSpeed * 20 : mTopSpeed;
		if (accel.squaredLength() != 0)
		{
			accel.normalise();
			mVelocity += accel * topSpeed * evt.timeSinceLastFrame * 10;
		}
		// if not accelerating, try to stop in a certain time
		else mVelocity -= mVelocity * evt.timeSinceLastFrame * 10;

		Ogre::Real tooSmall = std::numeric_limits<Ogre::Real>::epsilon();

		// keep camera velocity below top speed and above epsilon
		if (mVelocity.squaredLength() > topSpeed * topSpeed)
		{
			mVelocity.normalise();
			mVelocity *= topSpeed;
		}
		else if (mVelocity.squaredLength() < tooSmall * tooSmall)
			mVelocity = Ogre::Vector3::ZERO;

		if (mVelocity != Ogre::Vector3::ZERO) mCamera->move(mVelocity * evt.timeSinceLastFrame);

		return true;
	}

	/*-----------------------------------------------------------------------------
	| Processes key presses for free-look style movement.
	-----------------------------------------------------------------------------*/
	virtual void injectKeyDown(const OIS::KeyEvent& evt)
	{
		if (evt.key == OIS::KC_W || evt.key == OIS::KC_UP) mGoingForward = true;
		else if (evt.key == OIS::KC_S || evt.key == OIS::KC_DOWN) mGoingBack = true;
		else if (evt.key == OIS::KC_A || evt.key == OIS::KC_LEFT) mGoingLeft = true;
		else if (evt.key == OIS::KC_D || evt.key == OIS::KC_RIGHT) mGoingRight = true;
		else if (evt.key == OIS::KC_PGUP) mGoingUp = true;
		else if (evt.key == OIS::KC_PGDOWN) mGoingDown = true;
		else if (evt.key == OIS::KC_LSHIFT) mFastMove = true;
	}

	/*-----------------------------------------------------------------------------
	| Processes key releases for free-look style movement.
	-----------------------------------------------------------------------------*/
	virtual void injectKeyUp(const OIS::KeyEvent& evt)
	{
		if (evt.key == OIS::KC_W || evt.key == OIS::KC_UP) mGoingForward = false;
		else if (evt.key == OIS::KC_S || evt.key == OIS::KC_DOWN) mGoingBack = false;
		else if (evt.key == OIS::KC_A || evt.key == OIS::KC_LEFT) mGoingLeft = false;
		else if (evt.key == OIS::KC_D || evt.key == OIS::KC_RIGHT) mGoingRight = false;
		else if (evt.key == OIS::KC_PGUP) mGoingUp = false;
		else if (evt.key == OIS::KC_PGDOWN) mGoingDown = false;
		else if (evt.key == OIS::KC_LSHIFT) mFastMove = false;
	}

	/*-----------------------------------------------------------------------------
	| Processes mouse movement differently for each style.
	-----------------------------------------------------------------------------*/
	virtual void injectMouseMove(const OIS::MouseEvent& evt)
	{
		mCamera->yaw(Ogre::Degree(-evt.state.X.rel * 0.15f));
		mCamera->pitch(Ogre::Degree(-evt.state.Y.rel * 0.15f));
	}

protected:
	Ogre::Camera* mCamera;
	Ogre::SceneNode* mTarget;
	bool mOrbiting;
	bool mZooming;
	Ogre::Real mTopSpeed;
	Ogre::Vector3 mVelocity;
	bool mGoingForward;
	bool mGoingBack;
	bool mGoingLeft;
	bool mGoingRight;
	bool mGoingUp;
	bool mGoingDown;
	bool mFastMove;
};

#endif
