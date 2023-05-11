#include <PCH.h>
#include <Graphics/DX11/DXShader.h>
#include <Graphics/DX11/DX11Config.h>
#include <Graphics/Context.h>

void Compile(LPCSTR code, LPCSTR entry, LPCSTR version, ID3DBlob** blob)
{
	ID3DBlob* errorBlob = nullptr;
	DWORD flag = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef _DEBUG
	flag |= D3DCOMPILE_DEBUG;
	flag |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	HRESULT hr = D3DCompile(code,
		strlen(code),
		nullptr,
		nullptr,
		nullptr,
		entry,
		version,
		flag,
		0,
		blob,
		&errorBlob
	);

	if (FAILED(hr))
	{
		MessageBox(NULL,(LPCSTR)errorBlob->GetBufferPointer(),"Shader Compile Error",MB_OK);
	}

	SAFE_RELEASE(errorBlob);
}

DXVertexShader::DXVertexShader() : mVS(nullptr)
{
}

DXVertexShader::~DXVertexShader()
{
	SAFE_RELEASE(mVS);
}

void DXVertexShader::Create(LPCSTR code)
{
	//Compile -> Create Shader -> Create Input Layout
	ID3DBlob* blob = nullptr;
	Compile(code,VS_ENTRY,VS_VERSION,&blob);

	HR(gDXDevice->CreateVertexShader(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&mVS
	));
}

void DXVertexShader::BindPipeline()
{
	gDXContext->VSSetShader(mVS, 0, 0);
}

DXPixelShader::DXPixelShader() : mPS(nullptr)
{
}

DXPixelShader::~DXPixelShader()
{
	SAFE_RELEASE(mPS);
}

void DXPixelShader::Create(LPCSTR code)
{
	ID3DBlob* psBlob = nullptr; // binary byte code

	Compile(code, PS_ENTRY, PS_VERSION, &psBlob);

	HR(gDXDevice->CreatePixelShader(
		psBlob->GetBufferPointer(),
		psBlob->GetBufferSize(),
		nullptr,
		&mPS
	));

	SAFE_RELEASE(psBlob);
}

void DXPixelShader::BindPipeline()
{
	gDXContext->PSSetShader(mPS, 0, 0);
}
