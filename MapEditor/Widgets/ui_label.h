

#include "../stdafx.h"
#include "ui_widget.h"

namespace alex
{
	namespace ui
	{
		class Label : public Widget
		{
		public:
			virtual void draw();

		public:
			void setText(string& text);
		};
	}
}