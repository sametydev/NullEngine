#include <PCH.h>
#include <Wnd/WndFrame.h>
#include <Graphics/DX11/DXBuffer.h>
#include <PCH.h>
#include <Scene/GLTestScene.h>
#include <Engine/Timer.h>

int main(int args, char* argv[]) {

	WndDesc desc{};
	desc.width = 1024;
	desc.heigth = 680;
	desc.api = GraphicAPI::OpenGL46;

	WndFrame wnd(desc);
	GLTestScene scene01;
	

	return wnd.ExecFrame(nullptr);
}