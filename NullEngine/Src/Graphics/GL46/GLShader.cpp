#include <PCH.h>
#include <Graphics/GL46/GLShader.h>
#include <Graphics/GL46/GLConfig.h>
#include <fstream>

GLShader::GLShader()
	: mId(0)
{
}

GLShader::~GLShader()
{
	if (mId) glDeleteProgram(mId);
	mIsCompiled = false;
}

void GLShader::CreateFromFile(const char* vs, const char* fs)
{
	auto vsCode = this->FileToCode(vs);
	auto fsCode = this->FileToCode(fs);

	this->CreateFromCode(vsCode.c_str(), fsCode.c_str());
}

void GLShader::CreateFromCode(const char* vs, const char* fs)
{
	auto vertShader = this->CompileCode(vs, GL_VERTEX_SHADER);
	auto fragShader = this->CompileCode(fs, GL_FRAGMENT_SHADER);

	mId = glCreateProgram();
	glAttachShader(mId, vertShader);
	glAttachShader(mId, fragShader);
	glLinkProgram(mId);

	GLint success;
	GLchar errLog[512];

	glGetProgramiv(mId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(mId, 512, nullptr, errLog);
		LOG_ERROR(errLog);
	}
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	mIsCompiled = true;
}

void GLShader::Bind()
{
	glUseProgram(mId);
}

void GLShader::UnBind()
{
	glUseProgram(NULL);
}

std::string GLShader::FileToCode(const char* file)
{
	std::string bits;
	std::ifstream fs(file, std::ios::in);

	if (!fs.is_open())
	{
		LOG_ERROR("failed to find file");
	}

	std::string line = "";
	while (!fs.eof())
	{
		std::getline(fs, line);
		bits.append(line + "\n");
	}

	fs.close();
	return bits;
}

uint GLShader::CompileCode(const char* code, uint type)
{
	GLint success;
	GLchar errInfo[512];

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, errInfo);
		MessageBoxA(NULL, errInfo, "shader compile error", MB_OK);
	}
	return shader;
}
