#include <PCH.h>
#include <Wnd/WndFrame.h>
#include <Graphics/DX11/DXBuffer.h>

int main(int args, char* argv[]) {

	WndFrame wnd(nullptr, 860, 640);


	return wnd.ExecFrame();

}