#pragma once
#include <Graphics/Context.h>
#include <Graphics/DX11/DXRenderState.h>

class DXContext : public Context
{
public:

	DXContext(int cx, int cy, HWND hwnd);
	~DXContext();

	//protected
	void CreateDevice();
	void ResizeRenderBuffer(uint cx, uint cy) override;
	void CreateSwapChain();
	//end protected

	ID3D11Device1*			mDevice;
	ID3D11DeviceContext1*	mDeviceContext;
	IDXGISwapChain1*		mSwapChain;

	//View
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11DepthStencilView* mDepthStencilView;
	ID3D11Texture2D*		mDepthStencilBuffer;

	DXRenderState mStates;

	virtual ID3D11DeviceContext* GetDXContext();
	virtual ID3D11Device* GetDXDevice();
	virtual void SetTopology(Topolgy topology);


	//API Function 
	virtual void GetViewport(Viewport* vp) override;
	virtual void SetViewport(Viewport* vp) override;
	virtual void SetSampler(SamplerState sampler) override;
	virtual void ClearBuffer(float r, float g, float b, float a);
	virtual void SwapBuffer();
	virtual void DrawIndexed(uint indices, uint offset, uint base);
	virtual void SetCullMode(CullMode mode);
	virtual void SetBlendState(BlendState state);

};