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

protected:
	TCamera* camera;
	ConstantBuffer* cbo;


	Shader* mFrameShader;

	std::shared_ptr<ScreenViewport> mScreenVp;
	std::shared_ptr<FrameBuffer> mFrameBuffer;

	vec3f pos = {0,0,0};
	vec3f rot = { 0,0,0 };
	float angle = 0;
	
	struct{ mat4x4 proj, view, model; }matrices;
	

	Model* tree;
	Model* mPlane;
	Texture* texture;
};

