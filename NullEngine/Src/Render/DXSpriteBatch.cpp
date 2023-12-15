#include "PCH.h"
#include "DXSpriteBatch.h"
#include <Graphics/Context.h>
#include <Graphics/Shader.h>
#include <Graphics/Buffer.h>
#include <Graphics/DX11/DXContext.h>

DXSpriteBatch* DXSpriteBatch::Instance = nullptr;

DXSpriteBatch::DXSpriteBatch()
{
	if (Instance == nullptr)
	{
		Instance = this;
	}
}

void DXSpriteBatch::Init()
{
	Viewport vp{};
	gContext->GetViewport(&vp);


	mat4x4 screen = mat4x4::NDCToScreen(vp.w, vp.h);


	ConstantBufferDesc cbd{};
	cbd.cbSize = sizeof(mat4x4);
	cbd.pData = &screen;

	mCBO = BufferCache::CreateConstantBuffer(cbd);
	mCBO->SubData(&screen);

	mScreen = ShaderCache::CreateShader("SpriteVS","SpritePS");



	D3D11_INPUT_ELEMENT_DESC ied[2] = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_INSTANCE_DATA,1},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_INSTANCE_DATA,1},
	};
	mScreen->CreateInputLayout(ied, std::size(ied));

	CreateBuffer();
}

void DXSpriteBatch::Begin()
{
	bIsBegin = true;
	mQueuedIndex = 0;
	mSortedSprites.clear();
	mBatchItems.clear();
}

void DXSpriteBatch::Render(const char* text, int x, int y, const vec4f& color)
{

}

void DXSpriteBatch::End()
{
	if (!bIsBegin || mQueuedIndex == 0) return;

	mSortedSprites.resize(mQueuedIndex);

	for (int i = 0; i < mQueuedIndex; i++)
	{
		mSortedSprites[i] = &mQueuedSprites[i];
	}
	this->DoSort();
	this->CreateBatches();
	this->RenderBatches();
}

void DXSpriteBatch::Render(Texture* tex, int x,int y,int h, int w)
{
	if (tex == nullptr || !bIsBegin || mQueuedIndex >= MAX_SPRITE) return;
	mQueuedIndex++;

	mQueuedSprites[mQueuedIndex].pTexture = tex;
	mQueuedSprites[mQueuedIndex].LT = { vec3f(x,y,0.0f),    vec2f(0,0)};
	mQueuedSprites[mQueuedIndex].RT = { vec3f(x+w,y,0.0f),  vec2f(1,0) };
	mQueuedSprites[mQueuedIndex].LB = { vec3f(x,y+h,0.0f),  vec2f(0,1) };
	mQueuedSprites[mQueuedIndex].RB = { vec3f(x+w,y+h,0.0f),vec2f(1,1) };


}

void DXSpriteBatch::CreateBuffer()
{
	//Create Buffer with previous full of extended reserve resource
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VertexPS) * MAX_SPRITE * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;

	HR(gDXDevice->CreateBuffer(&bd, nullptr, &mVBO));


	// Creating Index Buffer
	int indexPerSprite[6] = {0,1,2, 2,1,3};
	std::vector<int[6]> indices(MAX_SPRITE);

	for (int i = 0; i < indices.size(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			indices[i][j] = indexPerSprite[j] + (i * 4);
		}

	}

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * 6 * indices.size();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = indices.data();

	HR(gDXDevice->CreateBuffer(&bd,&sd,&mIBO));

	mQueuedSprites = std::unique_ptr<SpriteBatch[]>(new SpriteBatch[MAX_SPRITE]);

}

void DXSpriteBatch::CreateBatches(/*int max_batch*/)
{
	if (mSortedSprites.empty()) return;
	std::vector<VertexPS> vertices;
	vertices.resize(mSortedSprites.size()*4);

	int currVtx = 0;
	int offset  = 0;

	vertices[currVtx++] = mSortedSprites[0]->LT;
	vertices[currVtx++] = mSortedSprites[0]->RT;
	vertices[currVtx++] = mSortedSprites[0]->LB;
	vertices[currVtx++] = mSortedSprites[0]->RB;
	
	Texture* prevTex = nullptr;

	for (int index = 1; index < mSortedSprites.size(); index++)
	{
		//Compare texture A and B
		if (mSortedSprites[index]->pTexture != prevTex)
		{
			mBatchItems.emplace_back(offset,6, mSortedSprites[index]->pTexture);
		}
		else
		{
			mBatchItems.back().nVertices+=6;
		}

		vertices[currVtx++] = mSortedSprites[index]->LT;
		vertices[currVtx++] = mSortedSprites[index]->RT;
		vertices[currVtx++] = mSortedSprites[index]->LB;
		vertices[currVtx++] = mSortedSprites[index]->RB;
		offset += 4;
	}

	D3D11_MAPPED_SUBRESOURCE mapped{};
	gDXContext->Map(mVBO, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, vertices.data(), sizeof(VertexPS) * vertices.size());
	gDXContext->Unmap(mVBO, 0);

}

void DXSpriteBatch::RenderBatches()
{
	auto dxContext = static_cast<DXContext*>(gContext);

	gDXContext->OMSetDepthStencilState(nullptr, 0);
	mScreen->Bind();
	mCBO->BindVS(1);

	uint stride = sizeof(VertexPS);
	uint offset = 0;

	mScreen->SetInputLayoutPipeline();

	gDXContext->IASetVertexBuffers(0, 1, &mVBO, &stride, &offset);
	gDXContext->IASetIndexBuffer(mIBO, DXGI_FORMAT_R32_UINT, offset);

	gDXContext->PSSetSamplers(0, 1, &dxContext->mStates.SSWrap);

	for (int i = 0; i < mBatchItems.size(); i++)
	{
		uint offset = mBatchItems[i].offset;
		uint nVerices = mBatchItems[i].nVertices;
		if (mBatchItems[i].pTexture)
		{
			mBatchItems[i].pTexture->Bind(0);
		}
		gDXContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		gDXContext->DrawIndexed(nVerices, 0, offset);
	}

	mScreen->UnBind();
	gDXContext->OMSetDepthStencilState(dxContext->mStates.DSState, 0);

}

bool DXSpriteBatch::TextureSort(SpriteBatch* A, SpriteBatch* B)
{
	return (A->pTexture > B->pTexture);
}

void DXSpriteBatch::DoSort()
{
	std::stable_sort(mSortedSprites.begin(), mSortedSprites.end(),
		DXSpriteBatch::TextureSort);
}
