#pragma once
class Buffer
{
public:
	Buffer() {};
	virtual ~Buffer() {};
	virtual void BindPipeline(uint slot) = 0;
	virtual void UnBind() {};
	//virtual void Create(const VertexBufferDesc& desc) = 0;
};

class VertexBuffer : public Buffer
{
public:
	VertexBuffer() {};
	virtual ~VertexBuffer() {};
	virtual void BindPipeline(uint slot = 0) = 0;
	virtual void Create(const VertexBufferDesc& desc) = 0;
};

class IndexBuffer : public Buffer
{
public:
	IndexBuffer() {};
	virtual ~IndexBuffer() {};
	virtual void BindPipeline(uint offset = 0) = 0;
	virtual void Create(const IndexBufferDesc& desc) = 0;
	uint indices = 0;
};

class ConstantBuffer : public Buffer
{
public:
	ConstantBuffer() {};
	virtual ~ConstantBuffer() {};
	virtual void BindPS(uint slot = 0) = 0;
	virtual void BindVS(uint slot = 0) = 0;
	virtual void Create(const ConstantBufferDesc& desc) = 0;
	virtual void SubData(void* pData) = 0;
};

class BufferCache {
public:
	static VertexBuffer* CreateVertexBuffer(const VertexBufferDesc& desc);
	static IndexBuffer* CreateIndexBuffer(const IndexBufferDesc& desc);
	static ConstantBuffer* CreateConstantBuffer(const ConstantBufferDesc& desc);

	static std::vector<std::shared_ptr<Buffer>> mCache;
};