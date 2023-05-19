#pragma once
#include <Graphics/FrameBuffer.h>
class DXFrameBuffer : public FrameBuffer
{
public:
	DXFrameBuffer();
	virtual ~DXFrameBuffer();
	void Create(const FrameBufferDesc& desc);

	void BeginFrame();
	void EndFrame();

	virtual void BindRenderPass() override;
	virtual void UnBindRenderPass() override;

	std::vector<ID3D11Texture2D*>			mTexture2D;
	std::vector<ID3D11RenderTargetView*>	mRenderTargetViews;

	ID3D11Texture2D* mDepthTexture2D          = nullptr;
	ID3D11DepthStencilView* mDepthStencilView = nullptr;

	ID3D11RenderTargetView* mPrevRTV = nullptr;
	ID3D11DepthStencilView* mPrevDTV = nullptr;

};

