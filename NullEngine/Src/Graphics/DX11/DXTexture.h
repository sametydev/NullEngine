#pragma once
#include <Graphics/Texture.h>


class DXTexture : public Texture
{
public:
	DXTexture();
	virtual ~DXTexture();

	virtual void Load(LPCSTR filename);
	virtual void Bind(uint slot = 0);
	virtual void UnBind();
	ID3D11ShaderResourceView* mSRV;
	uint width;
	uint height;
	uint mSlot;
};

