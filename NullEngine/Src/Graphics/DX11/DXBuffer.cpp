#include <PCH.h>
#include <Graphics/Context.h>
#include <Graphics/DX11/DXBuffer.h>
#include <Graphics/DX11/DX11Config.h>


DXVertexBuffer::DXVertexBuffer() : mBuffer(nullptr), mStride(0) {

}

DXVertexBuffer::~DXVertexBuffer()
{
	SAFE_RELEASE(mBuffer);
}

void DXVertexBuffer::Create(const VertexBufferDesc& desc)
{
	mStride = desc.cbStride;

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
DXIndexBuffer::DXIndexBuffer() : mBuffer(nullptr) {

}
DXIndexBuffer::~DXIndexBuffer()
{
	SAFE_RELEASE(mBuffer);
}
void DXIndexBuffer::Create(const IndexBufferDesc& desc)
{
	indices = desc.nIndices;

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

DXConstantBuffer::DXConstantBuffer() : mBuffer(nullptr)
{
}

DXConstantBuffer::~DXConstantBuffer()
{
	SAFE_RELEASE(mBuffer);
}

void DXConstantBuffer::Create(const ConstantBufferDesc& desc)
{
	D3D11_BUFFER_DESC bd{};
	bd.ByteWidth = desc.cbSize;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = desc.pData;

	HR(gDXDevice->CreateBuffer(&bd, &sd, &mBuffer));

}

void DXConstantBuffer::BindPipeline(uint slot)
{
	gDXContext->VSSetConstantBuffers(slot, 1, &mBuffer);
}



void DXConstantBuffer::SubData(void* pData)
{
	gDXContext->UpdateSubresource(mBuffer, NULL, NULL, pData, NULL, NULL);
}

