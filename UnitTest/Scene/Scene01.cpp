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

	mPlane = ModelCache::CreatePlane(i);
	mPlane->SetTexture(0, TextureCache::Load("../data/checker.jpg"));
	ConstantBufferDesc cd{};
	cd.cbSize = sizeof(matrices);
	cd.pData = &matrices;

	cbo = BufferCache::CreateConstantBuffer(cd);


	//camera->LookAt({0,0,-10 }, vec3f(0.f));
	camera->SetPosition({ 0,0.5f,-5 });
	matrices.proj = camera->GetProjectionMatrix();

	tree = ModelCache::LoadFromFile("../data/tree01.obj");
	tree->mNodes[0].texture = TextureCache::Load("../data/tree01.png");
	tree->mNodes[1].texture = TextureCache::Load("../data/tree00.png");

	mFrameBuffer = std::make_shared<DXFrameBuffer>();
	FrameBufferDesc fd{};
	fd.width = vp.w;
	fd.height = vp.h;
	fd.nRenderPass = 3;
	fd.bDepthStencil = true;

	mFrameBuffer->Create(fd);

	//00 10
	//01 11
	mScreenVp = std::make_shared<ScreenViewport>();
	mScreenVp->Create();

	mFrameShader = ShaderCache::CreateShader("GBufferVS","GBufferPS");

	gContext->SetTopology(Topolgy::TRIANGLELIST);
}

void Scene01::UpdateFrame(float dt)
{
	camera->Update(dt);
	matrices.proj = camera->GetProjectionMatrix();
	matrices.view = camera->GetViewMatrix();
	matrices.model = mat4x4();

	cbo->SubData(&matrices);
}

void Scene01::RenderFrame()
{

	cbo->BindVS(0);
	mFrameBuffer->BeginFrame();
	mFrameShader->Bind();

	tree->Render();
	mPlane->Render();


	mFrameBuffer->EndFrame();
	//Bind texture from 0 to 1
	mFrameBuffer->BindRenderPass();

	mScreenVp->Render();

	//We need unbind
	mFrameBuffer->UnBindRenderPass();


}
