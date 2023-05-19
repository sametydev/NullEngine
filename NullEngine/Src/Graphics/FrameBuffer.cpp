#include <PCH.h>
#include <Graphics/FrameBuffer.h>
 
FrameBuffer::FrameBuffer() : bDepthStencil(false)
{
}

FrameBuffer::~FrameBuffer()
{
}

uint FrameBuffer::GetTextureSize()
{
	return (uint)mRenderPass.size();
}

Texture* FrameBuffer::GetTexture(uint index)
{
	return mRenderPass[index].get();
}
