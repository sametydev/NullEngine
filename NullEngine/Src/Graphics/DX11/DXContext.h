#pragma once
#include <Graphics/DX11/DX11Config.h>
#include <Graphics/Context.h>

class DXContext : public Context
{
public:

	DXContext(int cx, int cy, HWND hwnd);
	~DXContext();

	void CreateDevice();
	void ResizeRenderBuffer(uint cx, uint cy) override;
	void CreateSwapChain();
	void CreateStates();

	virtual void ClearBuffer(float r, float g, float b, float a);
	virtual void SwapBuffer();

	ID3D11Device1*			mDevice;
	ID3D11DeviceContext1*	mDeviceContext;
	IDXGISwapChain1*		mSwapChain;

	//View
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11DepthStencilView* mDepthStencilView;
	ID3D11Texture2D*		mDepthStencilBuffer;

	//State
	ID3D11RasterizerState* mRSState[2]{};

	virtual ID3D11DeviceContext* GetDXContext() { return mDeviceContext; }
	virtual ID3D11Device* GetDXDevice() { return mDevice; }
};