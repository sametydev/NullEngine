#pragma once
#include <PCH.h>
#include <Engine/Scene.h>

class Shadow : public Scene
{
public:
	Shadow() = default;

	void InitFrame() override;
	void UpdateFrame(float dt) override;
	void RenderFrame() override;

	void RenderDepth();

protected:
	TCamera* camera;
	ConstantBuffer* mCBO;
	ConstantBuffer* mLightCBO;

	Shader* mFrameShader;
	Shader* mShadowShader;
	std::shared_ptr<ScreenViewport> mScreenVp;
	std::shared_ptr<FrameBuffer> mFrameBuffer;

	struct{ mat4x4 proj, view, model; } matrices;
	struct { mat4x4 proj, view; vec3f pos; float padding; } lightMatrices;

	
	std::shared_ptr<ShadowPass> mShadowPass;

	Model* mTree;
	Model* mPlane;
	Texture* texture;
};

