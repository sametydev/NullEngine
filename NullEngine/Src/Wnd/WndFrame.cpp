#include <PCH.h>
#include <Wnd/WndFrame.h>
#include <Engine/Scene.h>
#include <Engine/Timer.h>
#include <Engine/Input.h>
#include <Graphics/DX11/DXContext.h>
#include <Graphics/GL46/GLContext.h>
#include <Wnd/WndConfig.h>

WndFrame::WndFrame(const WndDesc& desc) : Wnd(nullptr, 0, 0, desc.width, desc.heigth),mApiType(desc.api)
{
	geo.x = (GetSystemMetrics(SM_CXSCREEN) - desc.width) / 2;
	geo.y = (GetSystemMetrics(SM_CYSCREEN) - desc.heigth) / 2;
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
	switch (mApiType)
	{
	case GraphicAPI::DirectX11:
		mContext = std::make_shared<DXContext>(w, h, *this);
		break;
	case GraphicAPI::OpenGL46:
		mContext = std::make_shared<GLContext>(w, h, *this);
		break;
	default:
		LOG_ERROR("Failed to load Graphics API");
		break;
	}

	mBatcher = std::make_shared<DXBatch>();
	mBatcher->Init();

}

void WndFrame::OnReSize(uint cx, uint cy)
{
	//if(mContext)   mContext->ResizeRenderBuffer(cx, cy);
}

int WndFrame::ExecFrame(Scene* scene)
{
	if (scene) {
		scene->InitFrame();
	}


	MSG msg{};

	while (msg.message != WM_QUIT)
	{

		if (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE)) {
			TranslateMessage(&msg);
			//Input::HookMsg(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE)
			{
				PostQuitMessage(0);
			}
			
		}
		if (mContext)
		{
			Timer::instance()->Update();
			Input::Update(*this);
			
			//Batch Begin
			//TODO :: Batch Begin
			mBatcher->Begin();

			mContext->ClearBuffer(0.2f, 0.2f, 0.2f,1.0f);
			if (scene)
			{
				scene->UpdateFrame(Timer::instance()->deltaTime);
				scene->RenderFrame();
			}
			mBatcher->End();

			mContext->SwapBuffer();
		}
		//Update
		
		//Render

		//SwapChain
	}

	return (int)msg.lParam;
}
