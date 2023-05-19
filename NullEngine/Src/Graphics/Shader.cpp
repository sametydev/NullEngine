#include <PCH.h>
#include <Graphics/Shader.h>
#include <Graphics/Context.h>
#include <Graphics/DX11/DXShader.h>
#include <Graphics/GL46/GLShader.h>


std::unordered_map<std::string, std::shared_ptr<Shader>> ShaderCache::mCache;
std::vector<std::shared_ptr<Shader>> ShaderCache::mShaders;

Shader* ShaderCache::LoadVS(LPCSTR filename)
{

	return nullptr;
}

Shader* ShaderCache::LoadPS(LPCSTR filename)
{

	return nullptr;
}

Shader* ShaderCache::CreateVertexShaderFromCode(LPCSTR code)
{
	auto it = mCache.find(code);
	if (it != mCache.end())
	{
		return it->second.get();
	}

	std::shared_ptr<Shader> shader = nullptr;

	auto type = gContext->mApiType;

	switch (type)
	{
	case GraphicAPI::DirectX11:
		shader = std::make_shared<DXVertexShader>();
		break;
	case GraphicAPI::OpenGL46:
		shader = std::make_shared<GLVertexShader>();
		break;
	}

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

	std::shared_ptr<Shader> shader = nullptr;

	auto type = gContext->mApiType;
	switch (type)
	{
	case GraphicAPI::DirectX11:
		shader = std::make_shared<DXPixelShader>();
		break;
	case GraphicAPI::OpenGL46:
		shader = std::make_shared<GLPixelShader>();
		break;
	}
	shader->Create(code);

	mCache.insert(std::make_pair(code, shader));

	return shader.get();
}

