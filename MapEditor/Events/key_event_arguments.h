
#pragma once

#include "../stdafx.h"
#include "event_arguments.h"

namespace alex
{
	namespace ui
	{
		namespace events
		{
			class KeyEventArg : public EventArg
			{
			public:
				KeyEventArg(WPARAM wParam, LPARAM lParam)
					: EventArg(wParam, lParam)
				{
				}

				Keys key() const 
				{
					return static_cast<Keys>(_wParam);
				}

				int repeatCount() const
				{
					return _lParam & 0x7fff;
				}

				bool prevState() const
				{
					return (_lParam & 0x2000) == 0x2000;
				}
			};
		}
	}
}
