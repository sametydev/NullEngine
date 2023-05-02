#include <PCH.h>
#include <Scene/Scene01.h>
#include <Graphics/DX11/DXBuffer.h>
#include <Graphics/DX11/DXShader.h>
#include <Graphics/Vertex.h>

LPCSTR vsCode = R"(
cbuffer matrices : register(b0)
{
	matrix world;
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
	ps.pos = mul(float4(vs.pos,1),world);
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
	
	desc.pData = model.data();
	desc.cbSize = sizeof(mat4x4);

	mCBO = BufferCache::Create<DXConstantBuffer>(desc);
	
	return true;
}

void Scene01::UpdateFrame(float dt)
{
	mat4x4 s = mat4x4::scaled(vec3f(0.5f, 0.5f, 0.5f));
	mat4x4 r = mat4x4::rotateZ(90.f);
	mat4x4 t = mat4x4::translated(pos);

	model = s * r * t;

	if (GetAsyncKeyState('A') & 0x8000)
	{
		pos.x += 0.01f;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		pos.x -= 0.01f;
	}

	mCBO->SubData(model.data());
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
