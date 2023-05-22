#include <PCH.h>
#include <Render/ShadowPass.h>
#include <Graphics/Context.h>
#include <Graphics/DX11/DX11Config.h>
#include <Graphics/DX11/DXTexture.h>

ShadowPass::ShadowPass()
{
}

void ShadowPass::Create(uint width, uint height)
{
	this->width = width;
	this->height = height;

	D3D11_TEXTURE2D_DESC td{};
	td.Width = width;
	td.Height = height;
	td.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;     //normaly
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.SampleDesc.Count = 1;
	td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;

	ID3D11Texture2D* tex2d = nullptr;  //TEST+

	HR(gDXDevice->CreateTexture2D(&td, nullptr, &tex2d));

	D3D11_RENDER_TARGET_VIEW_DESC vd{};
	vd.Format = td.Format;
	vd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	vd.Texture2D.MipSlice = 0;


	HR(gDXDevice->CreateRenderTargetView(tex2d, &vd, &mRtv));
	

	D3D11_SHADER_RESOURCE_VIEW_DESC srd{};
	srd.Format = td.Format;
	srd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srd.Texture2D.MostDetailedMip = 0;
	srd.Texture2D.MipLevels = 1;

	auto colorPtr = std::make_shared<DXTexture>();
	colorPtr->width = width;
	colorPtr->height = height;
	

	HR(gDXDevice->CreateShaderResourceView(tex2d, &srd, &colorPtr->mSRV));
	
	mTexture = colorPtr;


	D3D11_TEXTURE2D_DESC depthDesc{};
	depthDesc.Width = width;
	depthDesc.Height = height;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	ID3D11Texture2D* depth2d = nullptr;

	HR(gDXDevice->CreateTexture2D(&depthDesc, nullptr, &depth2d));

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd{};
	dsvd.Format = depthDesc.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0;

	HR(gDXDevice->CreateDepthStencilView(depth2d, &dsvd, &mDsv));

	SAFE_RELEASE(tex2d);
	SAFE_RELEASE(depth2d);

	//first we need view matrix and projection matrix
}
