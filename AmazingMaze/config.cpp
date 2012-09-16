
#include "stdafx.h"
#include "config.h"

void ConfigManager::initialise(string configFileName)
{
	fstream stream(configFileName.c_str(), ios_base::in);

	char szBuffer[1024] = {'\0'};

	mConfigMap.clear();

	while (stream.good() && !stream.eof())
	{
		stream.getline(szBuffer, 1024);
		string line = szBuffer;
		int equalIndex = line.find('=');
		if (equalIndex != -1)
		{
			string key = line.substr(0, equalIndex);
			string val = line.substr(equalIndex + 1);
			mConfigMap[key] = val;
		}
	}
}

string ConfigManager::getValue(string key, string defaultValue)
{
	return mConfigMap.find(key) == mConfigMap.end() ? defaultValue : mConfigMap[key];
}

void ConfigManager::setValue(string key, string value)
{
	mConfigMap[key] = value;
}