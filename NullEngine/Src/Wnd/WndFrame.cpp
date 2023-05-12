#include <PCH.h>
#include <Wnd/WndFrame.h>
#include <Engine/Scene.h>
#include <Engine/Timer.h>
#include <Engine/Input.h>
#include <Graphics/DX11/DXContext.h>
#include <Wnd/WndConfig.h>

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
	//if(mContext)   mContext->ResizeRenderBuffer(cx, cy);
}

int WndFrame::ExecFrame(Scene* scene)
{
	if (scene) {
		if (!scene->InitFrame())
		{
			LOG_ERROR("Failed to init scene");
		}
	}


	MSG msg{};

	while (msg.message != WM_QUIT)
	{

		if (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE)) {
			TranslateMessage(&msg);
			Input::HookMsg(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE)
			{
				PostQuitMessage(0);
			}
			
		}
		else
		{
			Input::DiscardEvents();
		}
		if (mContext)
		{
			Timer::instance()->Update();
			mContext->ClearBuffer(0.4f, 0.2f, 0.2f,1.0f);
			if (scene)
			{
				
				scene->UpdateFrame(Timer::instance()->deltaTime);
				scene->RenderFrame();
			}
			mContext->SwapBuffer();
		}
		//Update
		
		//Render

		//SwapChain
	}

	return (int)msg.lParam;
}
