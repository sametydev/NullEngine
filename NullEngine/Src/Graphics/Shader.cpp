#include <PCH.h>
#include <Graphics/Shader.h>
#include <Graphics/Context.h>
#include <Graphics/DX11/DXShader.h>
#include <Graphics/GL46/GLShader.h>
#include <Core/FileSystem.h>

std::unordered_map<std::string, std::shared_ptr<Shader>> ShaderCache::mInternalShader;
std::unordered_map<std::string, std::shared_ptr<Shader>> ShaderCache::mExternalShader;
std::string shader_dir_glsl = "../NullEngine/Shader/GLSL/";
std::string shader_dir_hlsl = "../NullEngine/Shader/HLSL/";

Shader* ShaderCache::CreateShader(const std::string& vs, const std::string& fs)
{
	std::string VS;
	std::string PS;

	std::shared_ptr<Shader> shader = nullptr;
	switch (gContext->mApiType)
	{
	case GraphicAPI::DirectX11:
	{
		VS += shader_dir_hlsl + vs + ".hlsl";
		if (!FileSystem::IsExistsFile(VS)) {
			LOG_ERROR("failed to find %s" ,VS.c_str());
		}
		PS += shader_dir_hlsl + fs + ".hlsl";
		if (!FileSystem::IsExistsFile(PS)) {
			LOG_ERROR("failed to find %s", PS.c_str());
		}

		auto found = mExternalShader.find(VS + PS);
		if (found != mExternalShader.end()) {
			return found->second.get();
		}

		shader = std::make_shared<DXShader>();
		shader->CreateFromFile(VS.c_str(), PS.c_str());
		mExternalShader.insert(std::make_pair(VS + PS, shader));

		break;
	}

	case GraphicAPI::OpenGL46:
	{

		return nullptr;
		VS += shader_dir_glsl + vs + ".glsl";
		if (!FileSystem::IsExistsFile(VS)) {
			LOG_ERROR("failed to find %s", VS.c_str());
		}
		PS += shader_dir_glsl + fs + ".glsl";
		if (!FileSystem::IsExistsFile(PS)) {
			LOG_ERROR("failed to find %s", PS.c_str());
		}

		auto found = mExternalShader.find(VS + PS);
		if (found != mExternalShader.end()) {
			return found->second.get();
		}

		//shader = std::make_shared<GLShader>();
		//shader->CreateFromFile(VS.c_str(), PS.c_str());
		//mExternalShader.insert(std::make_pair(VS + PS, shader));
		break;
	}
	}

	return shader.get();
}
