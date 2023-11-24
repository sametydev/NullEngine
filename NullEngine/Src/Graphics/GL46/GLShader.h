#pragma once

#include <Graphics/Shader.h>

class GLShader
{
public:
	GLShader();
	virtual~GLShader();

	void CreateFromFile(const char* vs, const char* fs);
	void CreateFromCode(const char* vs, const char* fs);

	void Bind();
	void UnBind();
	uint mId;
protected:
	std::string FileToCode(const char* file);
	uint		CompileCode(const char* code, uint type);

};
