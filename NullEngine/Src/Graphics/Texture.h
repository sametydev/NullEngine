#pragma once
#include <Core/TypeDecl.h>

class Texture
{
public:
	Texture();
	virtual ~Texture();

	virtual void Load(LPCSTR filename) = 0;
	virtual void BindPipeline(uint slot = 0) = 0;
	virtual void UnBind() {};

	uint bytePerPixel = 0; //Optional;
	uint width;
	uint height;
};