
#include "../stdafx.h"
#include "ui_widget.h"

namespace alex
{
	namespace ui
	{
		class PictureBox : public Widget
		{
		public:
			virtual void draw() const;

		public:
			void setImageFile(string& imageFile);

			void setImage(ResourceID resourceID);
		};
	}
}