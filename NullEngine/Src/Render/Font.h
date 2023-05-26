#pragma once

#pragma comment(lib,"freetype.lib")

class Font
{
public:
	Font();

	void Create(LPCSTR filename);
};

