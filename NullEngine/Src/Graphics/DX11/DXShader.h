#pragma once

#include <graphics/shader.h>


#define VS_ENTRY	"VS"
#define PS_ENTRY	"PS"

#define VS_VER		"vs_5_0"
#define PS_VER		"ps_5_0"

class DXShader : public Shader
{
public:
	DXShader();
	virtual~DXShader();

	void CreateFromFile(const char* vs, const char* fs) override;
	void CreateFromCode(const char* vs, const char* fs) override;

	void Bind() override;
	void UnBind() override;

	void CompileFromFile(const std::string& file, const char* entry, const char* ver, ID3DBlob** blob);
	void CompileFromCode(const char* code, const char* entry, const char* ver, ID3DBlob** blob);

	ID3DBlob& GetVertexShaderBlob() override;
	ID3DBlob& GetPixelShaderBlob() override;
	ID3D11InputLayout& GetInputLayout() override;

	void SetInputLayoutPipeline() override;

	void CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* elements,
		uint32_t nElements) override;

	ID3D11VertexShader* mVShader;
	ID3D11PixelShader* mPShader;

private:
	ID3DBlob* pixelShaderBlob = nullptr;
	ID3DBlob* vertexShaderBlob = nullptr;

	ID3D11InputLayout* inputLayout = nullptr;
};