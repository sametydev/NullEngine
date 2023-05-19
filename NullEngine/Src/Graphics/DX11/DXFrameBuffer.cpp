#include <PCH.h>
#include <Graphics/DX11/DXFrameBuffer.h>
#include <Graphics/DX11/DX11Config.h>
#include <Graphics/DX11/DXTexture.h>
#include <Graphics/Context.h>

DXFrameBuffer::DXFrameBuffer()
{

}

void DXFrameBuffer::Create(const FrameBufferDesc& desc)
{
	width = desc.width;
	height = desc.height;

	D3D11_TEXTURE2D_DESC txd{};
	txd.Width = width;
	txd.Height = height;
	txd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	txd.MipLevels = 1;
	txd.ArraySize = 1;
	txd.Usage = D3D11_USAGE_DEFAULT;
	txd.SampleDesc.Count = 1;
	txd.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	txd.CPUAccessFlags = 0;
	txd.MiscFlags = 0;

	mRenderPass.resize(desc.nRenderPass);
	mTexture2D.resize(desc.nRenderPass);


	for (int i = 0; i < desc.nRenderPass; i++)
	{
		gDXDevice->CreateTexture2D(&txd, nullptr, &mTexture2D[1]);
	}

	D3D11_RENDER_TARGET_VIEW_DESC vd{};
	vd.Format = txd.Format;
	vd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	vd.Texture2D.MipSlice = 0;

	mRenderTargetViews.resize(desc.nRenderPass);

	for (int i = 0; i < desc.nRenderPass; i++)
	{
		gDXDevice->CreateRenderTargetView(mTexture2D[i],&vd,&mRenderTargetViews[i]);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srd{};
	srd.Format = txd.Format;
	srd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srd.Texture2D.MostDetailedMip = 0;
	srd.Texture2D.MipLevels = 1;

	mRenderPass.resize(desc.nRenderPass);

	for (int i = 0; i < desc.nRenderPass; i++)
	{
		auto renderPass = std::make_shared<DXTexture>();
		renderPass->width = width;
		renderPass->height = height;
		auto srv = renderPass->mSRV;
		HR(gDXDevice->CreateShaderResourceView(mTexture2D[i], &srd, &srv));
	}

	if (bDepthStencil)
	{
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

		gDXDevice->CreateTexture2D(&depthDesc, nullptr, &mDepthTexture2D);

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd{};
		dsvd.Format = depthDesc.Format;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvd.Texture2D.MipSlice = 0;

		HR(gDXDevice->CreateDepthStencilView(mDepthTexture2D, &dsvd, &mDepthStencilView));
	}
}

void DXFrameBuffer::BeginFrame()
{
}

void DXFrameBuffer::EndFrame()
{
}
