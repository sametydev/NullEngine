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
#include <Graphics/Shader.h>


//memory leak
ID3D11Buffer* DXModel::gInstanceBuffer = nullptr;

DXModel::DXModel()
{

}

DXModel::~DXModel()
{
	SAFE_RELEASE(mIBO);
	SAFE_RELEASE(mVBO);
}



void DXModel::Create(std::vector<VertexPNTS>& vertices, std::vector<uint>& indices, Shader* shader)
{
	currentShader = shader;
	D3D11_BUFFER_DESC vd{};
	vd.Usage = D3D11_USAGE_DEFAULT;
	vd.CPUAccessFlags = 0;
	vd.ByteWidth = vertices.size() * sizeof(VertexPNTS);
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


	//D3D11_INPUT_ELEMENT_DESC ied[] = {
	//	{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	//	{"TEXCOORD",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	//	{"TEXCOORD",1,DXGI_FORMAT_R32G32B32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0},
	//	{"TEXCOORD",2,DXGI_FORMAT_R32G32_FLOAT,0,36,D3D11_INPUT_PER_VERTEX_DATA,0},

	//	//Instancing 
	//	{"INSTANCE",0,DXGI_FORMAT_R32G32B32A32_FLOAT,1,0,D3D11_INPUT_PER_INSTANCE_DATA,1},
	//	{"INSTANCE",1,DXGI_FORMAT_R32G32B32A32_FLOAT,1,16,D3D11_INPUT_PER_INSTANCE_DATA,1},
	//	{"INSTANCE",2,DXGI_FORMAT_R32G32B32A32_FLOAT,1,32,D3D11_INPUT_PER_INSTANCE_DATA,1},
	//	{"INSTANCE",3,DXGI_FORMAT_R32G32B32A32_FLOAT,1,48,D3D11_INPUT_PER_INSTANCE_DATA,1}
	//};

	//HR(gDXDevice->CreateInputLayout(ied,
	//	std::size(ied),
	//	proxyBlob->GetBufferPointer(),
	//	proxyBlob->GetBufferSize(),
	//	&mLayout
	//));

	//shader->CreateInputLayout(ied, std::size(ied));

	if (gInstanceBuffer == nullptr)
	{
		D3D11_BUFFER_DESC ibd{};
		ibd.Usage = D3D11_USAGE_DYNAMIC;
		ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		ibd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		ibd.ByteWidth = g_instaceSize; // TODO : Make Global Functions for Performant Calculations
		

		HR(gDXDevice->CreateBuffer(&ibd, nullptr, &gInstanceBuffer));

	}
}

void DXModel::Render()
{
	uint stride = sizeof(VertexPNTS);
	uint offset = 0;

	gDXContext->IASetVertexBuffers(0, 1, &mVBO, &stride, &offset);
	gDXContext->IASetIndexBuffer(mIBO, DXGI_FORMAT_R32_UINT, 0);
	currentShader->SetInputLayoutPipeline();

	for (int i = 0; i < GetNodeCount(); i++)
	{
		ModelNode* node = GetNode(i);
		if (node->texture)
		{
			//node->texture->Bind(0);
		}
		gDXContext->DrawIndexed(node->nIndices, node->nIndicesOffset, offset);
	}
}

void DXModel::RenderInstanced(uint nInstance,void* data)
{
	D3D11_MAPPED_SUBRESOURCE mapped{};
	//Update transform matrix array to mapping
	gDXContext->Map(gInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0,&mapped);

	memcpy(mapped.pData, data, nInstance*sizeof(mat4x4));

	gDXContext->Unmap(gInstanceBuffer, 0);
	uint stride[2] = { sizeof(VertexPNTS),sizeof(mat4x4) };
	uint offset[2] = { 0,0 };
	ID3D11Buffer* buffers[2] = { mVBO,gInstanceBuffer };

	gDXContext->IASetVertexBuffers(0, 2, buffers, stride, offset);
	gDXContext->IASetIndexBuffer(mIBO, DXGI_FORMAT_R32_UINT, 0);
	currentShader->SetInputLayoutPipeline();

	for (unsigned int i = 0; i < GetNodeCount(); i++)
	{
		ModelNode* node = GetNode(i);
		if (node->texture)
		{
			node->texture->Bind();
		}
		gDXContext->DrawIndexedInstanced(node->nIndices, nInstance, node->nIndicesOffset,
			0, 0);
	}
}
