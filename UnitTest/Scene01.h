#pragma once
#include <PCH.h>
#include <Engine/Scene.h>
class Scene01 : public Scene
{
public:
	Scene01() = default;

	bool InitFrame() override;
	void UpdateFrame(float dt) override;
	void RenderFrame() override;
};

