#pragma once
#include <PCH.h>
#include <Engine/Scene.h>
#include <Graphics/DX11/DXContext.h>


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

	vec3f pos;

	mat4x4 M;
	mat4x4 P;
	mat4x4 V;
};

