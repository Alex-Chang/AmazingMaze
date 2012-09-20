
#pragma once

#include "../stdafx.h"
#include <winuser.h>
#include "keys.h"

namespace alex
{
	namespace ui
	{
		namespace events
		{
			class EventArg
			{
			public:
				EventArg(WPARAM wParam, LPARAM lParam)
					: _wParam(wParam), _lParam(lParam)
				{
				}

			protected:
				WPARAM _wParam;
				LPARAM _lParam;
			};
		}
	}
}
