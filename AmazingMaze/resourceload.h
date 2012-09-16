
/******************************************************************
* @FileName: ResourceLoadListener.h
* @Brief   : 
* @Author  : jianqifeihong
* @DateTime: 2011-6-21 10:25:34
******************************************************************/

#include "stdafx.h"

#define NUM_GROUPS 2

class ResourceLoadListener : public ResourceGroupListener
{
public:
	ResourceLoadListener() : mpWindow(NULL), mpLoadingProgressBar(NULL), mpParsingProgressBar(NULL)
	{
	}
protected:
	void bind(RenderWindow* pwindow, ProgressBar* pLoadGroupBar, ProgressBar* pLoadFileBar);

	    /** This event is fired when a resource group begins parsing scripts.
		@note
			Remember that if you are loading resources through ResourceBackgroundQueue,
			these callbacks will occur in the background thread, so you should
			not perform any thread-unsafe actions in this callback if that's the
			case (check the group name / script name).
		@param groupName The name of the group 
		@param scriptCount The number of scripts which will be parsed
		*/
		virtual void resourceGroupScriptingStarted(const String& groupName, size_t scriptCount);

		/** This event is fired when a script is about to be parsed.
			@param scriptName Name of the to be parsed
			@param skipThisScript A boolean passed by reference which is by default set to 
			false. If the event sets this to true, the script will be skipped and not
			parsed. Note that in this case the scriptParseEnded event will not be raised
			for this script.
		*/
		virtual void scriptParseStarted(const String& scriptName, bool& skipThisScript);

		/** This event is fired when the script has been fully parsed.*/
		virtual void scriptParseEnded(const String& scriptName, bool skipped){}

		/** This event is fired when a resource group finished parsing scripts. */
		virtual void resourceGroupScriptingEnded(const String& groupName){}

		/** This event is fired  when a resource group begins loading.
		@param groupName The name of the group being loaded
		@param resourceCount The number of resources which will be loaded, including
            a number of stages required to load any linked world geometry
		*/
		virtual void resourceGroupLoadStarted(const String& groupName, size_t resourceCount);

		/** This event is fired when a declared resource is about to be loaded. 
		@param resource Weak reference to the resource loaded.
		*/
		virtual void resourceLoadStarted(const ResourcePtr& resource);

        /** This event is fired when the resource has been loaded. 
        */
		virtual void resourceLoadEnded(){}

        /** This event is fired when a stage of loading linked world geometry 
            is about to start. The number of stages required will have been 
            included in the resourceCount passed in resourceGroupLoadStarted.
        @param description Text description of what was just loaded
        */
		virtual void worldGeometryStageStarted(const String& description){}

        /** This event is fired when a stage of loading linked world geometry 
            has been completed. The number of stages required will have been 
            included in the resourceCount passed in resourceGroupLoadStarted.
        @param description Text description of what was just loaded
        */
		virtual void worldGeometryStageEnded(){}

        /** This event is fired when a resource group finished loading. */
		virtual void resourceGroupLoadEnded(const String& groupName){}

private:
	RenderWindow* mpWindow;
	OgreBites::ProgressBar* mpLoadingProgressBar;
	OgreBites::ProgressBar* mpParsingProgressBar;
	
	String mCurrentGroupName;
	Real mLoadingStep;
	Real mParsingStep;
};