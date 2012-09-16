
#include "stdafx.h"
#include "shape.h"

class Property : Shape
{
private:
	string mName;
	
	string mDescription;
	
	string mImageFile;

public:
	inline const string& getName() const;

	inline const string& getDescription() const;

	inline const string& getImageFile() const;

	inline void setName(const string& name);

	inline void setDescription(const string& description);

	inline void setImageFile(const string& imageFile);
};
