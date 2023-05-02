#include <PCH.h>
#include <Scene/Scene01.h>
#include <Graphics/DX11/DXBuffer.h>
#include <Graphics/DX11/DXShader.h>
#include <Graphics/Vertex.h>
#include <Engine/InputSystem.h>

LPCSTR vsCode = R"(
cbuffer matrices : register(b0)
{
	//matrix proj;
	//matrix model;
	matrix mvp;
};

struct VS_IN{
	float3 pos : POSITION;
	float3 col : COLOR;
};

struct PS_IN{
	float4 pos : SV_POSITION;
	float3 col : COLOR;
};

PS_IN VS(VS_IN vs){
	PS_IN ps;
	ps.pos = mul(float4(vs.pos,1),mvp);
	ps.col = vs.col;
	return ps;
};
)";


LPCSTR psCode = R"(
struct PS_IN{
	float4 pos : SV_POSITION;
	float3 col : COLOR;
};

float4 PS(PS_IN ps) : SV_TARGET
{
	return float4(ps.col,1);
};
)";


bool Scene01::InitFrame()
{
	D3D11_VIEWPORT vp{};
	uint nVp = 1;

	gDXContext->RSGetViewports(&nVp, &vp);

	float aspect = vp.Width / vp.Height;

	P = mat4x4::perspectiveLH(45.f, aspect, 0.01f, 100.f);


	float i = 0.5f;


	VertexPC vertices[] = {
		{{-i,-i,0},  {1,0,0,}},
		{{0,i,0},    {1,1,0}},
		{{i,-i,0},   {0,1,1}}
	};

	uint indices[] = {
		{0},
		{1},
		{2}
	};

	
	BufferDesc desc{};

	desc.cbSize = sizeof(vertices);
	desc.pData = vertices;
	desc.stride = sizeof(VertexPC);

	mVBO = BufferCache::Create<DXVertexBuffer>(desc);

	mVBO->BindPipeline(0);
	

	ShaderDesc sd;
	sd.element = VertexPC::elements;
	sd.numberOfElements = VertexPC::nElements;
	sd.code = vsCode;
	sd.type = ShaderType::Vertex;

	mVS = ShaderCache::Create(&sd);

	sd.type = ShaderType::Pixel;
	sd.code = psCode;

	mPS = ShaderCache::Create(&sd);

	desc.pData = indices;
	desc.cbSize = sizeof(indices);
	desc.indices = 3;

	mIBO = BufferCache::Create<DXIndexBuffer>(desc);
	pos = { 0,0,-10 };

	T = mat4x4::translated(pos);
	mat4x4 t = t.transposedTranslation(T);
	mat4x4 r = mat4x4::rotateY(angle);


	//define as SRT
	V = r*t;

	//define as PVM
	MVP = P * V;


	desc.pData = MVP.data();
	desc.cbSize = sizeof(MVP);

	mCBO = BufferCache::Create<DXConstantBuffer>(desc);
	
	return true;
}

void Scene01::UpdateFrame(float dt)
{
	auto deltaM = input->GetDeltaMouse();
	angle += deltaM.x * dt * 1.2f;

	if (input->GetKeyDown(NKey::W))
	{
		pos.z += 0.8f * dt;
	}
	if (input->GetKeyDown(NKey::S))
	{
		pos.z -= 0.8f * dt;
	}

	if (input->GetKeyDown(NKey::A))
	{
		pos.x += 0.8f * dt;
	}
	if (input->GetKeyDown(NKey::D))
	{
		pos.x -= 0.8f * dt;
	}


	T = mat4x4::translated(pos);
	mat4x4 t = t.transposedTranslation(T);
	mat4x4 r = mat4x4::rotateY(angle);

	V = r*t;

	MVP = P*V;

	mCBO->SubData(MVP.data());
}

void Scene01::RenderFrame()
{
	mVBO->BindPipeline();
	mIBO->BindPipeline();

	mVS->BindPipeline();
	mPS->BindPipeline();

	mCBO->BindPipeline(0);

	gDXContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	gDXContext->DrawIndexed(mIBO->GetIndices(), 0,0);
}
