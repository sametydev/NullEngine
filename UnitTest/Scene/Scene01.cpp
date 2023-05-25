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
#include <Render/ShadowPass.h>


void Scene01::InitFrame()
{
	Viewport vp{};

	gContext->GetViewport(&vp);

	camera = new TCamera(45.f, vp.w / vp.h, 0.01f, 100.f);

	mShadowPass = std::make_shared<ShadowPass>();
	mShadowPass->Create(1024, 1024);

	float i = 10.f;

	mPlane = ModelCache::CreatePlane(i);
	mPlane->SetTexture(0, TextureCache::Load("../data/checker.jpg"));
	ConstantBufferDesc cd{};
	cd.cbSize = sizeof(matrices);
	cd.pData = &matrices;

	mCBO = BufferCache::CreateConstantBuffer(cd);

	cd.cbSize = sizeof(lightMatrices);
	cd.pData = &lightMatrices;

	mLightCBO = BufferCache::CreateConstantBuffer(cd);

	//camera->LookAt({0,0,-10 }, vec3f(0.f));
	camera->SetPosition({ 0,0.5f,-5 });
	matrices.proj = camera->GetProjectionMatrix();

	mTree = ModelCache::LoadFromFile("../data/model/knot.obj");
	mTree->mNodes[0].texture = TextureCache::Load("../data/checker.jpg");

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
	mCBO->SubData(&matrices);

	lightMatrices.proj = mShadowPass->projection;
	lightMatrices.view = mShadowPass->view;
	lightMatrices.pos = mShadowPass->lightPosition;

	mLightCBO->SubData(&lightMatrices);
}

void Scene01::RenderFrame()
{
	RenderDepth();
	matrices.proj = mShadowPass->projection;
	matrices.view = mShadowPass->view;
	matrices.model = mat4x4();

	mCBO->SubData(&matrices);
	mCBO->BindVS(0);

	mShadowPass->Bind();
	Renderable* models[2] = {mTree,mPlane};
	mShadowPass->Render(models,std::size(models));

	mShadowPass->UnBind();


}

void Scene01::RenderDepth()
{
	matrices.proj = mShadowPass->projection;
	matrices.view = mShadowPass->view;
	matrices.model = mat4x4();

	mCBO->SubData(&matrices);
	mCBO->BindVS(0);

	mShadowPass->Bind();
	
	mTree->Render();
	mPlane->Render();

	mShadowPass->UnBind();

	auto texture = mShadowPass->GetDepthMap();
	texture->Bind(0);
	mScreenVp->Render();
	texture->UnBind();


}
