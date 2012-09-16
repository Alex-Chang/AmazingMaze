
#pragma once

#include "../Graphics/point.h"
#include "../Graphics/size.h"
#include "ui.h"

class Widget
{
public:
	Widget();
	const string&	getName	   ()	const;
	const string&   getText	   ()   const;

	Point	getPosition()	const;
	Size	getSize    ()	const;
	int		getLeft    ()	const;
	int		getTop     ()	const;
	int		getRight   ()	const;
	int		getButtom  ()	const;

public:
	void	setName    (std::string& name            );
	void	setText	   (string& text            );
	void	setPosition(int x, int y            );
	void	setPosition(const Position& position);
	void	setSize    (int width, int height   );
	void	setSize    (const Size& size        );

public:
	virtual	void	draw()			const = 0;

public:
	class Widgets
	{
	public:
		typedef		list<Widget*>			WidgetList;
		typedef		WidgetList::iterator	WidgetIterator;

	public:
		void add   (const Widget* const subWidget);
		void remove(const Widget* const subWidget);

		const WidgetList&	getChildWidgets() const;

	private:
		WidgetList mWidgetList;
	};

private:
	string		mName;
	string		mText;
	Position	mLocation;
	Size		mSize;
	Widgets		mSubControl;
};
