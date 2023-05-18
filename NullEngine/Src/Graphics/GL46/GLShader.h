#pragma once
#include <Graphics/Shader.h>

class GLShader : public Shader {
public:
	GLShader() : mShader(0) {};
	virtual ~GLShader();
	virtual void BindPipeline();
	uint mShader;
};

class GLVertexShader : public GLShader
{
public:
	GLVertexShader() {};
	virtual ~GLVertexShader() {};


	virtual void Create(LPCSTR code);
};

class GLPixelShader : public GLShader
{
public:
	GLPixelShader() {};
	virtual ~GLPixelShader() {};

	virtual void Create(LPCSTR code);
};

