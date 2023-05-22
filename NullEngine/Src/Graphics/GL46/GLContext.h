#pragma once
#include <Graphics/Context.h>
class GLContext : public Context
{
public:
	GLContext(int cx, int cy, HWND hwnd);
	~GLContext();
private:
	void CreateDevice();


	HDC			mDC;
	HGLRC		mRC;
	friend Context;
public:
	//API Function
	virtual void ClearBuffer(float r, float g, float b, float a);
	virtual void SwapBuffer();
	virtual void ResizeRenderBuffer(uint cx, uint cy) override;
	virtual void SetViewport(Viewport* vp) override;
	virtual void GetViewport(Viewport* vp) {};
	virtual void SetSampler(SamplerState sampler) {};
	virtual void SetTopology(Topolgy topology);
	virtual void DrawIndexed(uint indices, uint offset, uint base);
	virtual void SetCullMode(CullMode mode) {};
	virtual void SetBlendState(BlendState state) {};

private:
	GLenum mTopolgy;
};

