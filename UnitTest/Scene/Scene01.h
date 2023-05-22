#pragma once
#include <PCH.h>
#include <Engine/Scene.h>

class Scene01 : public Scene
{
public:
	Scene01() = default;

	void InitFrame() override;
	void UpdateFrame(float dt) override;
	void RenderFrame() override;

	void RenderDepth();

protected:
	TCamera* camera;
	ConstantBuffer* mCBO;
	ConstantBuffer* mLightCBO;

	Shader* mFrameShader;

	std::shared_ptr<ScreenViewport> mScreenVp;
	std::shared_ptr<FrameBuffer> mFrameBuffer;

	struct{ mat4x4 proj, view, model; } matrices;
	struct { mat4x4 proj, view; vec3f pos; } lightMatrices;

	
	std::shared_ptr<ShadowPass> mShadowPass;

	Model* mTree;
	Model* mPlane;
	Texture* texture;
};

