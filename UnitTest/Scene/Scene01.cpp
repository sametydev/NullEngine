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
#include <Render/BasicBatch.h>

void Scene01::InitFrame()
{
	testTexture = TextureCache::Load("../data/checker.jpg");
}

void Scene01::UpdateFrame(float dt)
{
}

void Scene01::RenderFrame()
{
	BasicBatch::Instance->Render(50, 50, 128, 128);

	DXFontBatch::Instance->Render("Hello World!", 20, 30);

}
