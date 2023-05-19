#pragma once
#include <Graphics/FrameBuffer.h>
class DXFrameBuffer : public FrameBuffer
{
public:
	DXFrameBuffer();
	virtual ~DXFrameBuffer();
	void Create(const FrameBufferDesc& desc) override;

	void BeginFrame() override;
	void EndFrame() override;
	void Clear(float r, float g, float b, float a) override;

	virtual void BindRenderPass() override;
	virtual void UnBindRenderPass() override;

	std::vector<ID3D11RenderTargetView*>	mRenderTargetViews;

	ID3D11Texture2D* mDepthTexture2D          = nullptr;
	ID3D11DepthStencilView* mDepthStencilView = nullptr;

	ID3D11RenderTargetView* mPrevRTV = nullptr;
	ID3D11DepthStencilView* mPrevDTV = nullptr;

};

