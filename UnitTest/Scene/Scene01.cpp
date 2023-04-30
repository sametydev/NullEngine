#include <PCH.h>
#include <Scene/Scene01.h>
#include <Graphics/DX11/DXBuffer.h>
#include <Graphics/DX11/DXShader.h>

LPCSTR vsCode = R"(
struct VS_IN{
	float3 pos : POSITION;
};

struct PS_IN{
	float4 pos : SV_POSITION;
};

PS_IN VS(VS_IN vs){

	PS_IN ps;
	ps.pos = float4(vs.pos,1);

	return ps;
}
)";


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
	
	mShader = new VertexShader();
	mShader->Create(vsCode);

	D3D11_INPUT_ELEMENT_DESC ied[]{
	
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex,Vertex::pos), D3D11_INPUT_PER_VERTEX_DATA, 0}
	};


	HRESULT hr = gDXDevice->CreateInputLayout(ied, ARRAYSIZE(ied), mShader->byteBinary->GetBufferPointer(),
		mShader->byteBinary->GetBufferSize(), &mLayout
		);

	return true;
}

void Scene01::UpdateFrame(float dt)
{
}

void Scene01::RenderFrame()
{
}
