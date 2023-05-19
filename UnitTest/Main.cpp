#include <PCH.h>
#include <Wnd/WndFrame.h>
#include <Graphics/DX11/DXBuffer.h>
#include <PCH.h>
#include <Scene/GLTestScene.h>
#include <Scene/Scene01.h>
#include <Engine/Timer.h>
#pragma comment(lib, "opengl32")
int main(int args, char* argv[]) {

	WndDesc desc{};
	desc.width = 1024;
	desc.heigth = 680;
	desc.api = GraphicAPI::DirectX11;

	WndFrame wnd(desc);
	GLTestScene scene01;

	return wnd.ExecFrame(nullptr);
}