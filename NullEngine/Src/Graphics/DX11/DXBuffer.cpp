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
	static uint mCounter;


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
