#pragma once
#include <Graphics/Texture.h>
#include <Graphics/DX11/DXContext.h>

class DXTexture : public Texture
{
public:
	DXTexture();
	virtual ~DXTexture();

	virtual void Load(LPCSTR filename) = 0;
	virtual void BindPipeline(uint slot = 0) = 0;
	virtual void UnBind() {};

	uint bytePerPixel = 0; //Optional;
	uint width;
	uint height;


};

