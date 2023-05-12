#include <PCH.h>
#include <Graphics/Context.h>

Context* Context::gInstance = nullptr;

Context::Context(int cx, int cy, HWND hwnd) :
	width(cx), height(cx), mHwnd(hwnd),
	mIsMsaaEnable(true), Msaa(0),
	mFlipModel(false)
{
	if (!gInstance)
	{
		gInstance = this;
	}
	else
	{
		LOG_ERROR("Engine doesn't supports multiple graphic contexts!");
	}
}

ID3D11DeviceContext* Context::GetDXContext()
{
	return nullptr;
}

ID3D11Device* Context::GetDXDevice()
{
	return nullptr;
}
