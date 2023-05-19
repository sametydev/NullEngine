#include <PCH.h>
#include <Graphics/Buffer.h>
#include <Graphics/DX11/DXBuffer.h>
#include <Graphics/GL46/GLBuffer.h>
#include <Graphics/Context.h>
std::vector<std::shared_ptr<Buffer>> BufferCache::mCache;

VertexBuffer* BufferCache::CreateVertexBuffer(const VertexBufferDesc& desc)
{
	std::shared_ptr<VertexBuffer> buffer = nullptr;
	switch (gContext->mApiType)
	{
	case GraphicAPI::DirectX11:
		buffer = std::make_shared<DXVertexBuffer>();
		break;
	case GraphicAPI::OpenGL46:
		buffer = std::make_shared<GLVertexBuffer>();
		break;
	default:
		break;
	}
	buffer->Create(desc);
	mCache.emplace_back(buffer);
	return buffer.get();
}

IndexBuffer* BufferCache::CreateIndexBuffer(const IndexBufferDesc& desc)
{

	std::shared_ptr<IndexBuffer> buffer = nullptr;
	switch (gContext->mApiType)
	{
	case GraphicAPI::DirectX11:
		buffer = std::make_shared<DXIndexBuffer>();
		break;
	case GraphicAPI::OpenGL46:
		buffer = std::make_shared<GLIndexBuffer>();
		break;
	default:
		break;
	}
	buffer->Create(desc);
	mCache.emplace_back(buffer);
	return buffer.get();
}

ConstantBuffer* BufferCache::CreateConstantBuffer(const ConstantBufferDesc& desc)
{
	std::shared_ptr<ConstantBuffer> buffer = nullptr;
	switch (gContext->mApiType)
	{
	case GraphicAPI::DirectX11:
		buffer = std::make_shared<DXConstantBuffer>();
		break;
	case GraphicAPI::OpenGL46:
		buffer = std::make_shared<GLUniformBuffer>();
		break;
	default:
		break;
	}
	buffer->Create(desc);
	mCache.emplace_back(buffer);
	return buffer.get();
}
