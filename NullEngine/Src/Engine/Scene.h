#pragma once
class Scene
{
public:
	Scene();
	virtual ~Scene(){}

	virtual bool InitFrame() = 0;
	virtual void UpdateFrame(float dt) = 0;
	virtual void RenderFrame() = 0;
};

