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

	HWND ref;
protected:
	TCamera* camera;
	ConstantBuffer* mCBO;

	struct { mat4x4 proj, view, model; } matrices;

	Texture* texture;

	Font* font;
};

