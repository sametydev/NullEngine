#pragma once
#include <PCH.h>
#include <Engine/Scene.h>
#include <Graphics/DX11/DXContext.h>
#include <Engine/InputSystem2.h>
#include <Graphics/DX11/DXTexture.h>

class Scene01 : public Scene
{
public:
	Scene01() = default;

	bool InitFrame() override;
	void UpdateFrame(float dt) override;
	void RenderFrame() override;

protected:
	DXVertexBuffer* mVBO;
	DXIndexBuffer* mIBO;
	IShader* mVS;
	IShader* mPS;

	DXConstantBuffer* mCBO;

	vec3f pos = {0,0,0};
	vec3f rot = { 0,0,0 };
	float angle = 0;

	mat4x4 M;
	mat4x4 V;
	mat4x4 P;
	mat4x4 MVP;

	mat4x4 T;

	Texture* texture;
};

