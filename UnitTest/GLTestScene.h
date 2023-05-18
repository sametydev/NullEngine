#pragma once
#include <PCH.h>
#include <Engine/Scene.h>

class GLTestScene : public Scene
{
public:
	GLTestScene() = default;

	void InitFrame() override;
	void UpdateFrame(float dt) override;
	void RenderFrame() override;

protected:
	TCamera* camera;
	VertexBuffer* vbo;
	IndexBuffer* ibo;
	ConstantBuffer* cbo;
	Shader* vs;
	Shader* ps;


	vec3f pos = { 0,0,0 };
	vec3f rot = { 0,0,0 };
	float angle = 0;

	struct { mat4x4 proj, view, model; }matrices;



	Model* tree;
	Texture* texture;
};