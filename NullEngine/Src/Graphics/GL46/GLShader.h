#pragma once
#include <Graphics/Shader.h>
class GLVertexShader : public Shader
{
public:
	GLVertexShader();
	virtual ~GLVertexShader();



	virtual void BindPipeline();
	virtual void Create(LPCSTR code);

	
	uint mShader;
};

class GLPixelShader : public Shader
{
public:
	GLPixelShader();
	virtual ~GLPixelShader();



	virtual void BindPipeline();
	virtual void Create(LPCSTR code);

	uint mShader;
};

