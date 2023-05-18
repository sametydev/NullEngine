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
	virtual void SetTopology(Topolgy topology) {};
	virtual void DrawIndexed(uint indices, uint offset, uint base) = 0;
	virtual void SetCullMode(CullMode mode) = 0;
	virtual void SetBlendState(BlendState state) = 0;

	HWND mHwnd;
	int width;
	int height;

	bool mIsMsaaEnable;
	uint Msaa;
	bool mFlipModel;
	bool mVSync = false;

	GraphicAPI mApiType;


	virtual ID3D11DeviceContext* GetDXContext();
	virtual ID3D11Device* GetDXDevice();
	static Context* gInstance;
};