#pragma once
class FrameBuffer
{
public:
	FrameBuffer();

	uint GetTextureSize();
	Texture* GetTexture(uint index);

	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;

	virtual void BindRenderPass() = 0;
	virtual void UnBindRenderPass() = 0;

	uint width;
	uint height;


	std::vector<std::shared_ptr<Texture>>	mRenderPass;
	//std::shared_ptr<Texture>				mDepthPass;

	bool bDepthStencil;

	//TODO : ReSize
};

