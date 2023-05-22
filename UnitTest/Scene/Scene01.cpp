#include <PCH.h>
#include <Scene/Scene01.h>
#include <Graphics/Buffer.h>
#include <Graphics/DX11/DXShader.h>
#include <Engine/Input.h>
#include <Graphics/Texture.h>
#include <Graphics/Context.h>
#include <Graphics/Texture.h>
#include <Graphics/Model.h>
#include <Graphics/DX11/DXFrameBuffer.h>
#include <Graphics/DX11/DX11Config.h>
#include <Component/TCamera.h>
#include <Render/ScreenViewport.h>



void Scene01::InitFrame()
{
	Viewport vp{};

	gContext->GetViewport(&vp);

	camera = new TCamera(45.f, vp.w / vp.h, 0.01f, 100.f);

	float i = 10.f;

	mScreenVp = std::make_shared<ScreenViewport>();
	mScreenVp->Create();

	mPlane = ModelCache::CreatePlane(i);

	ConstantBufferDesc cd{};
	cd.cbSize = sizeof(matrices);
	cd.pData = &matrices;

	cbo = BufferCache::CreateConstantBuffer(cd);


	//camera->LookAt({0,0,-10 }, vec3f(0.f));
	camera->SetPosition({ 0,0.5f,-5 });
	matrices.proj = camera->GetProjectionMatrix();

	tree = ModelCache::LoadFromFile("../data/tree01.obj");
	texture = TextureCache::Load("../data/style.jpg");
	tree->mNodes[0].texture = TextureCache::Load("../data/tree01.png");
	tree->mNodes[1].texture = TextureCache::Load("../data/tree00.png");

	fbo = new DXFrameBuffer();
	FrameBufferDesc fd{};
	fd.width = vp.w;
	fd.height = vp.h;
	fd.nRenderPass = 2;
	fd.bDepthStencil = false;

	fbo->Create(fd);

	//00 10
	//01 11
	


	frameShaderVS = ShaderCache::CreateShader("GBuffer","GBuffer");
}

void Scene01::UpdateFrame(float dt)
{
	camera->Update(dt);
	matrices.view = camera->GetViewMatrix();

	cbo->SubData(&matrices);
}

void Scene01::RenderFrame()
{

	//Bind frame buffer
	//--------------------------
	fbo->BeginFrame();
	fbo->Clear(0.f, 0.f, 0.f, 1.f);

	frameShaderVS->Bind();

	gContext->SetTopology(Topolgy::TRIANGLELIST);

	cbo->BindVS(0);
	cbo->BindPS(0);


	texture->Bind(0);

	mPlane->Render();
	tree->Render();
	//-----------------------
	fbo->EndFrame();


	fbo->BindRenderPass();

	mScreenVp->Render();

	fbo->UnBindRenderPass();
}
