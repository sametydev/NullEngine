#include <PCH.h>
#include <Graphics/DX11/DXTexture.h>

#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

comptr<ID3D11SamplerState> DXTexture::InternalSampler = nullptr;

DXTexture::DXTexture():mSRV(nullptr),mSlot(0)
{
	if (!InternalSampler)
	{
		CreateSampler();
	}
}

DXTexture::~DXTexture()
{
	SAFE_RELEASE(mSRV);
}

void DXTexture::Load(LPCSTR filename)
{
	if (!std::filesystem::exists(filename)) {
		LOG_ERROR("File is not exists %s",filename);
	}

	int w, h, comp;

	int bytePerPixel = 4;  //r g b a

	byte* buffers = stbi_load(filename, &h, &w, &comp, bytePerPixel);

	if (buffers == nullptr)
	{
		LOG_ERROR("Failed to load image file %s",filename);
	}

	width = w;
	height = h;

	ID3D11Texture2D* dump = nullptr;

	D3D11_TEXTURE2D_DESC td{};
	td.Width = width;
	td.Height = height;
	td.MipLevels = 0;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	td.CPUAccessFlags = 0;
	td.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	HR(gDXDevice->CreateTexture2D(&td, nullptr, &dump));

	//calc pitch
	uint rowPitches = (width * bytePerPixel);
	uint rowPitchBufferSize = rowPitches * (sizeof(byte));

	gDXContext->UpdateSubresource(dump, NULL, nullptr,
		buffers, rowPitchBufferSize, NULL
	);


	D3D11_SHADER_RESOURCE_VIEW_DESC srvd{};
	srvd.Format = td.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MostDetailedMip = 0;
	srvd.Texture2D.MipLevels = -1;

	HR(gDXDevice->CreateShaderResourceView(dump, &srvd, &mSRV));
	gDXContext->GenerateMips(mSRV);

	SAFE_RELEASE(dump);
	stbi_image_free(buffers);
}

void DXTexture::BindPipeline(uint slot)
{
	mSlot = slot;
	gDXContext->PSSetSamplers(0, 1, InternalSampler.GetAddressOf());
	gDXContext->PSSetShaderResources(mSlot, 1, &mSRV);
}

void DXTexture::UnBind()
{
	ID3D11ShaderResourceView* clearView = nullptr;
	gDXContext->PSSetShaderResources(mSlot, 1, &clearView);
}

void DXTexture::CreateSampler()
{
	D3D11_SAMPLER_DESC sd{};
	sd.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.BorderColor[0] = { 0 };
	sd.BorderColor[1] = { 0 };
	sd.BorderColor[2] = { 0 };
	sd.BorderColor[3] = { 0 };
	sd.MinLOD = 0;
	sd.MaxAnisotropy = D3D11_MAX_MAXANISOTROPY;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	
	gDXDevice->CreateSamplerState(&sd, InternalSampler.GetAddressOf());

}
