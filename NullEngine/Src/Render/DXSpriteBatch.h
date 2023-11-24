#pragma once
#include <Render/DXBatch.h>
#include <Graphics/Texture.h>

#define MAX_SPRITE 8192


/*
	LT(0) ----- RT(1)
	|				|
	|				|
	LB(2) ----- RB(3)
*/


struct SpriteBatch {
	VertexPS LT, RT, LB, RB;
	Texture* pTexture;
};

struct BatchItem {

	BatchItem(int _offset, uint _nVert, Texture* _tex)
		: offset(_offset), nVertices(_nVert), pTexture(_tex) {}

	int offset;    //vertex offset
	uint nVertices; //count of vertex
	Texture* pTexture;
};

enum class SortType : unsigned int {
	TEXTURE,DEPTH,NUMBER
};

class DXSpriteBatch : Batch {
public:
	DXSpriteBatch();

	void Init() override;
	void Begin() override;
	void Render(const char* text, int x, int y,
		const vec4f& color = vec4f(1.f)) override;
	void End() override;

	void Render(Texture* tex, int x, int y,int h, int w);

	void CreateBuffer();
	void CreateBatches();
	void RenderBatches();

	static DXSpriteBatch* Instance;
	static bool TextureSort(SpriteBatch* A,SpriteBatch* B);
protected:
	void DoSort();

private:
	ConstantBuffer* mCBO = nullptr;
	ID3D11Buffer* mVBO = nullptr;
	ID3D11Buffer* mIBO = nullptr;
	SpriteBatch* spriteData;
	Shader* mScreen = nullptr;

	std::vector<SpriteBatch*> mSortedSprites;
	std::vector<BatchItem>    mBatchItems;

	uint                           mQueuedIndex = 0;
	std::unique_ptr<SpriteBatch[]> mQueuedSprites;

	bool bIsBegin = false;;
};