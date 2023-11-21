#include <PCH.h>
#include <Scene/Shadow.h>
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


void Shadow::InitFrame()
{
	Viewport vp{};

	gContext->GetViewport(&vp);

	camera = new TCamera(45.f, vp.w / vp.h, 0.01f, 100.f);

	mShadowPass = std::make_shared<ShadowPass>();
	mShadowPass->Create(1024, 1024);

	mPlane = ModelCache::CreatePlane(5.f);
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

	mShadowShader = ShaderCache::CreateShader("ShadowVS", "ShadowPS");

	gContext->SetTopology(Topolgy::TRIANGLELIST);
	gContext->SetSampler(0, SamplerState::WRAP);
	gContext->SetSampler(1, SamplerState::CLAMP);
}

void Shadow::UpdateFrame(float dt)
{
	camera->Update(dt);
	matrices.proj = camera->GetProjectionMatrix();
	matrices.view = camera->GetViewMatrix();
	matrices.model = mat4x4();
	mCBO->SubData(&matrices);

	//Bind Light Matrix
	lightMatrices.proj = mShadowPass->projection;
	lightMatrices.view = mShadowPass->view;
	lightMatrices.pos = mShadowPass->lightPosition;
	lightMatrices.padding = 0.f;
	mLightCBO->SubData(&lightMatrices);
	mLightCBO->BindVS(1);
}

void Shadow::RenderFrame()
{
	//Render DepthMap with Light Matrix
	matrices.proj = mShadowPass->projection;
	matrices.view = mShadowPass->view;
	matrices.model = mat4x4();

	mCBO->SubData(&matrices);
	mCBO->BindVS(0);

	mShadowPass->Bind();

	Renderable* models[2] = {mTree,mPlane};
	mShadowPass->Render(models,std::size(models));

	mShadowPass->UnBind();

	//Back to Main Matrix
	matrices.proj = camera->GetProjectionMatrix();
	matrices.view = camera->GetViewMatrix();
	matrices.model = mat4x4();

	mCBO->SubData(&matrices);
	mCBO->BindVS(0);

	mLightCBO->BindVS(1);

	mShadowShader->Bind();

	Texture* depth = mShadowPass->GetDepthMap();
	depth->Bind(1);
	mTree->Render();
	mPlane->Render();
	depth->UnBind();
}
