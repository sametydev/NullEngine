#pragma once
#include <Graphics/Context.h>
class GLContext : public Context
{
	GLContext(int cx, int cy, HWND hwnd);
	virtual ~GLContext();
private:
	void CreateDevice();


	HDC			mDC;
	HGLRC		mRC;
public:
	//API Function
	virtual void ClearBuffer(float r, float g, float b, float a) {};
	virtual void SwapBuffer() {};
	virtual void ResizeRenderBuffer(uint cx, uint cy) {};
	virtual void GetViewport(Viewport* vp) {};
	virtual void SetSampler(SamplerState sampler) {};
	virtual void SetTopology(Topolgy topology) {};
	virtual void DrawIndexed(uint indices, uint offset, uint base) {};
	virtual void SetCullMode(CullMode mode) {};
	virtual void SetBlendState(BlendState state) {};
};

