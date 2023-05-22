#pragma once

#include <Graphics/Shader.h>

class GLShader : public Shader
{
public:
	GLShader();
	virtual~GLShader();

	void CreateFromFile(const char* vs, const char* fs) override;
	void CreateFromCode(const char* vs, const char* fs) override;

	void Bind() override;
	void UnBind() override;
	uint mId;
protected:
	std::string FileToCode(const char* file);
	uint		CompileCode(const char* code, uint type);

};
