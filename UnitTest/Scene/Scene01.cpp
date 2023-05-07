#include <PCH.h>
#include <Scene/Scene01.h>
#include <Graphics/DX11/DXBuffer.h>
#include <Graphics/DX11/DXShader.h>
#include <Graphics/Vertex.h>
#include <Engine/Input.h>
#include <Graphics/Texture.h>
#include <Graphics/DX11/DXContext.h>
#include <Graphics/DX11/DXTexture.h>
#include <Graphics/DX11/DXModel.h>

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

	
	BufferDesc desc{};

	desc.cbSize = sizeof(vertices);
	desc.pData = vertices;
	desc.stride = sizeof(VertexPC);

	//CreateVertexBuffer
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


	mat4x4 T = mat4x4::translated(vec3f(0,0,-5));
	mat4x4 ry = mat4x4::rotateX(rot.y);    //yaw
	mat4x4 rx = mat4x4::rotateY(rot.x); //pitch

	//ry(yaw) * rx(pitch) * rz(roll)
	mat4x4 R = ry * rx;

	vec3f right = vec3f(R[0][0], R[1][0], R[2][0]);
	vec3f forward = vec3f(R[0][2], R[1][2], R[2][2]);

	//V = (R-1 * T-1)
	
	//00 01 02 03
	//10 11 12 13
	//20 21 22 23
	//30 31 32 33
	desc.cbSize = sizeof(matrices);
	desc.pData  = &matrices;
	


	mCBO = BufferCache::Create<DXConstantBuffer>(desc);
	
	texture = new DXTexture();
	//texture->Load("../data/wall.jpg");
	texture = TextureCache::Load("../data/wall.jpg");

	//Matrices
	Viewport vp;
	gContext->GetViewport(&vp);
	matrices.proj = mat4x4::perspectiveLH(45.f, (float)(vp.w/vp.h), 0.01f, 100.f);

	model = new DXModel();

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


	mat4x4 ry = mat4x4::rotateX(rot.y);    //yaw
	mat4x4 rx = mat4x4::rotateY(rot.x); //pitch

	mat4x4 R = ry * rx;
	//pre multed
	//what is x axis on R  = Right compponet(axis)
	//what is y axis on R = Up commponet
	//what is z axis on R = forward com


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
	mat4x4 invR = mat4x4::transposed(R);
	mat4x4 invT = mat4x4::transposedTranslation(T);

	//V = (R-1*T-1)
	//matrices.view = invR * invT;
	//V = (TR)-1
	//V = S R T;
	// wa mult (T*R*S).inverted()
	matrices.view = (T*R).inverted();
	static vec3f modelPos = {};
	if (Input::IsKeyDown(Key::C))
	{
		modelPos.x -= 3.3f * keySpeed * dt;
	}

	mat4x4 model = mat4x4::translated(modelPos);
	matrices.model = model;

	mCBO->SubData(&matrices);
}

void Scene01::RenderFrame()
{
	mVBO->BindPipeline();
	mIBO->BindPipeline();

	mVS->BindPipeline();
	mPS->BindPipeline();

	mCBO->BindPipeline(0);
	texture->BindPipeline(0);


	gDXContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	gDXContext->DrawIndexed(mIBO->GetIndices(), 0,0);
}
