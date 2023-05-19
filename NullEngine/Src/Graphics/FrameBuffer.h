#pragma once
class FrameBuffer
{
public:
	FrameBuffer();

	uint GetTextureSize();
	Texture* GetTexture(uint index);


	uint width;
	uint height;


	std::vector<std::shared_ptr<Texture>>	mRenderPass;
	//std::shared_ptr<Texture>				mDepthPass;

	bool bDepthStencil;
};

