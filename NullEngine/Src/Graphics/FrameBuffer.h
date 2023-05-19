#pragma once
class FrameBuffer
{
public:
	FrameBuffer();
	virtual ~FrameBuffer();

	virtual void Create(const FrameBufferDesc& desc) = 0;
	uint GetTextureSize();
	Texture* GetTexture(uint index);

	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;
	virtual void Clear(float r, float g, float b, float a) = 0;

	virtual void BindRenderPass() = 0;
	virtual void UnBindRenderPass() = 0;

	uint width;
	uint height;


	std::vector<std::shared_ptr<Texture>>	mRenderPass;
	//std::shared_ptr<Texture>				mDepthPass;

	bool bDepthStencil;

	//TODO : ReSize
};
