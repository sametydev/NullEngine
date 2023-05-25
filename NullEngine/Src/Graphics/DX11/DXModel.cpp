#include <PCH.h>
#include <Graphics/DX11/DXModel.h>
#include <Graphics/DX11/DX11Config.h>
#include <Core/FileSystem.h>
#include <Graphics/Buffer.h>
#include <Graphics/Context.h>
#include <Graphics/Texture.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


DXModel::DXModel()
{

}

DXModel::~DXModel()
{
	SAFE_RELEASE(mLayout);
	SAFE_RELEASE(mIBO);
	SAFE_RELEASE(mVBO);
}


ID3D11Buffer* DXModel::gInstanceBuffer = nullptr;


void DXModel::Create(std::vector<VertexPNS>& vertices, std::vector<uint>& indices)
{
	D3D11_BUFFER_DESC vd{};
	vd.Usage = D3D11_USAGE_DEFAULT;
	vd.CPUAccessFlags = 0;
	vd.ByteWidth = vertices.size() * sizeof(VertexPNS);
	vd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertices.data();

	HR(gDXDevice->CreateBuffer(&vd, &sd, &mVBO));

	D3D11_BUFFER_DESC id{};
	id.Usage = D3D11_USAGE_DEFAULT;
	id.BindFlags = D3D11_BIND_INDEX_BUFFER;
	id.CPUAccessFlags = 0;
	id.ByteWidth = indices.size() * sizeof(uint);

	sd.pSysMem = indices.data();

	HR(gDXDevice->CreateBuffer(&id, &sd, &mIBO));


	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",1,DXGI_FORMAT_R32G32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0},

		//Instancing 
		{"INSTANCE",0,DXGI_FORMAT_R32G32B32A32_FLOAT,1,0,D3D11_INPUT_PER_INSTANCE_DATA,1},
		{"INSTANCE",1,DXGI_FORMAT_R32G32B32A32_FLOAT,1,16,D3D11_INPUT_PER_INSTANCE_DATA,1},
		{"INSTANCE",2,DXGI_FORMAT_R32G32B32A32_FLOAT,1,32,D3D11_INPUT_PER_INSTANCE_DATA,1},
		{"INSTANCE",3,DXGI_FORMAT_R32G32B32A32_FLOAT,1,48,D3D11_INPUT_PER_INSTANCE_DATA,1}

	};
	std::string bumpCode = R"(
		struct VSIn {
			float3 pos : POSITION;
			float3 normal : TEXCOORD0;
			float2 st : TEXCOORD1;
			
			float4 inst0 : INSTANCE0;
			float4 inst1 : INSTANCE1;
			float4 inst2 : INSTANCE2;
			float4 inst3 : INSTANCE3;
		};
		

		float4 VS(VSIn vs) : SV_POSITION {
			return vs.pos.xxxx;
		};
	)";

	ID3DBlob* proxyBlob;
	ID3DBlob* errBlob;

	HR(D3DCompile(bumpCode.c_str(), bumpCode.size(), NULL,
		nullptr, nullptr, "VS", "vs_5_0", 0, 0, &proxyBlob, &errBlob));

	if (errBlob != nullptr)
	{
		LOG_ERROR("D3D Compile Error from Model : %s", errBlob->GetBufferPointer());
	}

	HR(gDXDevice->CreateInputLayout(ied,
		std::size(ied),
		proxyBlob->GetBufferPointer(),
		proxyBlob->GetBufferSize(),
		&mLayout
	));

	if (gInstanceBuffer == nullptr)
	{
		D3D11_BUFFER_DESC ibd{};
		ibd.Usage = D3D11_USAGE_DYNAMIC;
		ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		ibd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		ibd.ByteWidth = sizeof(VertexPNS) * 40000; // TODO : Make Global Functions for Performant Calculations
		

		HR(gDXDevice->CreateBuffer(&ibd, nullptr, &gInstanceBuffer));

	}
}

void DXModel::Render()
{
	uint stride = sizeof(VertexPNS);
	uint offset = 0;

	gDXContext->IASetVertexBuffers(0, 1, &mVBO, &stride, 0);
	gDXContext->IASetIndexBuffer(0, DXGI_FORMAT_R32_UINT, 0);
	gDXContext->IASetInputLayout(mLayout);

	for (int i = 0; i < GetNodeCount(); i++)
	{
		ModelNode* node = GetNode(i);
		if (node->texture)
		{
			node->texture->Bind(0);
		}
		gDXContext->DrawIndexed(node->nIndices, node->nIndicesOffset, offset);
	}
}
