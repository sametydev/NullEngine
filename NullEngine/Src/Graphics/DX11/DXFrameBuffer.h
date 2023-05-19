#pragma once
#include <Graphics/FrameBuffer.h>
class DXFrameBuffer : public FrameBuffer
{
public:
	DXFrameBuffer();

	void Create(const FrameBufferDesc& desc);

	void BeginFrame();
	void EndFrame();

	std::vector<ID3D11Texture2D*>			mTexture2D;
	std::vector<ID3D11RenderTargetView*>	mRenderTargetViews;

	ID3D11Texture2D* mDepthTexture2D          = nullptr;
	ID3D11DepthStencilView* mDepthStencilView = nullptr;
};

