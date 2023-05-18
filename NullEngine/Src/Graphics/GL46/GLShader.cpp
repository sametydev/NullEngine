#include <PCH.h>
#include <Graphics/GL46/GLShader.h>
#include <Graphics/GL46/GLConfig.h>


uint Compile(LPCSTR code, uint type) {

	GLint sucess = 0;
	GLchar error[256];

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &sucess);

	if (!sucess)
	{
		glGetShaderInfoLog(shader, 256, nullptr, error);
		LOG_ERROR("[GL] Shader Error \n%s\n", error);
	}
	return shader;
}

GLVertexShader::GLVertexShader() : mShader(0)
{
}

GLVertexShader::~GLVertexShader()
{
	if (mShader) glDeleteProgram(mShader);
}

void GLVertexShader::BindPipeline()
{
	glUseProgram(mShader);
}

void GLVertexShader::Create(LPCSTR code)
{

	auto VS = Compile(code, GL_VERTEX_SHADER);

	mShader = glCreateProgram();
	glAttachShader(mShader, VS);
	glLinkProgram(mShader);

	GLint sucess = 0;
	GLchar err[256]{};

	glGetProgramiv(mShader, GL_LINK_STATUS, &sucess);
	if (!sucess) {
		glGetProgramInfoLog(mShader, 256, nullptr, err);
		LOG_ERROR("GL shader link error %s\n", err);
	}
	glDeleteShader(VS);
}

