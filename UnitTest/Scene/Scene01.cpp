#include <PCH.h>
#include <Scene/Scene01.h>
#include <Graphics/Buffer.h>
#include <Graphics/DX11/DXShader.h>
#include <Engine/Input.h>
#include <Graphics/Texture.h>
#include <Graphics/Context.h>
#include <Graphics/Texture.h>
#include <Graphics/Model.h>
#include <Graphics/DX11/DX11Config.h>
#include <Component/TCamera.h>




LPCSTR vsTest = R"(
cbuffer matrices : register(b0) {
	matrix proj;
	matrix view;
	matrix model;
};


struct VS_IN {
	float3 pos : POSITION;
	float3 normal : TEXCOORD0;
	float2 st  : TEXCOORD1;
};

struct PS_IN {
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float2 st  : TEXCOORD;
};

PS_IN VS(VS_IN vs) {
	PS_IN ps;
	ps.pos = mul(float4(vs.pos,1),model);
	ps.pos = mul(ps.pos,view);
	ps.pos = mul(ps.pos,proj);
	ps.normal = vs.normal;
	ps.st  = vs.st;
	
	return ps;
};

)";

LPCSTR psTest = R"(
Texture2D Texture0 : register(t0);
SamplerState Sampler0 : register(s0);

struct PS_IN {
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float2 st  : TEXCOORD;
};

float4 PS(PS_IN ps) : SV_TARGET {
	float4 albedo = Texture0.Sample(Sampler0,ps.st);
	clip(albedo.a-0.1);
	return albedo;
};
)";


bool Scene01::InitFrame()
{
	Viewport vp{};
	
	gContext->GetViewport(&vp);

	camera = new TCamera(45.f,vp.w/vp.h,0.01f,100.f);

	float i = 10.f;

	//00-10
	//01-11

	//-1 0 -1 (0)
	//-1 0 1 (1)
	//1 0 1 (2)
	//1 0 -1 (3)

	VertexPNS vertices[] = {
		{{-i,0,-i},		{0,1.f,0},	{0.f,1.f}},
		{{-i,0,i},		{0,1.f,0},	{0.0f,0.f}},
		{{i,0,i},		{0,1.f,0},	{1.f,0.f}},
		{{i,0,-i},		{0,1.f,0},	{1.f,1.f}}
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

	ConstantBufferDesc cd{};
	cd.cbSize = sizeof(matrices);
	cd.pData = &matrices;

	cbo = BufferCache::CreateConstantBuffer(cd);

	vs = ShaderCache::CreateVertexShaderFromCode(vsTest);
	ps = ShaderCache::CreatePixelShaderFromCode(psTest);

	//camera->LookAt({0,0,-10 }, vec3f(0.f));
	camera->SetPosition({0,0.5f,-5});
	matrices.proj = camera->GetProjectionMatrix();

	tree = ModelCache::LoadFromFile("../data/tree01.obj");
	texture = TextureCache::Load("../data/style.jpg");
	tree->mNodes[0].texture = TextureCache::Load("../data/tree01.png");
	tree->mNodes[1].texture = TextureCache::Load("../data/tree00.png");

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

	texture->BindPipeline(0);

	vs->BindPipeline();
	ps->BindPipeline();
	ibo->BindPipeline();


	gContext->SetTopology(Topolgy::TRIANGLELIST);

	gContext->SetCullMode(CullMode::BACK);
	gContext->SetBlendState(BlendState::Disable);
	gContext->DrawIndexed(ibo->indices, 0, 0);

	gContext->SetCullMode(CullMode::FRONT_AND_BACK);
	gContext->SetBlendState(BlendState::Transparent);

	tree->Render();
}
