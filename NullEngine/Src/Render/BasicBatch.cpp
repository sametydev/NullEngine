#include "PCH.h"
#include "BasicBatch.h"

#include <Graphics/Shader.h>

BasicBatch::BasicBatch(ID3D11Device* device, ID3D11DeviceContext* context)
{
	mDevice = device;
	mContext = context;
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
	mCmdList.clear();
	mColorList.clear();
}

void BasicBatch::DrawRect(int x, int y, int w, int h, const vec3f& color)
{
	if (mQueueIndex > DEFAULT_SPRITE_SIZE) return;

	//Vertex Data Part
	vec4f* ptr = mQueuedVertices.get();

	ptr += mQueueIndex;

	vec4f src[4] = {
		{(float)x,(float)y,0,0}, //pos and uv
		{(float)(x+w),(float)y,0,0},
		{(float)x,(float)(y+h),0,0},
		{(float)(x+w),(float)(y+h),0,0},
	};

	//memcpy_s(ptr,sizeof(vec4f)*4,src,sizeof(vec4f) * 4);
	memcpy(ptr,src,sizeof(vec4f)*4);

	//--------
	vec4f currColor = { color.x,color.y,color.z,1.f };
	//Command Part

	BatchCommandList cmd{};
	cmd.type         = QUAD;
	cmd.bufferOffset = 4;
	cmd.drawCount    = 6;

	mCmdList.emplace_back(cmd);
	mColorList.emplace_back(currColor);
	mQueueIndex += VERTEX_PER_QUAD;
}

void BasicBatch::DrawLine(const vec2f& p1, const vec2f& p2, const vec3f& color)
{
	if (mQueueIndex > DEFAULT_SPRITE_SIZE) return;

	//Vertex Data Part
	vec4f* ptr = mQueuedVertices.get();

	ptr += mQueueIndex;

	vec4f src[2] = {
		{p1.x,p1.y,0,0},
		{p2.x,p2.y,0,0}
	};

	memcpy(ptr, src, sizeof(vec4f) * 2);

	//--------
	vec4f currColor = {color.x,color.y,color.z,1.f};

	//Command Part

	BatchCommandList cmd{};
	cmd.type         = LINE;
	cmd.bufferOffset = 2;
	cmd.drawCount    = 2;

	mCmdList.emplace_back(cmd);
	mColorList.emplace_back(currColor);
	mQueueIndex += VERTEX_PER_LINE;
}


void BasicBatch::End()
{
	if (mIsBegin && (mQueueIndex <= 0)) return;
	
	mShader->Bind();
	mShader->SetInputLayoutPipeline();

	uint stride = sizeof(vec4f), offset = 0;

	mContext->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride,&offset);

	mContext->VSSetConstantBuffers(1, 1, mConstantBuffer.GetAddressOf());

	mContext->PSSetConstantBuffers(1, 1, mColorBuffer.GetAddressOf());

	mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_MAPPED_SUBRESOURCE map{};
	mContext->Map(mVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
	memcpy(map.pData, mQueuedVertices.get(), sizeof(vec4f) *  BATCH_MAX_VERTEX);
	mContext->Unmap(mVertexBuffer.Get(), 0);

	

	uint currentOffset = 0;
	for (size_t i = 0; i < mCmdList.size(); i++)
	{
		ZeroMemory(&map, sizeof(D3D11_MAPPED_SUBRESOURCE));
		mContext->Map(mColorBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
		memcpy(map.pData, &mColorList[i], sizeof(vec4f));
		mContext->Unmap(mColorBuffer.Get(), 0);

		BatchCommandList& CMD = mCmdList[i];
		
		if (CMD.type == QUAD)
		{
			mContext->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			mContext->DrawIndexed(CMD.drawCount, 0, currentOffset);
		}
		else if (CMD.type == LINE) {

			mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
			mContext->Draw(CMD.drawCount, currentOffset);
		}

		currentOffset += CMD.bufferOffset;
	}
	

	mIsBegin = false;
}

void BasicBatch::Shutdown()
{
}

void BasicBatch::Update()
{
}

void BasicBatch::CreateShader()
{
	mShader = ShaderCache::CreateShader("SpriteVS", "SpritePS");
	D3D11_INPUT_ELEMENT_DESC ied[3] = {
		{"POSITION", 0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,                           D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD", 0,DXGI_FORMAT_R32G32_FLOAT,   0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",    0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,                           D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	mShader->CreateInputLayout(ied, std::size(ied));
}

void BasicBatch::CreateBuffer()
{
	D3D11_BUFFER_DESC bd{};
	D3D11_SUBRESOURCE_DATA sd{};

	//Allocate vertices data
	mQueuedVertices   = std::make_unique<vec4f[]>(BATCH_MAX_VERTEX);

	//Vertex;
	bd.ByteWidth      = sizeof(VertexPS) * DEFAULT_SPRITE_SIZE * VERTEX_PER_QUAD;
	bd.Usage          = D3D11_USAGE_DYNAMIC;
	bd.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HR(mDevice->CreateBuffer(&bd, nullptr, mVertexBuffer.GetAddressOf()));


	//Index Buffer;
	std::vector<uint> indices;
	indices.reserve(DEFAULT_SPRITE_SIZE*6);

	for (size_t i     = 0; i < DEFAULT_SPRITE_SIZE*INDEX_PER_QUAD; i += 6)
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
	bd.ByteWidth      = sizeof(uint) * DEFAULT_SPRITE_SIZE * INDEX_PER_QUAD;
	bd.Usage          = D3D11_USAGE_DEFAULT;
	bd.BindFlags      = D3D11_BIND_INDEX_BUFFER;

	sd.pSysMem        = indices.data();

	HR(mDevice->CreateBuffer(&bd, &sd, mIndexBuffer.GetAddressOf()));

	//Constant Buffer;
	screenNDC         = mat4x4::NDCToScreen(mVp.w, mVp.h);

	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.Usage          = D3D11_USAGE_DEFAULT;
	bd.ByteWidth      = sizeof(mat4x4);
	bd.CPUAccessFlags = 0;
	bd.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;


	sd.pSysMem        = screenNDC.data();

	HR(mDevice->CreateBuffer(&bd, &sd, mConstantBuffer.GetAddressOf()));

	//Color Constant Buffer
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.Usage          = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth      = sizeof(vec4f);
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;

	vec4f initialColor(1.f);
	sd.pSysMem        = &initialColor;

	HR(mDevice->CreateBuffer(&bd, &sd, mColorBuffer.GetAddressOf()));

}
