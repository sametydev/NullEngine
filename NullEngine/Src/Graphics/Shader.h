#pragma once

class Shader
{
public:
	Shader() = default;
	virtual ~Shader() {}
	virtual void BindPipeline() = 0;

	virtual void Create(LPCSTR code) = 0;
};

#include <unordered_map>

//Todo: ECS Subsystem Shader Cache
class ShaderCache {
public:
	/*static Shader* Create(ShaderDesc* desc);*/
	static Shader* LoadVS(LPCSTR filename);
	static Shader* LoadPS(LPCSTR filename);

	static Shader* CreateVertexShaderFromCode(LPCSTR code);
	static Shader* CreatePixelShaderFromCode(LPCSTR code);


	static std::unordered_map<std::string, std::shared_ptr<Shader>> mCache;
	static std::vector<std::shared_ptr<Shader>> mShaders;
};
