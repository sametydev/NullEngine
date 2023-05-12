#include <PCH.h>
#include <Scene/Scene01.h>
#include <Graphics/Buffer.h>
#include <Graphics/DX11/DXShader.h>
#include <Engine/Input.h>
#include <Graphics/Texture.h>
#include <Graphics/Context.h>
#include <Graphics/Texture.h>
#include <Graphics/DX11/DXModel.h>
#include <Graphics/DX11/DX11Config.h>
#include <Component/Camera.h>


LPCSTR vsCode = R"(
cbuffer matrices : register(b0)
{
    matrix proj;
    matrix view;
    matrix model;   //world
};

struct VS_IN{
    float3 pos	: POSITION;
    float2 st	: TEXCOORD0;
};

struct PS_IN{
    float4 pos : SV_POSITION;
    float2 st : TEXCOORD;
};

PS_IN VS(VS_IN vs){
    PS_IN ps;
    ps.pos = mul(float4(vs.pos,1),model);
    ps.pos = mul(ps.pos, view);
    ps.pos = mul(ps.pos, proj);
    ps.st = vs.st;
    return ps;
};
)";

LPCSTR psCode = R"(
Texture2D Texture01 : register(t0);
SamplerState Sampler01 : register(s0);
struct PS_IN{
	float4 pos : SV_POSITION;
	float2 st  : TEXCOORD;
};

float4 PS(PS_IN ps) : SV_TARGET
{
	float4 albedo = Texture01.Sample(Sampler01,ps.st);

	return albedo;
};
)";

LPCSTR vsTest = R"(
cbuffer matrices : register(b0) {
	matrix proj;
	matrix view;
	matrix model;
};


struct VS_IN {
	float3 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD;
};

PS_IN VS(VS_IN vs) {
	PS_IN ps;
	ps.pos = mul(float4(vs.pos,1),model);
	ps.pos = mul(ps.pos,view);
	ps.pos = mul(ps.pos,proj);

	ps.uv  = vs.uv;
	
	return ps;
};

)";

LPCSTR psTest = R"(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD;
};

float4 PS(PS_IN ps) : SV_TARGET {
	
	return ps.pos;
};
)";


bool Scene01::InitFrame()
{
	Viewport vp{};
	
	gContext->GetViewport(&vp);

	camera = new Camera(45.f,vp.w/vp.h,0.01f,100.f);

	float i = 1.f;

	//00-10
	//01-11

	VertexPC vertices[] = {
		{{-i,-i,0},  {0,1}},
		{{0,i,0},    {0.5f,0}},
		{{i,-i,0},   {1,1}}
	};

	uint indices[] = {
		{0},
		{1},
		{2}
	};

	VertexAttrib attbs[] = {
		{0,Format::Float,3,offsetof(VertexPC,VertexPC::position)},
		{0,Format::Float,2,offsetof(VertexPC,VertexPC::st)}
	};
	
	VertexBufferDesc vd{};
	vd.nAttrib = std::size(attbs);
	vd.pAttrib = attbs;
	vd.cbStride = sizeof(VertexPC);
	vd.pData = vertices;
	vd.cbSize = sizeof(vertices);

	vbo = BufferCache::CreateVertexBuffer(vd);

	IndexBufferDesc id{};
	id.cbSize = sizeof(indices);
	id.nIndices = std::size(indices);
	id.pData = indices;

	ibo = BufferCache::CreateIndexBuffer(id);

	ConstantBufferDesc cd{};
	cd.cbSize = sizeof(matrices);
	cd.pData = &matrices;

	cbo = BufferCache::CreateConstantBuffer(cd);

	vs = ShaderCache::CreateVertexShaderFromCode(vsTest);
	ps = ShaderCache::CreatePixelShaderFromCode(psTest);

	camera->LookAt({ 10,10,-10 }, vec3f(0.f));

	matrices.proj = camera->GetProjectionMatrix();
	matrices.view = camera->GetViewMatrix();
	matrices.model = mat4x4();

	cbo->SubData(&matrices);

	return true;
}

void Scene01::UpdateFrame(float dt)
{
	camera->Update(dt);
	matrices.view = camera->GetViewMatrix();
	cbo->SubData(&matrices);
}

void Scene01::RenderFrame()
{

	cbo->BindPipeline(0);
	vbo->BindPipeline();
	vs->BindPipeline();
	ps->BindPipeline();



	//texture->BindPipeline(0);

	gContext->SetTopology(Topolgy::TRIANGLELIST);

	gDXContext->Draw(3, 0);
	//mModel->Render();
}
