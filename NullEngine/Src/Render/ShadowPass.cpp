#include <PCH.h>
#include <Render/ShadowPass.h>
#include <Graphics/Context.h>
#include <Graphics/DX11/DX11Config.h>
#include <Graphics/DX11/DXTexture.h>
#include <Graphics/Shader.h>
#include <Component/Object.h>

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

	std::shared_ptr<DXTexture> depthPtr = std::make_shared<DXTexture>();
	depthPtr->width = width;
	depthPtr->height = height;
	

	HR(gDXDevice->CreateShaderResourceView(tex2d, &srd, &depthPtr->mSRV));
	mTexture = depthPtr;


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

	//Creating Matrix;
	lightPosition = { -5.f , 8.f, -5.f };
	view = CreateLightView(lightPosition, vec3f(0.f));
	projection = CreateLightProjection(1.f, 100.f);

	//Creating Shader;
	mShader = ShaderCache::CreateShader("DepthVS","DepthPS");

	mViewport = { 0.f,0.f,(float)width,(float)height,0.f,1.f };
}

Texture* ShadowPass::GetDepthMap() const
{
	return mTexture.get();
}

void ShadowPass::Bind()
{
	// Get Prev Viewport
	gContext->GetViewport(&prevViewport);
	
	// Set our Viewport
	gContext->SetViewport(&mViewport);

	// Get Prev Rtv and Dsv
	gDXContext->OMGetRenderTargets(1, &prevRtv, &prevDsv);

	// Set RenderTarget
	gContext->GetDXContext()->OMSetRenderTargets(1, &mRtv, mDsv);

	// Clear Render Buffer
	const float rgba[4] = { 0.0f,0.0f,0.0f,0.0f };
	gDXContext->ClearRenderTargetView(mRtv, rgba);
	gDXContext->ClearDepthStencilView(mDsv, D3D11_CLEAR_DEPTH, 1.0f, 0);

	mShader->Bind();
}

void ShadowPass::UnBind()
{
	// Restore Prev Viewport
	gContext->SetViewport(&prevViewport);
	// Restore Prev Render Target
	gDXContext->OMSetRenderTargets(1, &prevRtv, prevDsv);

	mShader->UnBind();
}

void ShadowPass::Render(Renderable** Objs, uint nObjs)
{
	for (int i = 0; i < nObjs; i++)
	{
		Objs[i]->Render();
	}
}

mat4x4 ShadowPass::CreateLightView(const vec3f& pos, const vec3f& center)
{
	return mat4x4::LookAt(pos, center, vec3f(0.f, 1.f, 0.f));
}

mat4x4 ShadowPass::CreateLightProjection(float znear, float zfar)
{
	float fov = M_PI / 2.f * DEGREES;
	float aspect = 1.0f;
	return mat4x4::perspectiveLH(fov,aspect,znear,zfar);
}

