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
	Shader* vs;
	Shader* ps;

	Shader* frameShaderVS;
	Shader* frameShaderPS;


	Shader* f_vs;
	Shader* f_ps;
	std::shared_ptr<ScreenViewport> mScreenVp;


	vec3f pos = {0,0,0};
	vec3f rot = { 0,0,0 };
	float angle = 0;
	
	struct{ mat4x4 proj, view, model; }matrices;

	FrameBuffer* fbo;
	

	Model* tree;
	Model* mPlane;
	Texture* texture;
};

