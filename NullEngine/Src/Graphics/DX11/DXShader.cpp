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
	HR(gDXDevice->CreateVertexShader(
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		nullptr,
		&mVS
	));
}

void VertexShader::BindPipeline()
{
	gDXContext->VSSetShader(mVS, 0, 0);
}

PixelShader::PixelShader() : mPS(nullptr)
{
}

PixelShader::~PixelShader()
{
	SAFE_DELETE(mPS);
}

void PixelShader::Create(LPCSTR code)
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

void PixelShader::BindPipeline()
{
	gDXContext->PSSetShader(mPS, 0, 0);
}
std::unordered_map<std::string, std::shared_ptr<IShader>> ShaderCache::mCache;

IShader* ShaderCache::Create(const ShaderDesc& desc)
{
	//Checking
	std::string codeStr(desc.code);
	auto it = mCache.find(codeStr);
	if (it != mCache.end())
	{
		return it->second.get();
	}


	std::shared_ptr<IShader> shader = nullptr;

	switch (desc.type)
	{
	case ShaderType::Vertex: {
		auto vs = std::shared_ptr<VertexShader>();
		vs->Create(desc.code);
		shader = vs;
		}
		break;
	case ShaderType::Pixel: {
		auto ps = std::shared_ptr<PixelShader>();
		ps->Create(desc.code);
		shader = ps;
		}
		break;
	}

	mCache.insert(std::make_pair(codeStr,shader));

	return shader.get();
}
