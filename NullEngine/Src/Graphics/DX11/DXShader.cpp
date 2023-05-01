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
	SAFE_RELEASE(mBinary);
}

void VertexShader::Create(LPCSTR code)
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

void VertexShader::BindPipeline()
{
	if (!mLayout)
	{
		LOG_ERROR("Failed to bind Input Layout");
	}
	gDXContext->IASetInputLayout(mLayout);
	gDXContext->VSSetShader(mVS, 0, 0);
}

void VertexShader::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* element, uint numOfElements)
{
	HR(gDXDevice->CreateInputLayout(element, numOfElements,
		mBinary->GetBufferPointer(), mBinary->GetBufferSize(), &mLayout));
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
std::vector<std::shared_ptr<IShader>> ShaderCache::mShaders;

IShader* ShaderCache::Create(LPCSTR name,ShaderDesc* desc)
{
	//Checking
	//std::string nameStr = name;
	//auto it = mCache.find(nameStr);
	//if (it != mCache.end())
	//{
	//	return it->second.get();
	//}


	std::shared_ptr<IShader> shader = nullptr;

	switch (desc->type)
	{
	case ShaderType::Vertex: {
		auto vs = std::make_shared<VertexShader>();
		vs->Create(desc->code);
		vs->CreateInputLayout(desc->element,desc->numberOfElements);
		mShaders.emplace_back(vs);
		}
		break;
	case ShaderType::Pixel: {
		auto ps = std::make_shared<PixelShader>();
		ps->Create(desc->code);
		mShaders.emplace_back(ps);
		}
		break;

	default:
		LOG_ERROR("Doesnt match shader type");
		break;
	}

	/*mCache.insert(std::make_pair(nameStr,shader));*/
	//mShaders.emplace_back(shader);

	return nullptr;
}
