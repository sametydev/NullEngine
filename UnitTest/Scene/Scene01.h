#pragma once
#include <PCH.h>
#include <Engine/Scene.h>
#include <Graphics/DX11/DXContext.h>

struct Vertex {
	Vec3f pos;
};
class Scene01 : public Scene
{
public:
	Scene01() = default;

	bool InitFrame() override;
	void UpdateFrame(float dt) override;
	void RenderFrame() override;

protected:
	DXVertexBuffer* mVBO;
	VertexShader* mShader;
	ID3D11InputLayout* mLayout;
};

