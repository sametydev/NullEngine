#pragma once
#include <Graphics/Buffer.h>

class GLVertexBuffer : public VertexBuffer
{
public:
	GLVertexBuffer();
	virtual ~GLVertexBuffer();
	virtual void BindPipeline(uint slot = 0);
	virtual void Create(const VertexBufferDesc& desc);
	virtual void UnBind();

	uint vbo;
	uint vao; //inputlayout
};

class GLIndexBuffer : public IndexBuffer
{
public:
	GLIndexBuffer();
	virtual ~GLIndexBuffer();
	virtual void Create(const IndexBufferDesc& desc);
	virtual void BindPipeline(uint offset = 0);
	virtual void UnBind();
	uint indices = 0;
	uint ibo;
};

class GLUniformBuffer : public ConstantBuffer
{
public:
	GLUniformBuffer();
	virtual ~GLUniformBuffer();
	virtual void Create(const ConstantBufferDesc& desc);
	virtual void BindPS(uint slot = 0) override;
	virtual void BindVS(uint slot = 0) override;

	virtual void SubData(void* pData);

	uint mSize;
	uint ubo;
};

