#pragma once
#include <Math/vec4f.h>
#include <Core/Singleton.h>
#include <freetype/freetype.h>
#include <Render/DXBatch.h>
#include <Core/SubSystem.h>
#define MAX_FONT_TEXT 8192
#pragma comment(lib,"freetype.lib")
constexpr int FONT_MIN_CHAR = 32;
constexpr int FONT_MAX_CHAR = 128;

struct FontGlyph {
	//advance
	float ax;
	float ay;

	float w;
	float h;

	float bl;
	float bt;

	float uvx1;
	float uvy1;

	float uvx2;
	float uvy2;
};

struct FontInstanceVertex {
	vec4f pswh; // POS and W/H
	vec4f uv;  // UV1 and UV2
	vec4f color;
};

class DXFontBatch : public BaseSubsystem {
public:
	DXFontBatch(ID3D11Device* device, ID3D11DeviceContext* context);

	void Init() override;
	void Begin();
	void Render(const char* text, int x, int y,
		const vec4f& color = vec4f(1.f));
	void End();
	void Create_Font(const char* filename, uint size);
	void CreateBuffer();
	void Update() override;
	void Shutdown() override;

private:
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mContext;

	uint texture;
	uint m_width;
	uint m_height;

	Shader* mShader;

	//for bitmap each of all
	FontGlyph fonts[FONT_MAX_CHAR];
	ConstantBuffer* mScreenCbo;

	ID3D11ShaderResourceView* mTexture;

	ID3D11Buffer* mVbo;

	std::unique_ptr<FontInstanceVertex[]> mVertices;

	FontInstanceVertex* pCurrentVertex = nullptr;

	bool mIsBegin = false;

	int mCurVtxIndex = 0;
};

