#pragma once

class ShadowPass
{
public:
	ShadowPass();
	void Create(uint width, uint height);

	ID3D11RenderTargetView* mRtv = nullptr;
	ID3D11DepthStencilView* mDsv = nullptr;
	ID3D11ShaderResourceView* mSrv = nullptr;
	
	std::shared_ptr<Texture> mTexture;

	uint width, height;
};

