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
#include <Render/Font.h>
#include <Render/DXBatch.h>

void Scene01::InitFrame()
{

}

void Scene01::UpdateFrame(float dt)
{

}

void Scene01::RenderFrame()
{
	DXBatch::Instance->Render("Hello", 20, 30);
}
