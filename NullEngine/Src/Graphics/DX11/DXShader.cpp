#include <PCH.h>
#include <Graphics/dx11/dxshader.h>
#include <Graphics/Context.h>
#include <Graphics/DX11/DX11Config.h>
#include  <array>
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
	CompileFromFile(vs, VS_ENTRY, VS_VER, &vertexShaderBlob);

	HR(gDXDevice->CreateVertexShader(
		vertexShaderBlob->GetBufferPointer(),
		vertexShaderBlob->GetBufferSize(),
		NULL,
		&mVShader));

	CompileFromFile(fs, PS_ENTRY, PS_VER, &pixelShaderBlob);

	HR(gDXDevice->CreatePixelShader(
		pixelShaderBlob->GetBufferPointer(),
		pixelShaderBlob->GetBufferSize(),
		NULL,
		&mPShader));
}

void DXShader::CreateFromCode(const char* vs, const char* fs)
{
	HRESULT res;

	CompileFromCode(vs, VS_ENTRY, VS_VER, &vertexShaderBlob);

	HR(gDXDevice->CreateVertexShader(
		vertexShaderBlob->GetBufferPointer(),
		vertexShaderBlob->GetBufferSize(),
		NULL,
		&mVShader));

	CompileFromCode(fs, PS_ENTRY, PS_VER, &pixelShaderBlob);

	HR(gDXDevice->CreatePixelShader(
		pixelShaderBlob->GetBufferPointer(),
		pixelShaderBlob->GetBufferSize(),
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

ID3DBlob& DXShader::GetVertexShaderBlob()
{
	return *vertexShaderBlob;
}

ID3DBlob& DXShader::GetPixelShaderBlob()
{
	return *pixelShaderBlob;
}

ID3D11InputLayout& DXShader::GetInputLayout()
{
	return *inputLayout;
}

void DXShader::SetInputLayoutPipeline()
{
	gDXContext->IASetInputLayout(inputLayout);
}

void DXShader::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* elements, uint32_t nElements)
{
	HR(gDXDevice->CreateInputLayout(elements, nElements,
		vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(),
		&inputLayout));

	SetInputLayoutPipeline();
}
