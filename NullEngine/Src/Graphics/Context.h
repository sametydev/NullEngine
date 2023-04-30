#pragma once
#include <Core/TypeDecl.h>

class Context {
public:
	Context(int cx, int cy, HWND hwnd) :
		width(cx),height(cx),mHwnd(hwnd),
		mIsMsaaEnable(true),Msaa(0), 
		mFlipModel(false){

	}
	virtual ~Context() {};
	//Todo
	virtual void ClearBuffer(float r,float g,float b,float a) = 0;
	virtual void SwapBuffer() = 0;
	virtual void ResizeRenderBuffer(uint cx, uint cy) {};


	HWND mHwnd;
	int width;
	int height;

	bool mIsMsaaEnable;
	uint Msaa;
	bool mFlipModel;
};