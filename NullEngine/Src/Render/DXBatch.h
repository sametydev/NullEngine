#pragma once
#include <Math/vec4f.h>
#include <Render/Font.h>
#include <Core/Singleton.h>
#include <freetype/freetype.h>

#define MAX_FONT_TEXT 8192

struct FontInstanceVertex {
	vec4f pswh; // POS and W/H
	vec4f uv;  // UV1 and UV2
	vec4f color;
};

class Batch
{
public:
	Batch();
	virtual ~Batch();


	virtual void Init() = 0;

	//Gathering resources
	virtual void Begin() = 0;

	virtual void Render(const char* text, int x, int y,
		const vec4f& color = vec4f(1.f)) = 0;

	virtual void End() = 0;
};
class DXBatch : Batch {
public:
	DXBatch();

	void Init() override;
	void Begin() override;
	void Render(const char* text, int x, int y,
		const vec4f& color = vec4f(1.f)) override;
	void End() override;
	void Create_Font(const char* filename, uint size);
	void CreateBuffer();


	static DXBatch* Instance;

private:
	uint texture;
	uint m_width;
	uint m_height;


	Shader* mShader;
	FontGlyph fonts[FONT_MAX_CHAR];
	ConstantBuffer* mScreenCbo;

	ID3D11ShaderResourceView* mTexture;

	ID3D11Buffer* mVbo;

	ID3D11InputLayout* inputLayout;

	std::unique_ptr<FontInstanceVertex[]> mVertices;

	FontInstanceVertex* pCurrentVertex = nullptr;

	bool mIsBegin = false;

	int mCurVtxIndex = 0;
};

