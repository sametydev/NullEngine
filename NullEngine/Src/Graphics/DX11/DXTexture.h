#pragma once
#include <Graphics/Texture.h>
#include <Graphics/DX11/DXContext.h>

class DXTexture : public Texture
{
public:
	DXTexture();
	virtual ~DXTexture();

	virtual void Load(LPCSTR filename);
	virtual void BindPipeline(uint slot = 0);
	virtual void UnBind() {};

	uint width;
	uint height;
	uint mSlot;

	ID3D11ShaderResourceView* mSRV;
private:
	void CreateSampler();
	static comptr<ID3D11SamplerState> InternalSampler;
};

