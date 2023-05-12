#include <PCH.h>
#include <Graphics/Context.h>
#include <Graphics/Shader.h>
#include <Graphics/DX11/DXBuffer.h>
#include <Graphics/DX11/DX11Config.h>
#include <Graphics/Format.h>

//remember if u need dx function include DXConfig!
//if u need dxContext include only Context!

DXVertexBuffer::DXVertexBuffer() : mBuffer(nullptr), mStride(0) {

}

DXVertexBuffer::~DXVertexBuffer()
{
	SAFE_RELEASE(mBuffer);
}


void DXVertexBuffer::Create(const VertexBufferDesc& desc)
{
	D3D11_BUFFER_DESC bd{};
	bd.ByteWidth = desc.cbSize;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = desc.pData;

	HR(gDXDevice->CreateBuffer(&bd, &sd, &mBuffer));

	//make temp shader
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputs(desc.nAttrib);
	std::string temp;
	temp += "struct VS_IN {";
	for (uint i = 0; i < desc.nAttrib; i++)
	{
		D3D11_INPUT_ELEMENT_DESC& input = inputs[i];
		VertexAttrib& attr = desc.pAttrib[i];
		input.SemanticName = (i == 0) ? "POSITION" : "TEXCOORD";
		input.SemanticIndex = (i == 0) ? 0 : (i - 0);
		input.Format = format::FormatToDX(attr.nFormat, attr.format);
		input.InputSlot = attr.slot;
		input.AlignedByteOffset = attr.offset;
		input.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		input.InstanceDataStepRate = 0;

		//temp shader side
		uint nFormat = attr.nFormat;
		if (i == 0)
		{
			temp += "float" + std::to_string(nFormat) + " pos : POSITION; ";
		}
		else
		{
			temp += "float" + std::to_string(nFormat) +
				" param" + std::to_string(i - 1) +
				" : POSITION" + std::to_string(i - 1) + "; ";
		}
	}
	temp += "}; float4 VS(VS_IN vs) : SV_POSITION {return vs.pos.xxxx;};";

	uint a = 0;

	


	//make element with custom out element
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

