

#include "stdafx.h"
#include "Singleton.h"


class ConfigManager : public singleton<ConfigManager>
{
	friend singleton<ConfigManager>;

public:
	void initialise(string configFileName);

	string getValue(string key, string defaultValue);

	void setValue(string key, string value);

protected:
	ConfigMap mConfigMap;

private:
	// prevent user to construct another instance
	ConfigManager()	{	}
	ConfigManager(ConfigManager& other)	{	}
};
