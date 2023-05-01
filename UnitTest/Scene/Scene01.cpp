#include <PCH.h>
#include <Scene/Scene01.h>
#include <Graphics/DX11/DXBuffer.h>
#include <Graphics/DX11/DXShader.h>

LPCSTR hlsl = R"(
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
	sd.code = hlsl;
	sd.type = ShaderType::Vertex;

	mVS = ShaderCache::Create("triVS", &sd);

	sd.type = ShaderType::Pixel;
	mPS = ShaderCache::Create("triPS", &sd);

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

	Mat4x4 s = Mat4x4::rotateZ(90);


	desc.pData = s.data();
	desc.cbSize = sizeof(Mat4x4);

	mCBO = new DXConstantBuffer;
	mCBO->Create(desc);


	
	return true;
}

void Scene01::UpdateFrame(float dt)
{
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
