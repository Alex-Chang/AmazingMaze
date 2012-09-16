
/******************************************************************
* @FileName: ResourceLoadListener.cpp
* @Brief   : 
* @Author  : jianqifeihong
* @DateTime: 2011-6-21 10:27:38
******************************************************************/

#include "stdafx.h"
#include "resourceload.h"

void ResourceLoadListener::bind(RenderWindow* pWindow, ProgressBar* pLoadingBar, ProgressBar* pParsingBar)
{
	mpWindow = pWindow;
	mpLoadingProgressBar = pLoadingBar;
	mpParsingProgressBar = pParsingBar;
}

void ResourceLoadListener::resourceGroupLoadStarted(const String& groupName, size_t resourceCount)
{
	mLoadingStep = 1 / (Real)resourceCount;
	mpLoadingProgressBar->setCaption("Loading file");
	mpLoadingProgressBar->setProgress(0);
	mpWindow->update();
}

void ResourceLoadListener::resourceGroupScriptingStarted(const String& groupName, size_t scriptCount)
{
	mParsingStep = 1 / (Real)scriptCount;
	mpLoadingProgressBar->setCaption("Parsing file");
	mpLoadingProgressBar->setProgress(0);
	mpWindow->update();
}

void ResourceLoadListener::resourceLoadStarted(const ResourcePtr& resource)
{
	mpLoadingProgressBar->setComment(resource->getName());
	mpLoadingProgressBar->setProgress(mpLoadingProgressBar->getProgress() + mLoadingStep);
	mpWindow->update();
}

void ResourceLoadListener::scriptParseStarted(const String& scriptName, bool& skipThisScript)
{
	mpParsingProgressBar->setComment(scriptName);
	mpParsingProgressBar->setProgress(mpParsingProgressBar->getProgress() + mParsingStep);
	mpWindow->update();
}