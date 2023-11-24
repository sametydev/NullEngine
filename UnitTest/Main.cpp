#include <PCH.h>
#include <Wnd/WndFrame.h>
#include <Graphics/DX11/DXBuffer.h>
#include <PCH.h>

#include <Scene/Shadow.h>
#include <Scene/InstancingTest.h>
#include <Scene/Scene01.h>
#include <Engine/Timer.h>
#include <Core/FileSystem.h>

int main(int args, char* argv[]) {

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	WndDesc desc{};
	desc.width = 1024;
	desc.heigth = 680;
	desc.api = GraphicAPI::DirectX11;

	WndFrame wnd(desc);
	InstancingTest scene01;
	scene01.ref = wnd.mHwnd;

	return wnd.ExecFrame(&scene01);
}