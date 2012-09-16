
// ogre
#include <Ogre.h>
#include <OIS.h>
#include <SdkTrays.h>

// stl
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <limits>

// stdio
#include <fstream>
#include <stdio.h>
#include <strstream>

// windows
#include <Windows.h>

// xml
#include "rapidxml.hpp"

// self
#include "Singleton.h"

using namespace std;
using namespace OIS;
using namespace Ogre;
using namespace OgreBites;
using namespace rapidxml;
using namespace Alex;

typedef		std::map<string, string>	ConfigMap;
typedef		ConfigMap::iterator			ConfigIterator;

typedef		std::vector<string>			FileList;
typedef		FileList::iterator			FileIterator;

typedef		std::vector<string>			StringList;
typedef		StringList::iterator		StringIterator;

typedef		Ogre::Vector3				Force;
typedef		Ogre::Vector3				Velocity;
typedef		Ogre::Vector3				Position;