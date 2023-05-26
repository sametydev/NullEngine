#pragma once

#pragma comment(lib,"freetype.lib")
constexpr int FONT_MIN_CHAR = 32;
constexpr int FONT_MAX_CHAR = 128;

class Font
{
public:
	Font();

	void Create(LPCSTR filename,uint size);
};

