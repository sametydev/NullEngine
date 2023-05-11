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
	void Create(const ConstantBufferDesc& desc) override;
	void BindPipeline(uint slot) override;
	void SubData(void* pData) override;

	ID3D11Buffer* mBuffer;
};