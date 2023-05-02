#pragma once

class rect
{
public:
	rect() :width(0), height(0), left(0), top(0)
	{
	}
	rect(int width, int height) :left(0), top(0), width(width), height(height)
	{
	}
	rect(int left, int top, int width, int height) :left(left), top(top), width(width), height(height)
	{
	}
	rect(const rect& rect) :left(rect.left), top(rect.top), width(rect.width), height(rect.height)
	{
	}
	~rect()
	{
	}
public:
	int width, height, left, top;
};