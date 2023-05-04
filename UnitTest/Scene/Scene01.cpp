#include <PCH.h>
#include <Scene/Scene01.h>
#include <Graphics/DX11/DXBuffer.h>
#include <Graphics/DX11/DXShader.h>
#include <Graphics/Vertex.h>
#include <Engine/Input.h>

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


	//input->LockCursor(true);
	LOG << vp.Width;
	//input->SetLockArea(rect(860, 640));

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
	mat4x4 ry = mat4x4::rotateX(rot.y);    //yaw
	mat4x4 rx = mat4x4::rotateY(rot.x); //pitch

	mat4x4 R = rx * ry;
	R = mat4x4::transposed(R);
	vec3f right = vec3f(R[0][0], R[0][1], R[0][2]);
	vec3f forward = vec3f(R[2][0], R[2][1], R[2][2]);



	V = R * t;

	MVP = P * V;


	desc.pData = MVP.data();
	desc.cbSize = sizeof(MVP);

	mCBO = BufferCache::Create<DXConstantBuffer>(desc);
	
	texture = new DXTexture();
	texture->Load("../data/wall.jpg");

	return true;
}

void Scene01::UpdateFrame(float dt)
{
	float speed = 128.3;
	float keySpeed = 5.3f;
	if (Input::type == MouseEvent::MOVE) {
		printf("move\n");
		if (Input::state == Key::LMB) {
			vec2f delta = Input::delta;
			rot.x += -delta.x * speed * dt;
			rot.y += -delta.y * speed * dt;
			//LOG << delta << ENDL;
		}
	}


	mat4x4 ry = mat4x4::rotateX(rot.y);    //yaw
	mat4x4 rx = mat4x4::rotateY(rot.x); //pitch

	mat4x4 R = rx * ry;
	//pre multed
	//what is x axis on R  = Right compponet(axis)
	//what is y axis on R = Up commponet
	//what is z axis on R = Foward com
	R = mat4x4::transposed(R);

	vec3f right = vec3f(R[0][0], R[0][1], R[0][2]);
	vec3f foward = vec3f(R[2][0], R[2][1], R[2][2]);

	if (Input::IsKeyDown(Key::W))
	{
		pos += foward * keySpeed * dt;
	}
	if (Input::IsKeyDown(Key::S))
	{
		pos -= foward * keySpeed * dt;
	}

	if (Input::IsKeyDown(Key::D))
	{
		pos += right * keySpeed * dt;
	}
	if (Input::IsKeyDown(Key::A))
	{
		pos -= right * keySpeed * dt;
	}
	T = mat4x4::translated(pos);
	mat4x4 t = t.transposedTranslation(T);

	V = R * t;

	MVP = P * V;

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
