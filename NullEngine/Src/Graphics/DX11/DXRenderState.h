#pragma once
struct DXRenderState {
	DXRenderState();
	~DXRenderState();

	void Create();

	//State
	//ID3D11RasterizerState* RSState[2]{};
	ID3D11RasterizerState* RSCullBack         = nullptr;
	ID3D11RasterizerState* RSCullFront        = nullptr;
	ID3D11RasterizerState* RSCullFrontAndBack = nullptr;
	ID3D11RasterizerState* RSWireFrame        = nullptr;

	//Sampler
	ID3D11SamplerState* SSWrap                = nullptr;
	ID3D11SamplerState* SSClamp               = nullptr;

	ID3D11BlendState* BSTransparent           = nullptr;
	ID3D11BlendState* BSBlendDisable          = nullptr;
	ID3D11BlendState* BSBlend			  = nullptr;

	void CreateRSState();
	void CreateSamplerState();
	void CreateBlendState();
};
