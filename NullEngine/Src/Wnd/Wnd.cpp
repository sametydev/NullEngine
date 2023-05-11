#include <PCH.h>
#include <Wnd/Wnd.h>
#include <Wnd/WndConfig.h>

Wnd::Wnd(Wnd* parent, int x, int y, int width, int height) : mParent(parent), geo { x,y,width,height } , mHwnd (nullptr)
{


}

void Wnd::Create()
{
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = "Null Engine";

	if (!GetClassInfoEx(wc.hInstance, wc.lpszClassName, &wc)) {
		wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
		wc.lpfnWndProc = Wnd::GlobalWndProc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //todo owndc performance
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);

		if (!RegisterClassEx(&wc))
		{
			MessageBox(NULL, "Failed to create window class", "ERROR", MB_OK);
		}
	}




	HWND parentHwnd = mParent ? mParent->mHwnd : nullptr;

	DWORD style = WS_VISIBLE; // We dont call it showWindow

	if (parentHwnd)
	{
		style |= WS_CHILD;
	}
	else
	{
		style |= WS_OVERLAPPEDWINDOW;

		//style |= WS_POPUP;
	}

	mHwnd = CreateWindowEx(
		NULL,
		wc.lpszClassName,
		wc.lpszClassName,
		style,
		geo.x,
		geo.y,
		geo.cx,
		geo.cy,
		parentHwnd,
		(HMENU)0,
		wc.hInstance,
		this
	);

	if (!mHwnd)
	{
		MessageBox(NULL, "Failed to create window", "ERROR", MB_OK);
	}
}

void Wnd::OnCreate()
{
}

void Wnd::OnReSize(uint cx, uint cy)
{
}

Wnd::~Wnd()
{
	::DestroyWindow(mHwnd);
}

LRESULT Wnd::LocalWndProc(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:
		OnCreate();
		break;
	case WM_LBUTTONDOWN:
		SetCapture(mHwnd);
		break;
	case WM_LBUTTONUP:
		ReleaseCapture();
		break;
	case WM_SIZE:
		OnReSize(LOWORD(lp), HIWORD(lp));
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(*this,msg,wp,lp);
}

LRESULT __stdcall Wnd::GlobalWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	Wnd* currentWnd = (Wnd*)GetWindowLongPtr(hwnd, GWLP_USERDATA);


	if (msg == WM_CREATE)
	{
		CREATESTRUCT* cs = (LPCREATESTRUCT)lp;
		currentWnd = (Wnd*)cs->lpCreateParams;
		currentWnd->mHwnd = hwnd;
		SetWindowLongPtr(hwnd, GWLP_USERDATA,(LONG_PTR)currentWnd); //register user data
	}
	if (currentWnd)
	{
		//Hook;
		return currentWnd->LocalWndProc(msg,wp,lp);
	}
	return DefWindowProc(hwnd,msg,wp,lp);
}

Wnd::operator HWND()
{
	return mHwnd;
}
