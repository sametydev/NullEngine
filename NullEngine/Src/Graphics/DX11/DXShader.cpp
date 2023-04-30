#include <PCH.h>
#include <Graphics/DX11/DXShader.h>

void IShader::Compile(LPCSTR code, LPCSTR entry, LPCSTR version, ID3DBlob** blob)
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

VertexShader::VertexShader() : mVS(nullptr)
{
}

VertexShader::~VertexShader()
{
	SAFE_RELEASE(mVS);
}

void VertexShader::Create(LPCSTR code)
{
	ID3DBlob* vsBlob = nullptr; // binary byte code

	Compile(code,VS_ENTRY,VS_VERSION,&vsBlob);

	byteBinary = vsBlob;
}
