#pragma once
#include <Core/TypeDecl.h>
#define gDXContext Context::gInstance->GetDXContext()
#define gDXDevice  Context::gInstance->GetDXDevice()
#define gContext   Context::gInstance

class Context {
public:
	Context(int cx, int cy, HWND hwnd);
	virtual ~Context() {};
	//DX specific functions
	virtual void ClearBuffer(float r, float g, float b, float a) = 0;
	virtual void SwapBuffer() = 0;
	virtual void ResizeRenderBuffer(uint cx, uint cy) {};

	//API Function
	virtual void GetViewport(Viewport* vp) {};
	virtual void SetSampler(SamplerState sampler) {};

	HWND mHwnd;
	int width;
	int height;

	bool mIsMsaaEnable;
	uint Msaa;
	bool mFlipModel;

	virtual ID3D11DeviceContext* GetDXContext();
	virtual ID3D11Device* GetDXDevice();
}
	static Context* gInstance;
};