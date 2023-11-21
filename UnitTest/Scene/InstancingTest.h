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

	HWND ref;
protected:
	TCamera* camera;
	ConstantBuffer* mCBO;


	Shader* mSceneShader;
	Shader* mInstanceShader;

	std::vector<mat4x4> instanceData;

	std::shared_ptr<FrameBuffer> mFrameBuffer;

	struct { mat4x4 proj, view, model; } matrices;
	Model* mTree;
	Model* mPlane;
	Texture* texture;

	Font* font;
};

