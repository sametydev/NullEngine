#include <PCH.h>
#include <Graphics/DX11/DXRenderState.h>
#include <Graphics/DX11/DX11Config.h>
#include <Graphics/Context.h>


DXRenderState::DXRenderState()
{
}

DXRenderState::~DXRenderState()
{

}

void DXRenderState::Create()
{
	CreateRSState();
	CreateSamplerState();
	CreateBlendState();
	CreateDepthStencilState();
	bStateCreated = true;
}

void DXRenderState::ReleaseStates()
{
	//Release all of states release devices before
	gDXContext->ClearState();
	SAFE_RELEASE(RSCullBack);
	SAFE_RELEASE(RSCullFront);
	SAFE_RELEASE(RSCullFrontAndBack);
	SAFE_RELEASE(RSWireFrame);

	SAFE_RELEASE(SSWrap);
	SAFE_RELEASE(SSClamp);

	SAFE_RELEASE(BSTransparent);
	SAFE_RELEASE(BSBlendDisable);
	SAFE_RELEASE(BSBlend);
}

void DXRenderState::CreateRSState()
{
	D3D11_RASTERIZER_DESC rd{};
	rd.CullMode              = D3D11_CULL_BACK;
	rd.FillMode              = D3D11_FILL_SOLID;
	rd.FrontCounterClockwise = false;
	rd.DepthClipEnable       = true;
	rd.MultisampleEnable     = gContext->mIsMsaaEnable;
	rd.AntialiasedLineEnable = false;

	HR(gDXDevice->CreateRasterizerState(&rd, &RSCullBack));

	rd.CullMode = D3D11_CULL_FRONT;
	HR(gDXDevice->CreateRasterizerState(&rd, &RSCullFront));

	rd.CullMode = D3D11_CULL_NONE;
	HR(gDXDevice->CreateRasterizerState(&rd, &RSCullFrontAndBack));

	rd.CullMode = D3D11_CULL_BACK;
	rd.FillMode = D3D11_FILL_WIREFRAME;
	HR(gDXDevice->CreateRasterizerState(&rd, &RSWireFrame));

	gDXContext->RSSetState(RSCullBack);
}

void DXRenderState::CreateSamplerState()
{
	D3D11_SAMPLER_DESC sd{};
	sd.Filter         = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.BorderColor[0] = { 0 };
	sd.BorderColor[1] = { 0 };
	sd.BorderColor[2] = { 0 };
	sd.BorderColor[3] = { 0 };
	sd.MinLOD         = 0;
	sd.MaxAnisotropy  = D3D11_MAX_MAXANISOTROPY;
	//sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sd.ComparisonFunc = D3D11_COMPARISON_ALWAYS;


	//Wrap sampler to default 
	HR(gDXDevice->CreateSamplerState(&sd, &SSWrap));
	sd.AddressU       = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressV       = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressW       = D3D11_TEXTURE_ADDRESS_CLAMP;
	//Clamp
	HR(gDXDevice->CreateSamplerState(&sd, &SSClamp));

	//Default Sampler Set;
	gDXContext->PSSetSamplers(0, 1, &SSWrap);
}

void DXRenderState::CreateBlendState()
{
	//Transparent
	D3D11_BLEND_DESC bd{};
	bd.AlphaToCoverageEnable                 = false;
	bd.RenderTarget[0].BlendEnable           = true;
	bd.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend	         = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HR(gDXDevice->CreateBlendState(&bd,&BSTransparent));

	bd.RenderTarget[0].SrcBlend       = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].SrcBlendAlpha  = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

	HR(gDXDevice->CreateBlendState(&bd, &BSBlend));

	bd.RenderTarget[0].BlendEnable = false;

	HR(gDXDevice->CreateBlendState(&bd, &BSBlendDisable));


	//default
	const float factor[4] = {0.f,0.f ,0.f ,0.f };
	gDXContext->OMSetBlendState(BSBlendDisable, factor, 0xffffffff);



}

void DXRenderState::CreateDepthStencilState()
{

	D3D11_DEPTH_STENCIL_DESC desc{};
	// Set up the description of the stencil state.
	desc.DepthEnable = true;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	desc.DepthFunc = D3D11_COMPARISON_LESS;
	
	desc.StencilEnable = true;
	desc.StencilReadMask = 0xFF;
	desc.StencilWriteMask = 0xFF;
	
	//desctions if pixel is front-facing.
	desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	
	//desctions if pixel is back-facing.
	desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	HR(gDXDevice->CreateDepthStencilState(&desc, &DSState));

	// Set the depth stencil state.
	gDXContext->OMSetDepthStencilState(DSState, 1);
}
