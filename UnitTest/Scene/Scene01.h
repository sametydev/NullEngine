#pragma once
#include <PCH.h>
#include <Engine/Scene.h>
#include <Core/SubSystem.h>
#include <Render/BasicBatch.h>
#include <Render/DXFontBatch.h>

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
	Texture* testTexture = nullptr;
	struct { mat4x4 proj, view, model; } matrices;

	BasicBatch* basicBatcher = nullptr;
	DXFontBatch* fontBatcher = nullptr;

};
