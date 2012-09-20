
#include "../stdafx.h"
#include "ui_widget.h"

namespace alex
{
	namespace ui
	{
		Widget::Widget()
		{

		}

		const string& Widget::getName() const
		{
			return mName;
		}

		const string& Widget::getText() const
		{
			return mText;
		}

		int Widget::getLeft() const
		{
			return  mLocation.x;
		}

		int Widget::getTop() const
		{
			return  mLocation.y;
		}

		int Widget::getRight() const
		{
			return  mLocation.x + mSize.width;
		}

		int Widget::getButtom() const
		{
			return  mLocation.y + mSize.height;
		}

		Position Widget::getPosition() const
		{
			return mLocation;
		}

		Size Widget::getSize() const
		{
			return mSize;
		}

		void Widget::setName(std::string& name)
		{
			mName = name;
		}

		void Widget::setText(string& text)
		{
			mText = text;
		}

		void Widget::setPosition(const Position& position)
		{
			setPosition(position.x, position.y);
		}

		void Widget::setPosition(int x, int y)
		{
			mLocation.x	= x;
			mLocation.y = y;
		}

		void Widget::setSize(const Size& size)
		{
			setSize(size.width, size.height);
		}

		void Widget::setSize(int width, int height)
		{
			mSize.width = width;
			mSize.height = height;
		}
	}
}
