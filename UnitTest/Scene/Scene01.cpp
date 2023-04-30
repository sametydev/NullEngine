#include <PCH.h>
#include <Scene/Scene01.h>
#include <Graphics/DX11/DXBuffer.h>

bool Scene01::InitFrame()
{
	float i = 0.5f;

	Vertex vertices[] = {
		{{-i,-i,0}},
		{{0,i,0}},
		{{i,-i,0}}
	};

	
	BufferDesc desc{};

	desc.cbSize = sizeof(Vertex) * ARRAYSIZE(vertices);
	desc.pData = vertices;
	desc.stride = sizeof(Vertex);

	mVBO = new DXVertexBuffer();
	mVBO->Create(desc);

	mVBO->BindPipeline(0);
	

	return true;
}

void Scene01::UpdateFrame(float dt)
{
}

void Scene01::RenderFrame()
{
}
