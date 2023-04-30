#pragma once

//Abstract
class Wnd
{
public:
	Wnd(Wnd* parent, int x, int y, int width, int height);

	void Create();

	virtual void OnCreate();
	virtual void OnReSize(uint cx, uint cy);

	virtual ~Wnd();
	
	virtual LRESULT LocalWndProc(UINT, WPARAM, LPARAM);
	static LRESULT WINAPI GlobalWndProc(HWND, UINT, WPARAM, LPARAM);

	operator HWND();
	HWND mHwnd;

	union
	{
		struct { int x;  int y; int cx; int cy; } geo;
		int raw_geo[4];
	};

private:
	Wnd* mParent;
};

