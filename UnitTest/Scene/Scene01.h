#pragma once
#include <PCH.h>
#include <Engine/Scene.h>

class Scene01 : public Scene
{
public:
	Scene01() = default;

	bool InitFrame() override;
	void UpdateFrame(float dt) override;
	void RenderFrame() override;

protected:
	//DXVertexBuffer* mVBO;
	//DXIndexBuffer* mIBO;
	IShader* mVS;
	IShader* mPS;

	DXConstantBuffer* mCBO;

	vec3f pos = {0,0,0};
	vec3f rot = { 0,0,0 };
	float angle = 0;

	struct
	{
		mat4x4 proj;
		mat4x4 view;
		mat4x4 model;
	}matrices;
	DXModel* model;
	Texture* texture;
};

