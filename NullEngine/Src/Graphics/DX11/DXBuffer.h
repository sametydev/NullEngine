#pragma once
#include <Graphics/DX11/DX11Config.h>

struct BufferDesc {
	void* pData;
	uint cbSize;
	uint stride;
};


class DXBuffer
{
public:
	DXBuffer();
	virtual ~DXBuffer();

	virtual void Create(const BufferDesc& desc) = 0;
	ID3D11Buffer* mBuffer = nullptr;
private:
	uint mId;
};


class DXVertexBuffer : public DXBuffer {
public:
	DXVertexBuffer();
	void Create(const BufferDesc& desc) override;
};

