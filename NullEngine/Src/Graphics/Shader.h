#pragma once
#include <Graphics/DX11/DX11Config.h>
#include <Graphics/Vertex.h>
class Shader
{
public:
	Shader() : mIsCompiled(false) {}
	virtual~Shader() {}

	virtual void CreateFromFile(const char* vs, const char* fs) = 0;
	virtual void CreateFromCode(const char* vs, const char* fs) = 0;

	virtual void Bind() = 0;
	virtual void UnBind() = 0;
	virtual void CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* elements,
		uint32_t nElements) = 0;
	virtual void SetInputLayoutPipeline() = 0;
	virtual ID3DBlob& GetVertexShaderBlob() = 0;
	virtual ID3DBlob& GetPixelShaderBlob() = 0;

	virtual ID3D11InputLayout& GetInputLayout() = 0;
protected:
	bool mIsCompiled;
};

#include <unordered_map>

class ShaderCache
{
public:
	//Internal


	//External
	[[nodiscard]]static Shader* CreateShader(const std::string& vs, const std::string& fs);

	static std::unordered_map<std::string, std::shared_ptr<Shader>> mInternalShader;
	static std::unordered_map<std::string, std::shared_ptr<Shader>> mExternalShader;
};
