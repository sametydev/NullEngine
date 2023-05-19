#pragma once
#include <Graphics/Buffer.h>

class DXVertexBuffer : public VertexBuffer {
public:
	DXVertexBuffer();
	virtual~DXVertexBuffer();
	void Create(const VertexBufferDesc& desc) override;
	void BindPipeline(uint slot) override;

	uint mStride;
	ID3D11Buffer* mBuffer;
	ID3D11InputLayout* mLayout;
};

class DXIndexBuffer : public IndexBuffer {
public:
	DXIndexBuffer();
	virtual~DXIndexBuffer();
	void Create(const IndexBufferDesc& desc) override;
	void BindPipeline(uint offset) override;
private:
	ID3D11Buffer* mBuffer;
};



class DXConstantBuffer : public ConstantBuffer {
public:
	DXConstantBuffer();
	virtual~DXConstantBuffer();
	void BindPipeline(uint slot = 0) override;
	void BindPS(uint slot = 0) override;
	void BindVS(uint slot = 0) override;
	void Create(const ConstantBufferDesc& desc) override;
	void SubData(void* pData) override;

	ID3D11Buffer* mBuffer;
};