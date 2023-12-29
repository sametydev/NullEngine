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
#include <Render/DXFontBatch.h>
#include <Component/Object.h>

void Scene01::InitFrame()
{
	SubsystemManager::Create<TestSubystem>();

	testTexture = TextureCache::Load("../data/checker.jpg");

	TestSubystem* mySubTest = SubsystemManager::Get<TestSubystem>();

	Object obj;

	LOG << obj.mIdStr << ENDL;

	basicBatcher = SubsystemManager::Get<BasicBatch>();
	fontBatcher  = SubsystemManager::Get<DXFontBatch>();
}

void Scene01::UpdateFrame(float dt)
{
}

void Scene01::RenderFrame()
{
	//BasicBatch::Instance->Render(10, 10, 128, 128, {0.4,1,0.5,1}); // back
	//BasicBatch::Instance->Render(20, 20, 128, 128);                // front
	basicBatcher->DrawRect(50, 50,128,128,vec3f(1.f,0.5f,1.f));
	basicBatcher->DrawLine(vec2f(0.f),vec2f(100.f), vec3f(.8f, 0.7f, 1.f));
	fontBatcher->Render("Hello World!", 20, 30);

}
