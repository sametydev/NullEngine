#pragma once

class Shader
{
public:
	Shader() : mIsCompiled(false) {}
	virtual~Shader() {}

	virtual void CreateFromFile(const char* vs, const char* fs) = 0;
	virtual void CreateFromCode(const char* vs, const char* fs) = 0;

	virtual void Bind() = 0;
	virtual void UnBind() = 0;
protected:
	bool mIsCompiled;
};

#include <unordered_map>

class ShaderCache
{
public:
	//Internal


	//External
	static Shader* CreateShader(const std::string& vs, const std::string& fs);

	static std::unordered_map<std::string, std::shared_ptr<Shader>> mInternalShader;
	static std::unordered_map<std::string, std::shared_ptr<Shader>> mExternalShader;
};
