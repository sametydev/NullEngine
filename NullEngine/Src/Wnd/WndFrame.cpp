#include <PCH.h>
#include <Wnd/WndFrame.h>

WndFrame::WndFrame(Wnd* parent, uint width, uint heigth) : Wnd(parent, 0, 0, width, heigth)
{
	geo.x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	geo.y = (GetSystemMetrics(SM_CYSCREEN) - heigth) / 2;
	Create();
}

WndFrame::~WndFrame()
{

}

void WndFrame::OnCreate()
{
	//Choose API
	RECT rc{};
	::GetClientRect(*this, &rc);

	uint w = rc.right - rc.left;
	uint h = rc.bottom - rc.top;


	mContext = std::make_shared<DXContext>(w, h, *this);
}

void WndFrame::OnReSize(uint cx, uint cy)
{
	if(mContext)   mContext->ResizeRenderBuffer(cx, cy);
}

int WndFrame::ExecFrame(void* scene)
{
	MSG msg{};

	while (msg.message != WM_QUIT)
	{
		if (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);

			DispatchMessage(&msg);
			if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE)
			{
				PostQuitMessage(0);
			}
			
		}
		if (mContext)
		{
			mContext->ClearBuffer(0.4f, 0.2f, 0.2f,1.0f);

			mContext->SwapBuffer();
		}
		//Update

		//Render

		//SwapChain
	}

	return (int)msg.lParam;
}
