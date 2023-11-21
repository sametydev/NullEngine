#include <PCH.h>
#include <Graphics/dx11/dxshader.h>
#include <Graphics/Context.h>
#include <Graphics/DX11/DX11Config.h>

DXShader::DXShader()
	: mVShader(nullptr), mPShader(nullptr)
{
}

DXShader::~DXShader()
{
	SAFE_RELEASE(mVShader);
	SAFE_RELEASE(mPShader);
}

void DXShader::CreateFromFile(const char* vs, const char* fs)
{
	//ID3DBlob* vb = NULL;
	ID3DBlob* pb = NULL;

	CompileFromFile(vs, VS_ENTRY, VS_VER, &mBlob);

	HR(gDXDevice->CreateVertexShader(
		mBlob->GetBufferPointer(),
		mBlob->GetBufferSize(),
		NULL,
		&mVShader));

	CompileFromFile(fs, PS_ENTRY, PS_VER, &pb);

	HR(gDXDevice->CreatePixelShader(
		pb->GetBufferPointer(),
		pb->GetBufferSize(),
		NULL,
		&mPShader));
}

void DXShader::CreateFromCode(const char* vs, const char* fs)
{
	ID3DBlob* vb = NULL;
	ID3DBlob* pb = NULL;

	HRESULT res;

	CompileFromCode(vs, VS_ENTRY, VS_VER, &vb);

	HR(gDXDevice->CreateVertexShader(
		vb->GetBufferPointer(),
		vb->GetBufferSize(),
		NULL,
		&mVShader));

	CompileFromCode(fs, PS_ENTRY, PS_VER, &pb);

	HR(gDXDevice->CreatePixelShader(
		pb->GetBufferPointer(),
		pb->GetBufferSize(),
		NULL,
		&mPShader));
}

void DXShader::Bind()
{

	gDXContext->VSSetShader(mVShader, 0, 0);
	gDXContext->PSSetShader(mPShader, 0, 0);
}

void DXShader::UnBind()
{
}

void DXShader::CompileFromFile(const std::string& file, const char* entry, const char* ver, ID3DBlob** blob)
{
	ID3DBlob* errBlob = nullptr;
	HRESULT res;

	std::wstring widefile;
	widefile.assign(file.begin(), file.end());

	res = D3DCompileFromFile(widefile.c_str(), nullptr, nullptr,
		entry, ver, 0, 0, blob, &errBlob);

	if (FAILED(res))
	{
		if (!errBlob) {
			MessageBoxA(NULL, file.c_str(), "failed no find filename", MB_OK);
			return;
		}
		LOG_ERROR("Shader Error : %s \n%s",errBlob->GetBufferPointer(), file.c_str());
	}
}

void DXShader::CompileFromCode(const char* code, const char* entry, const char* ver, ID3DBlob** blob)
{
	ID3DBlob* errBlob = nullptr;

	HRESULT res = D3DCompile(code, strlen(code), nullptr, nullptr, nullptr, entry, ver, 0,
		0, blob, &errBlob);

	if (FAILED(res))
	{
		if (!errBlob) {
			MessageBoxA(NULL, code, "failed no find filename", MB_OK);
			return;
		}
		MessageBoxA(NULL, (char*)errBlob->GetBufferPointer(), code, MB_OK);
	}
}