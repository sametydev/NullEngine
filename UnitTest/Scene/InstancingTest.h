#pragma once
#include <PCH.h>
#include <Engine/Scene.h>

class InstancingTest : public Scene
{
public:
	InstancingTest() = default;

	void InitFrame() override;
	void UpdateFrame(float dt) override;
	void RenderFrame() override;

protected:
	TCamera* camera;
	ConstantBuffer* mCBO;


	Shader* mSceneShader;

	std::vector<mat4x4> instanceData;

	struct { mat4x4 proj, view, model; } matrices;
	Model* mTree;
	Model* mPlane;
	Texture* texture;
};

