#pragma once
#include <Graphics/DX11/DX11Config.h>


struct BufferDesc {
	void* pData;
	uint cbSize;
	uint stride;
	uint indices;
	//optional
	//our custom input layout
};


class DXBuffer
{
public:
	DXBuffer();
	virtual ~DXBuffer();
	virtual void BindPipeline(uint slot) = 0;
	virtual void Create(const BufferDesc& desc) = 0;
	ID3D11Buffer* mBuffer = nullptr;
private:
	uint mId;
};


class DXVertexBuffer : public DXBuffer {
public:
	DXVertexBuffer();
	void Create(const BufferDesc& desc) override;
	void BindPipeline(uint slot = 0) override;

	uint mStride;
};

class DXIndexBuffer : public DXBuffer {
public:
	DXIndexBuffer();
	void Create(const BufferDesc& desc) override;
	void BindPipeline(uint offset = 0) override;
	uint GetIndices();
private:
	uint mIndices;
};



class DXConstantBuffer : public DXBuffer {
public:
	DXConstantBuffer();
	void Create(const BufferDesc& desc) override;
	void BindPipeline(uint slot = 0) override;
		void SubData(void* pData);
};

class DXConstantMapBuffer : public DXBuffer {
public:
	DXConstantMapBuffer();
	void Create(const BufferDesc& desc) override;
	void BindPipeline(uint slot = 0) override;
	void Map(void* pData,uint size);
};


