#include <PCH.h>
#include <Graphics/Shader.h>
#include <Graphics/Context.h>
#include <Graphics/DX11/DXShader.h>
#include <Graphics/GL46/GLShader.h>
#include <Core/FileSystem.h>

std::unordered_map<std::string, std::shared_ptr<Shader>> ShaderCache::mCache;
std::vector<std::shared_ptr<Shader>> ShaderCache::mShaders;

Shader* ShaderCache::LoadVSBuiltIn(LPCSTR filename)
{
	std::string data;
	std::string fullPath;
	switch (gContext->mApiType)
	{
	case GraphicAPI::DirectX11:
		fullPath = std::string("../Shader/HLSL/") + filename + std::string(".hlsl");
		break;
	case GraphicAPI::OpenGL46:
		fullPath = std::string("../Shader/GLSL/") + filename + std::string(".glsl");
		break;
	}
	data = FileSystem::ReadAllLinesFromFile(fullPath);

	
	return CreateVertexShaderFromCode(data.c_str());
}

Shader* ShaderCache::LoadPSBuiltIn(LPCSTR filename)
{
	std::string data;
	std::string fullPath;
	switch (gContext->mApiType)
	{
	case GraphicAPI::DirectX11:
		fullPath = std::string("../Shader/HLSL/") + filename + std::string(".hlsl");
		break;
	case GraphicAPI::OpenGL46:
		fullPath = std::string("../Shader/GLSL/") + filename + std::string(".glsl");
		break;
	}
	data = FileSystem::ReadAllLinesFromFile(fullPath);

	return CreatePixelShaderFromCode(data.c_str());
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

