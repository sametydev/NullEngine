#include <PCH.h>
#include <Graphics/DX11/DXContext.h>
#include <Graphics/DX11/DX11Config.h>

DXContext::DXContext(int cx, int cy, HWND hwnd) :
	Context(cx,cy,hwnd),
	mDevice{nullptr},
	mDeviceContext{nullptr},
	mSwapChain{nullptr},
	mRenderTargetView{nullptr},
	mDepthStencilView{nullptr},
	mDepthStencilBuffer{nullptr}
{
	mApiType = GraphicAPI::DirectX11;

	CreateDevice();
	CreateSwapChain();
	ResizeRenderBuffer(cx, cy);

	mStates.Create();
}

DXContext::~DXContext()
{

	SAFE_RELEASE(mDepthStencilBuffer);
	SAFE_RELEASE(mDepthStencilView);
	SAFE_RELEASE(mRenderTargetView);
	SAFE_RELEASE(mSwapChain);
	SAFE_RELEASE(mDeviceContext);
	SAFE_RELEASE(mDevice);

}

void DXContext::CreateDevice()
{
	uint flag = 0;
#ifdef _DEBUG
	flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;

	uint nDriverType = 1;

	D3D_FEATURE_LEVEL featureLvls[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};

	uint nFeatureLvls = ARRAYSIZE(featureLvls);
	D3D_FEATURE_LEVEL outputFeatureLvl{};

	ID3D11Device* localDevice = nullptr;
	ID3D11DeviceContext* localContext = nullptr;

	HR(D3D11CreateDevice(
		nullptr,
		driverType,
		nullptr,
		flag,
		featureLvls,
		nFeatureLvls,
		D3D11_SDK_VERSION,
		&localDevice,
		&outputFeatureLvl,
		&localContext
	));

	//Upcasting device0 to device1
	HR(localDevice->QueryInterface(IID_PPV_ARGS(&mDevice)));
	HR(localContext->QueryInterface(IID_PPV_ARGS(&mDeviceContext)));

	SAFE_RELEASE(localDevice);
	SAFE_RELEASE(localContext);

	mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_SNORM, 4, &Msaa);

	if (mIsMsaaEnable)
	{
		LOG << "--MSAA Sampling : " << Msaa << ENDL;
	}

}

void DXContext::ResizeRenderBuffer(uint cx, uint cy)
{
	if (!mDevice) return;

	width = cx;
	height = cy;

	SAFE_RELEASE(mRenderTargetView);
	SAFE_RELEASE(mDepthStencilView);
	SAFE_RELEASE(mDepthStencilBuffer);

	ID3D11Texture2D* backBuffer = nullptr;
	HR(mSwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	HR(mSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer)));
	HR(mDevice->CreateRenderTargetView(backBuffer, nullptr, &mRenderTargetView));

	SAFE_RELEASE(backBuffer);

	D3D11_TEXTURE2D_DESC dsd{};
	dsd.Width = cx;
	dsd.Height = cy;
	dsd.MipLevels = 1;
	dsd.ArraySize = 1;
	dsd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsd.SampleDesc.Count = mIsMsaaEnable ? 4 : 1;
	dsd.SampleDesc.Quality = mIsMsaaEnable ? Msaa - 1 : 0;
	dsd.Usage = D3D11_USAGE_DEFAULT;
	dsd.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	HR(mDevice->CreateTexture2D(&dsd, nullptr, &mDepthStencilBuffer));
	HR(mDevice->CreateDepthStencilView(mDepthStencilBuffer, nullptr, &mDepthStencilView));

	mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

	D3D11_VIEWPORT vp{};
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = (float)cx;
	vp.Height = (float)cy;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	mDeviceContext->RSSetViewports(1, &vp);
}

