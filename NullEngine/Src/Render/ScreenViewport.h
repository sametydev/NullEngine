#pragma once
class ScreenViewport
{
public:
	ScreenViewport();

	void Create();
	void Render();

	VertexBuffer* mVbo;
	IndexBuffer* mIbo;
	Shader* mShader;
};

