#include "PCH.h"
#include "BasicBatch.h"

#include <Graphics/Shader.h>


BasicBatch* BasicBatch::Instance = nullptr;

BasicBatch::BasicBatch(ID3D11Device* device, ID3D11DeviceContext* context)
{
	mDevice = device;
	mContext = context;

	if (Instance == nullptr)
	{
		Instance = this;
	}
}

void BasicBatch::Init()
{
	gContext->GetViewport(&mVp);

	CreateShader();
	CreateBuffer();
}

void BasicBatch::Begin()
{
	mIsBegin = true;
	mQueueIndex = 0;
	mSprite.clear();
}

void BasicBatch::Render(int x, int y, int w, int h, const vec4f& color)
{
	if (mQueueIndex > DEFAULT_SPRITE_SIZE) return;

	SpriteRect sr{};

	sr.LT = {
		vec3f(x,       y,      0 ), vec2f(),
	};

	sr.RT = {
		vec3f(x + w,   y,      0), vec2f(),
	};

	sr.LB = {
		vec3f(x ,      y + h,  0 ), vec2f(),
	};

	sr.RB = {
		vec3f(x + w,   y+h,    0 ), vec2f(),
	};

	sr.color = color;

	mSprite.emplace_back(sr);
	++mQueueIndex;
}


void BasicBatch::End()
{
	if (mIsBegin && mSprite.empty())
	{
		return;
	}
	switch (mType)
	{
	case SortType::BackToFront:
		std::reverse(mSprite.begin(), mSprite.end());
		break;
	case SortType::FrontToBack:

		break;
	case SortType::TextureIndex:

		break;
	default:
		break;
	}
	
	mShader->Bind();
	mShader->SetInputLayoutPipeline();

	uint stride = sizeof(VertexPS), offset = 0;

	mContext->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride,&offset);

	mContext->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	mContext->VSSetConstantBuffers(1, 1, mConstantBuffer.GetAddressOf());

	mContext->PSSetConstantBuffers(1, 1, mColorBuffer.GetAddressOf());

	mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	std::vector<VertexPS> vertices;
	vertices.reserve(mQueueIndex * VERTEX_PER_QUAD);
	for (size_t i = 0; i < mSprite.size(); i++)
	{
		vertices.emplace_back(mSprite[i].LT);
		vertices.emplace_back(mSprite[i].RT);
		vertices.emplace_back(mSprite[i].LB);
		vertices.emplace_back(mSprite[i].RB);
	}


	D3D11_MAPPED_SUBRESOURCE map{};
	mContext->Map(mVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
	memcpy(map.pData, vertices.data(), sizeof(VertexPS) * 4 * mQueueIndex);
	mContext->Unmap(mVertexBuffer.Get(), 0);

	uint vertexPos = 0;
	ZeroMemory(&map, sizeof(D3D11_MAPPED_SUBRESOURCE));
	for (size_t i = 0; i < mQueueIndex; i++)
	{
		mContext->UpdateSubresource(mColorBuffer.Get(), 0, 0, &mSprite[i].color, 0, 0);

		mContext->DrawIndexed(6, 0, vertexPos);

		vertexPos += 4;
	}

	mIsBegin = false;
}

void BasicBatch::CreateShader()
{
	mShader = ShaderCache::CreateShader("SpriteVS", "SpritePS");
	D3D11_INPUT_ELEMENT_DESC ied[3] = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	mShader->CreateInputLayout(ied, std::size(ied));
}

void BasicBatch::CreateBuffer()
{
	D3D11_BUFFER_DESC bd{};
	D3D11_SUBRESOURCE_DATA sd{};

	//Vertex;
	bd.ByteWidth = sizeof(VertexPS) * DEFAULT_SPRITE_SIZE * VERTEX_PER_QUAD;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HR(mDevice->CreateBuffer(&bd, nullptr, mVertexBuffer.GetAddressOf()));


	//Index;

	std::vector<uint> indices;
	indices.reserve(DEFAULT_SPRITE_SIZE*6);

	for (size_t i = 0; i < DEFAULT_SPRITE_SIZE*INDEX_PER_QUAD; i += 6)
	{
		//First Triangle
		indices.emplace_back(i);
		indices.emplace_back(i + 1);
		indices.emplace_back(i + 2);

		//Second Triangle
		indices.emplace_back(i + 2);
		indices.emplace_back(i + 1);
		indices.emplace_back(i + 3);
	}

	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(uint) * DEFAULT_SPRITE_SIZE * INDEX_PER_QUAD;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	sd.pSysMem = indices.data();

	HR(mDevice->CreateBuffer(&bd, &sd, mIndexBuffer.GetAddressOf()));

	//Constant;
	screenNDC = mat4x4::NDCToScreen(mVp.w, mVp.h);

	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(mat4x4);
	bd.CPUAccessFlags = 0;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;


	sd.pSysMem = screenNDC.data();

	HR(mDevice->CreateBuffer(&bd, &sd, mConstantBuffer.GetAddressOf()));

	//Color Constant Buffer
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(vec4f);
	bd.CPUAccessFlags = 0;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	vec4f initialColor(1);
	sd.pSysMem = &initialColor;

	HR(mDevice->CreateBuffer(&bd, &sd, mColorBuffer.GetAddressOf()));

}
