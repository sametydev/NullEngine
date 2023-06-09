#pragma once

#pragma comment(lib,"freetype.lib")
constexpr int FONT_MIN_CHAR = 32;
constexpr int FONT_MAX_CHAR = 128;

struct FontGlyph {
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

class Font
{
public:
	Font();

	void Create(LPCSTR filename,uint size);

	uint mWidth;
	uint mHeight;

	FontGlyph mFont[FONT_MAX_CHAR];

	ID3D11ShaderResourceView* mSRV = nullptr;
	std::shared_ptr<Texture> mTexture;

	Texture* GetFontTexture() const;
};

