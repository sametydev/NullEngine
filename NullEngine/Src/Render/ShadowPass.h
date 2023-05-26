#pragma once

class ShadowPass
{
public:
	ShadowPass();
	void Create(uint width, uint height);

	Texture* GetDepthMap() const;

	void Bind();
	void UnBind();
	void Render(Renderable** Objs, uint nObjs);

	ID3D11RenderTargetView* mRtv = nullptr;
	ID3D11DepthStencilView* mDsv = nullptr;
	ID3D11ShaderResourceView* mSrv = nullptr;
	
	ID3D11RenderTargetView* prevRtv = nullptr;
	ID3D11DepthStencilView* prevDsv = nullptr;

	std::shared_ptr<Texture> mTexture;

	vec3f lightPosition;
	mat4x4 view;
	mat4x4 projection;

	Shader* mShader;

	Viewport mViewport;
	Viewport prevViewport;

	uint width, height;


	mat4x4 CreateLightView(const vec3f& pos, const vec3f& center);
	mat4x4 CreateLightProjection(float znear, float zfar);
};

