#include <PCH.h>
#include <Scene/Scene01.h>
#include <Graphics/DX11/DXBuffer.h>
#include <Graphics/DX11/DXShader.h>

LPCSTR vsCode = R"(
cbuffer matrices : register(b0)
{
	matrix world;
};

struct VS_IN{
	float3 pos : POSITION;
};

struct PS_IN{
	float4 pos : SV_POSITION;
};

PS_IN VS(VS_IN vs){
	
	PS_IN ps;
	ps.pos = mul(float4(vs.pos,1),world);

	return ps;
};
)";


LPCSTR psCode = R"(
struct PS_IN{
	float4 pos : SV_POSITION;
};

float4 PS(PS_IN ps) : SV_TARGET
{
	return float4(1,0,0,1);
};
)";


bool Scene01::InitFrame()
{
	float i = 0.5f;

	Vertex vertices[] = {
		{{-i,-i,0}},
		{{0,i,0}},
		{{i,-i,0}}
	};

	uint indices[] = {
		{0},
		{1},
		{2}
	};

	
	BufferDesc desc{};

	desc.cbSize = sizeof(Vertex) * ARRAYSIZE(vertices);
	desc.pData = vertices;
	desc.stride = sizeof(Vertex);

	mVBO = new DXVertexBuffer();
	mVBO->Create(desc);

	mVBO->BindPipeline(0);
	
	D3D11_INPUT_ELEMENT_DESC ied[]{

		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex,Vertex::pos), D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	ShaderDesc sd;
	sd.element = ied;
	sd.numberOfElements = ARRAYSIZE(ied);
	sd.code = vsCode;
	sd.type = ShaderType::Vertex;

	mVS = ShaderCache::Create(&sd);

	sd.type = ShaderType::Pixel;
	sd.code = psCode;

	mPS = ShaderCache::Create(&sd);

	desc.pData = indices;
	desc.cbSize = sizeof(indices);
	desc.indices = 3;

	mIBO = new DXIndexBuffer;
	mIBO->Create(desc);

	float scale[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	
	float rotation[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	float translate[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	//this projection


	desc.pData = model.data();
	desc.cbSize = sizeof(mat4x4);

	mCBO = new DXConstantBuffer;
	mCBO->Create(desc);


	vec3f test(1, 2, 3);

	LOG << test << ENDL;
	
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