void DXContext::CreateSwapChain()
{
	if (!mDevice) return;

	//DXGI top of device
	IDXGIDevice* dxgiDevice = nullptr;
	IDXGIAdapter* dxgiAdapter = nullptr;
	IDXGIFactory1* dxgiFactory1 = nullptr;
	IDXGIFactory2* dxgiFactory2 = nullptr;

	HR(mDevice->QueryInterface(IID_PPV_ARGS(&dxgiDevice)));
	HR(dxgiDevice->GetAdapter(&dxgiAdapter));
	HR(dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory1)));

	HRESULT hr = (dxgiFactory1->QueryInterface(IID_PPV_ARGS(&dxgiFactory2)));
	if (FAILED(hr))
	{
		LOG_ERROR("DirectX Device is not support %s","11.1");
	}

	DXGI_SWAP_CHAIN_DESC1 sd{};
	sd.Width              = width;
	sd.Height             = height;
	sd.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.SampleDesc.Count   = mIsMsaaEnable ? 4 : 1;
	sd.SampleDesc.Quality = mIsMsaaEnable ? Msaa - 1 : 0;
	sd.BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount        = mFlipModel ? 2:1;
	sd.SwapEffect         = mFlipModel ? DXGI_SWAP_EFFECT_FLIP_DISCARD : DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags              = 0;
	sd.Scaling            = DXGI_SCALING_STRETCH;
	sd.AlphaMode          = DXGI_ALPHA_MODE_UNSPECIFIED;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fd{};
	fd.RefreshRate.Numerator   = 60;
	fd.RefreshRate.Denominator = 1;
	fd.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;
	fd.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	fd.Windowed                = TRUE;

	HR(dxgiFactory2->CreateSwapChainForHwnd(
		mDevice,mHwnd,&sd,&fd,nullptr,&mSwapChain
	));

	//Reverse release
	SAFE_RELEASE(dxgiFactory2);
	SAFE_RELEASE(dxgiFactory1);
	SAFE_RELEASE(dxgiAdapter);
	SAFE_RELEASE(dxgiDevice);

}


void DXContext::ClearBuffer(float r, float g, float b, float a)
{
	const float colors[] = { r,g,b,a };

	mDeviceContext->ClearRenderTargetView(mRenderTargetView, colors);
	mDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

}

void DXContext::SwapBuffer()
{
	mSwapChain->Present(0, 0);
}

void DXContext::DrawIndexed(uint indices, uint offset, uint base)
{
	mDeviceContext->DrawIndexed(indices, offset, base);
}

void DXContext::SetCullMode(CullMode mode)
{
	switch (mode)
	{
		case CullMode::BACK:
			mDeviceContext->RSSetState(mStates.RSCullBack);
			break;
		case CullMode::FRONT:
			mDeviceContext->RSSetState(mStates.RSCullFront);
			break;
		case CullMode::FRONT_AND_BACK:
			mDeviceContext->RSSetState(mStates.RSCullFrontAndBack);
			break;
		case CullMode::WIREFRAME:
			mDeviceContext->RSSetState(mStates.RSWireFrame);
			break;
		default:
			break;
	}
}

void DXContext::SetBlendState(BlendState state)
{
	const float factor[4] = { 0.f,0.f ,0.f ,0.f };
	switch (state)
	{
	case BlendState::Transparent:
		mDeviceContext->OMSetBlendState(mStates.BSTransparent, factor, 0xFFFFFFFF);
		break;
	case BlendState::Disable:
		mDeviceContext->OMSetBlendState(mStates.BSBlendDisable, factor, 0xFFFFFFFF);
		break;
	case BlendState::Inverse:
		mDeviceContext->OMSetBlendState(mStates.BSBlend, factor, 0xFFFFFFFF);
		break;
	default:
		break;
	}
}

ID3D11DeviceContext* DXContext::GetDXContext()
{
	return mDeviceContext;
}

ID3D11Device* DXContext::GetDXDevice()
{
	return mDevice;
}

void DXContext::SetTopology(Topolgy topology)
{
	
	uint id = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;

	switch (topology)
	{
		case Topolgy::UNDEFINED:
			id = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
			break;
		case Topolgy::POINTLIST:
			id = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
			break;
		case Topolgy::LINELIST:
			id = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
			break;
		case Topolgy::LINESTRIP:
			id = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
			break;
		case Topolgy::TRIANGLELIST:
			id = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;
		case Topolgy::TRIANGLESTRIP:
			id = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
			break;
	}
	mDeviceContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)id);
}

void DXContext::GetViewport(Viewport* vp)
{
	D3D11_VIEWPORT dxVp{};


	uint nViewCount = 1;
	mDeviceContext->RSGetViewports(&nViewCount,&dxVp);

	vp->x = dxVp.TopLeftX;
	vp->y = dxVp.TopLeftY;
	vp->w = dxVp.Width;
	vp->h = dxVp.Height;
}

void DXContext::SetSampler(SamplerState sampler)
{
	switch (sampler)
	{
		case SamplerState::WRAP:
			mDeviceContext->PSSetSamplers(0, 1, &mStates.SSWrap);
			break;
		case SamplerState::CLAMP:
			mDeviceContext->PSSetSamplers(0, 1, &mStates.SSClamp);
			break;
	}
}
