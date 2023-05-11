#include <PCH.h>
#include <Graphics/DX11/DXShader.h>
#include <Graphics/DX11/DX11Config.h>
#include <Graphics/Context.h>

void Compile(LPCSTR code, LPCSTR entry, LPCSTR version, ID3DBlob** blob)
{
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompile(code,
		strlen(code),
		nullptr,
		nullptr,
		nullptr,
		entry,
		version,
		0,0,
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
	SAFE_RELEASE(mBinary);
}

void DXVertexShader::Create(LPCSTR code)
{
	//Compile -> Create Shader -> Create Input Layout
	Compile(code,VS_ENTRY,VS_VERSION,&mBinary);

	HR(gDXDevice->CreateVertexShader(
		mBinary->GetBufferPointer(),
		mBinary->GetBufferSize(),
		nullptr,
		&mVS
	));
}

void DXVertexShader::BindPipeline()
{
	if (!mLayout)
	{
		LOG_ERROR("Failed to bind Input Layout");
	}
	gDXContext->IASetInputLayout(mLayout);
	gDXContext->VSSetShader(mVS, 0, 0);
}

void DXVertexShader::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* element, uint numOfElements)
{
	HR(gDXDevice->CreateInputLayout(element, numOfElements,
		mBinary->GetBufferPointer(), mBinary->GetBufferSize(), &mLayout));
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
