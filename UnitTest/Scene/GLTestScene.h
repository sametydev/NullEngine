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

	Shader* vs;
	Shader* ps;
};