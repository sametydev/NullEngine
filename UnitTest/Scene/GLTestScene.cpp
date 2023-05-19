#include <PCH.h>
#include <Scene/GLTestScene.h>
#include <Graphics/Buffer.h>
#include <Graphics/GL46/GLShader.h>
#include <Engine/Input.h>
#include <Graphics/Texture.h>
#include <Graphics/Context.h>
#include <Graphics/Texture.h>
#include <Graphics/Model.h>
#include <Graphics/GL46/GLConfig.h>
#include <Component/TCamera.h>



LPCSTR gvsTest = R"(
#version 450 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 st;

out struct PS{
	vec3 normal;
	vec2 st;
}ps;

void main(){
	gl_Position = vec4(pos,1);
	ps.normal = normal;
	ps.st = st;
};

)";

LPCSTR gpsTest = R"(
#version 450 core

in struct PS{
	vec3 normal;
	vec2 st;
}ps;

out vec4 result;

void main(){

	result = vec4(1,1,1,1);

};

)";



void GLTestScene::InitFrame()
{
	Viewport vp{};

	gContext->GetViewport(&vp);

	camera = new TCamera(45.f, vp.w / vp.h, 0.01f, 100.f);

	float i = 0.5f;


	VertexPNS vertices[] = {
		{{-i,-i,0},		{0,1.f,0},	{0.f,1.f}},
		{{0,i,0},		{0,1.f,0},	{0.0f,0.f}},
		{{i,-i,0},		{0,1.f,0},	{1.f,0.f}},
	};

	uint indices[] = {
		0,1,2,0,2,3
	};

	VertexAttrib attbs[] = {
		{0,Format::Float,3,offsetof(VertexPNS,VertexPNS::position)},
		{0,Format::Float,3,offsetof(VertexPNS,VertexPNS::normal)},
		{0,Format::Float,2,offsetof(VertexPNS,VertexPNS::st)}
	};

	VertexBufferDesc vd{};
	vd.nAttrib = std::size(attbs);
	vd.pAttrib = attbs;
	vd.cbStride = sizeof(VertexPNS);
	vd.pData = vertices;
	vd.cbSize = sizeof(vertices);

	vbo = BufferCache::CreateVertexBuffer(vd);

	IndexBufferDesc id{};
	id.cbSize = sizeof(indices);
	id.nIndices = std::size(indices);
	id.pData = indices;

	ibo = BufferCache::CreateIndexBuffer(id);



	vs = ShaderCache::CreateVertexShaderFromCode(gvsTest);
	ps = ShaderCache::CreatePixelShaderFromCode(gpsTest);

	//camera->LookAt({0,0,-10 }, vec3f(0.f));
	camera->SetPosition({ 0,0.5f,-5 });
}

void GLTestScene::UpdateFrame(float dt)
{
	camera->Update(dt);
}

void GLTestScene::RenderFrame()
{
	vbo->BindPipeline();

	vs->BindPipeline();
	ps->BindPipeline();
	ibo->BindPipeline();
	gContext->SetTopology(Topolgy::TRIANGLELIST);
	gContext->DrawIndexed(3, 0, 0);
}
