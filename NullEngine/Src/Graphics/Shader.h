#pragma once
enum class ShaderType : uint
{
	Vertex,
	Pixel,
	Hull,
	Geometry,
	Compute
};

struct ShaderDesc {
	LPCSTR filename;
	LPCSTR code;
	ShaderType type;

	//Optional
	D3D11_INPUT_ELEMENT_DESC* element;
	uint					  numberOfElements;
};

class Shader
{
public:
	Shader() = default;
	virtual ~Shader() {}
	virtual void BindPipeline() = 0;
};

#include <unordered_map>

//Todo: ECS Subsystem Shader Cache
class ShaderCache {
public:
	/*static Shader* Create(ShaderDesc* desc);*/
	static Shader* CreateVertexShaderFromCode(LPCSTR code);
	static Shader* CreatePixelShader(LPCSTR code);
	static std::unordered_map<std::string, std::shared_ptr<Shader>> mCache;
	static std::vector<std::shared_ptr<Shader>> mShaders;
};
