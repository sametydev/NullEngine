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


GLShader::~GLShader()
{
	if(mShader)glDeleteProgram(mShader);
}

void GLShader::BindPipeline()
{
	glUseProgram(mShader);
}

//Vertex Shader
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

//Pixel Shader
void GLPixelShader::Create(LPCSTR code)
{
	auto PS = Compile(code, GL_FRAGMENT_SHADER);

	mShader = glCreateProgram();
	glAttachShader(mShader, PS);
	glLinkProgram(mShader);

	GLint sucess = 0;
	GLchar err[256]{};

	glGetProgramiv(mShader, GL_LINK_STATUS, &sucess);
	if (!sucess) {
		glGetProgramInfoLog(mShader, 256, nullptr, err);
		LOG_ERROR("GL shader link error %s\n", err);
	}
	glDeleteShader(PS);
}
