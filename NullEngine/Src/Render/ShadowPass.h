#pragma once

class ShadowPass
{
public:
	ShadowPass();
	void Create(uint width, uint height);

	void Bind();
	void UnBind();

	ID3D11RenderTargetView* mRtv = nullptr;
	ID3D11DepthStencilView* mDsv = nullptr;
	ID3D11ShaderResourceView* mSrv = nullptr;
	
	std::shared_ptr<Texture> mTexture;

	vec3f lightPosition;
	mat4x4 view;
	mat4x4 projection;

	uint width, height;


	mat4x4 CreateLightView(const vec3f& pos, const vec3f& center);
	mat4x4 CreateLightProjection(float znear, float zfar);
};

