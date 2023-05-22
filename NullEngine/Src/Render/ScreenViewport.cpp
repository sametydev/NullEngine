#include <PCH.h>
#include <Render/ScreenViewport.h>
#include <Graphics/Buffer.h>
#include <Graphics/Shader.h>
#include <Graphics/Context.h>

ScreenViewport::ScreenViewport()
{
}

void ScreenViewport::Create()
{
	VertexPS vertices[] = {
		{{-1,-1,0},	{0.f,1.f}},
		{{-1,1,0},	{0.0f,0.f}},
		{{1,1,0},	{1.f,0.f}},
		{{1,-1,0},	{1.f,1.f}}
	};

	uint indices[] = {
		0,1,2,0,2,3
	};

	VertexAttrib attbs[] = {
		{0,Format::Float,3,offsetof(VertexPS,VertexPS::position)},
		{0,Format::Float,2,offsetof(VertexPS,VertexPS::st)}
	};

	VertexBufferDesc vd{};
	vd.nAttrib = std::size(attbs);
	vd.pAttrib = attbs;
	vd.cbStride = sizeof(VertexPS);
	vd.pData = vertices;
	vd.cbSize = sizeof(vertices);

	mVbo = BufferCache::CreateVertexBuffer(vd);

	IndexBufferDesc id{};
	id.cbSize = sizeof(indices);
	id.nIndices = std::size(indices);
	id.pData = indices;

	mIbo = BufferCache::CreateIndexBuffer(id);

	mShader = ShaderCache::CreateShader("ScreenVS", "ScreenPS");

}

void ScreenViewport::Render()
{
	mVbo->BindPipeline();
	mIbo->BindPipeline();
	mShader->Bind();

	gContext->DrawIndexed(6, 0, 0);
}
