#include <PCH.h>
#include <Scene/InstancingTest.h>
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
#include <Render/Font.h>

void InstancingTest::InitFrame()
{

	font = new Font;
	font->Create("../data/font/arial.ttf",100);
	Viewport vp{};

	gContext->GetViewport(&vp);

	camera = new TCamera(45.f, vp.w / vp.h, 0.01f, 100.f);

	mPlane = ModelCache::CreatePlane(5.f);
	mPlane->SetTexture(0, TextureCache::Load("../data/checker.jpg"));
	ConstantBufferDesc cd{};
	cd.cbSize = sizeof(matrices);
	cd.pData = &matrices;

	mCBO = BufferCache::CreateConstantBuffer(cd);

	camera->SetPosition({ 0,0.5f,-5 });

	mTree = ModelCache::LoadFromFile("../data/tree01.obj");
	mTree->mNodes[0].texture = TextureCache::Load("../data/tree01.png");
	mTree->mNodes[1].texture = TextureCache::Load("../data/tree00.png");

	int size = 5;

	for (int z = -size; z < size; z++) {
		for (int x = -size; x < size; x++)
		{
			mat4x4 t = mat4x4::translated(vec3f(x, 0.f, z));
			instanceData.emplace_back(t);
		}
	}

	gContext->SetTopology(Topolgy::TRIANGLELIST);
	mSceneShader = ShaderCache::CreateShader("SceneInstanceVS","ScenePS");
}

void InstancingTest::UpdateFrame(float dt)
{
	camera->Update(dt);
	matrices.proj = camera->GetProjectionMatrix();
	matrices.view = camera->GetViewMatrix();
	matrices.model = mat4x4();
	mCBO->SubData(&matrices);
}

void InstancingTest::RenderFrame()
{
	mCBO->BindVS(0);
	mSceneShader->Bind();
	mPlane->Render();
	mTree->RenderInstanced(instanceData.size(), instanceData.data());
}
