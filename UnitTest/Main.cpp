#include <PCH.h>
#include <Wnd/WndFrame.h>
#include <Graphics/DX11/DXBuffer.h>
#include <PCH.h>
#include <Scene/Scene01.h>

int main(int args, char* argv[]) {

	WndFrame wnd(nullptr, 860, 640);
	Scene01 scene01;


	return wnd.ExecFrame(&scene01);

}