#include <PCH.h>
#include <Graphics/Context.h>
#include <Graphics/DX11/DXBuffer.h>
#include <Graphics/DX11/DXContext.h>

//	TODO: DXBuffer Abstract Class

//	DXVertexBuffer -> Devirred From DXBuffer;
//	DXIndexBuffer -> Devirred From DXBuffer;
//	DXConstantBuffer -> Devirred From DXBuffer;

DXBuffer::DXBuffer() : mId(0)
{
	static uint mCounter = 0;


	mId = mCounter;
	mCounter++;
}

DXBuffer::~DXBuffer()
{
	SAFE_RELEASE(mBuffer);
}


DXVertexBuffer::DXVertexBuffer() : mStride(0) {

}

void DXVertexBuffer::Create(const BufferDesc& desc)
{
	mStride = desc.stride;

	D3D11_BUFFER_DESC bd{};
	bd.ByteWidth = desc.cbSize;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = desc.pData;


	HR(gDXDevice->CreateBuffer(&bd, &sd, &mBuffer));
}

void DXVertexBuffer::BindPipeline(uint slot)
{
	uint offset = 0;
	gDXContext->IASetVertexBuffers(slot, 1, &mBuffer, &mStride, &offset);
}
DXIndexBuffer::DXIndexBuffer() {

}
void DXIndexBuffer::Create(const BufferDesc& desc)
{
	mIndices = desc.indices;

	D3D11_BUFFER_DESC bd{};
	bd.ByteWidth = desc.cbSize;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = desc.pData;

	HR(gDXDevice->CreateBuffer(&bd, &sd, &mBuffer));
}

void DXIndexBuffer::BindPipeline(uint offset)
{
	gDXContext->IASetIndexBuffer(mBuffer, DXGI_FORMAT_R32_UINT, offset);
}

DXConstantBuffer::DXConstantBuffer()
{
}

void DXConstantBuffer::Create(const BufferDesc& desc)
{
	D3D11_BUFFER_DESC bd{};
	bd.ByteWidth = desc.cbSize;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = desc.pData;

	gDXDevice->CreateBuffer(&bd,&sd,&mBuffer);
}

void DXConstantBuffer::BindPipeline(uint slot)
{
	gDXContext->VSSetConstantBuffers(slot, 1, &mBuffer);
}



void DXConstantBuffer::SubData(void* pData)
{
	gDXContext->UpdateSubresource(mBuffer, NULL, NULL, pData, NULL, NULL);
}

DXConstantMapBuffer::DXConstantMapBuffer() {

}

void DXConstantMapBuffer::Create(const BufferDesc& desc)
{
	D3D11_BUFFER_DESC bd{};
	bd.ByteWidth = desc.cbSize;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = desc.pData;

	gDXDevice->CreateBuffer(&bd, &sd, &mBuffer);
}

void DXConstantMapBuffer::BindPipeline(uint slot)
{
	gDXContext->VSSetConstantBuffers(slot, 1, &mBuffer);
}

void DXConstantMapBuffer::Map(void* pData, uint size)
{
	D3D11_MAPPED_SUBRESOURCE ms{};

	HR(gDXContext->Map(mBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms));

	memcpy_s(ms.pData, size, &pData, size);

	gDXContext->Unmap(mBuffer, NULL);
}

uint DXIndexBuffer::GetIndices()
{
	return mIndices;
}

std::vector<std::shared_ptr<DXBuffer>> BufferCache::mCache = {};