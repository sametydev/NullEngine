#include <PCH.h>
#include <Graphics/Buffer.h>
#include <Graphics/DX11/DXBuffer.h>

std::vector<std::shared_ptr<Buffer>> BufferCache::mCache;

VertexBuffer* BufferCache::CreateVertexBuffer(const VertexBufferDesc& desc)
{
	auto buffer = std::make_shared<DXVertexBuffer>();
	buffer->Create(desc);
	mCache.emplace_back(buffer);
	return buffer.get();
}

IndexBuffer* BufferCache::CreateIndexBuffer(const IndexBufferDesc& desc)
{
	auto buffer = std::make_shared<DXIndexBuffer>();
	buffer->Create(desc);
	mCache.emplace_back(buffer);
	return buffer.get();
}

ConstantBuffer* BufferCache::CreateConstantBuffer(const ConstantBufferDesc& desc)
{
	auto buffer = std::make_shared<DXConstantBuffer>();
	buffer->Create(desc);
	mCache.emplace_back(buffer);
	return buffer.get();
}
