#include <PCH.h>
#include <Graphics/Shader.h>
#include <Graphics/DX11/DXShader.h>


std::unordered_map<std::string, std::shared_ptr<Shader>> ShaderCache::mCache;
std::vector<std::shared_ptr<Shader>> ShaderCache::mShaders;

Shader* ShaderCache::CreateVertexShaderFromCode(LPCSTR code)
{
	auto it = mCache.find(code);
	if (it != mCache.end())
	{
		return it->second.get();
	}

	std::shared_ptr<Shader> shader = std::make_shared<DXVertexShader>();
	shader->Create(code);
	mCache.insert(std::make_pair(code, shader));

	return shader.get();
}

Shader* ShaderCache::CreatePixelShaderFromCode(LPCSTR code)
{
	auto it = mCache.find(code);
	if (it != mCache.end())
	{
		return it->second.get();
	}

	std::shared_ptr<Shader> shader = std::make_shared<DXPixelShader>();
	shader->Create(code);

	mCache.insert(std::make_pair(code, shader));

	return shader.get();
}

