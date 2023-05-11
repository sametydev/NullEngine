#include <PCH.h>
#include <Scene/Scene01.h>
#include <Graphics/Buffer.h>
#include <Graphics/DX11/DXShader.h>
#include <Graphics/Vertex.h>
#include <Engine/Input.h>
#include <Graphics/Texture.h>
#include <Graphics/Context.h>
#include <Graphics/Texture.h>
#include <Graphics/DX11/DXModel.h>
#include <Graphics/DX11/DX11Config.h>

LPCSTR vsCode = R"(
cbuffer matrices : register(b0)
{
    matrix proj;
    matrix view;
    matrix model;   //world
};

struct VS_IN{
    float3 pos : POSITION;
    float2 st : TEXCOORD;
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


bool Scene01::InitFrame()
{
	Viewport vp{};
	
	gContext->GetViewport(&vp);

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
		{0,Format::Float,3,sizeof(VertexPC),offsetof(VertexPC,vertices)}
	};


	matrices.proj = mat4x4::perspectiveLH(45.f, vp.w /vp.h,0.01f,100.f);
	
	VertexBufferDesc vd{};
	vd.cbSize = sizeof(vertices);
	vd.cbStride = sizeof(VertexPC);
	vd.pData = vertices;

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

	return true;
}

void Scene01::UpdateFrame(float dt)
{
	float speed = 128.3;
	float keySpeed = 5.3f;
	if (Input::type == MouseEvent::MOVE) {
		//printf("move\n");
		if (Input::state == Key::LMB) {
			vec2f delta = Input::delta;
			rot.x += -delta.x * speed * dt;
			rot.y += -delta.y * speed * dt;
			//LOG << delta << ENDL;
		}
	}


	mat4x4 ry = mat4x4::rotateX(rot.y);		//yaw
	mat4x4 rx = mat4x4::rotateY(rot.x);		//pitch

	mat4x4 R = ry * rx;

	matrices.model = mat4x4();

	vec3f right = vec3f(R[0][0], R[1][0], R[2][0]);
	vec3f forward = vec3f(R[0][2], R[1][2], R[2][2]);

	if (Input::IsKeyDown(Key::W))
	{
		pos += forward * keySpeed * dt;
	}
	if (Input::IsKeyDown(Key::S))
	{
		pos -= forward * keySpeed * dt;
	}

	if (Input::IsKeyDown(Key::D))
	{
		pos += right * keySpeed * dt;
	}
	if (Input::IsKeyDown(Key::A))
	{
		pos -= right * keySpeed * dt;
	}

	mat4x4 T = mat4x4::translated(pos);
	mat4x4 V = R * T;
	
	matrices.view = V.inverted();

	cbo->SubData(&matrices);
}

void Scene01::RenderFrame()
{

	mVS->BindPipeline();
	mPS->BindPipeline();

	cbo->BindPipeline(0);
	texture->BindPipeline(0);

	gContext->SetTopology(Topolgy::TRIANGLELIST);

	//mModel->Render();
}
