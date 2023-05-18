#pragma once
#include <Graphics/Buffer.h>

class GLVertexBuffer : public Buffer
{
public:
	GLVertexBuffer();
	virtual ~GLVertexBuffer();
	virtual void BindPipeline(uint slot = 0);
	virtual void Create(const VertexBufferDesc& desc);

	uint vbo;
	uint vao; //inputlayout
};

class GLIndexBuffer : public Buffer
{
public:
	GLIndexBuffer();
	virtual ~GLIndexBuffer();
	virtual void BindPipeline(uint offset = 0) = 0;
	virtual void Create(const IndexBufferDesc& desc) = 0;
	uint indices = 0;
};

class GLUniformBuffer : public Buffer
{
public:
	GLUniformBuffer();
	virtual ~GLUniformBuffer();
	virtual void BindPipeline(uint slot = 0) = 0;
	virtual void Create(const ConstantBufferDesc& desc) = 0;
	virtual void SubData(void* pData) = 0;
};

