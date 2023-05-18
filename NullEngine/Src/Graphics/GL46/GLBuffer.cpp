#include <PCH.h>
#include <Graphics/GL46/GLBuffer.h>
#include <Graphics/GL46/GLConfig.h>

//Vertex
GLVertexBuffer::GLVertexBuffer() :  vbo(0),vao(0)
{
}

GLVertexBuffer::~GLVertexBuffer()
{
	if (vao)	glDeleteVertexArrays(1, &vao);
	if (vbo)	glDeleteVertexArrays(1, &vbo);

}

void GLVertexBuffer::BindPipeline(uint slot)
{
	glBindVertexArray(vao);
}
void GLVertexBuffer::UnBind()
{
	glBindVertexArray(0);
}

void GLVertexBuffer::Create(const VertexBufferDesc& desc)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);	//make vertex buff

	glBindVertexArray(vao);	//bind array
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, desc.cbSize, desc.pData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPNS),
		(void*)offsetof(VertexPNS, VertexPNS::position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPNS),
		(void*)offsetof(VertexPNS, VertexPNS::normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPNS),
		(void*)offsetof(VertexPNS, VertexPNS::st));

	glBindVertexArray(0);
}


//Index
GLIndexBuffer::GLIndexBuffer() : ibo(0)
{
}

GLIndexBuffer::~GLIndexBuffer()
{
	if (ibo) glDeleteBuffers(1,&ibo);
	ibo = 0;
}

void GLIndexBuffer::Create(const IndexBufferDesc& desc)
{
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, desc.cbSize, desc.pData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLIndexBuffer::BindPipeline(uint offset)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void GLIndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}

//Uniform
GLUniformBuffer::GLUniformBuffer()
{
}

GLUniformBuffer::~GLUniformBuffer()
{
}

void GLUniformBuffer::Create(const ConstantBufferDesc& desc)
{
	mSize = desc.cbSize;
	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	//sub and map
	glBufferData(GL_UNIFORM_BUFFER, desc.cbSize, desc.pData, GL_STATIC_DRAW);

	//check later
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, mSize);
	glBindBuffer(GL_UNIFORM_BUFFER, NULL);
}

void GLUniformBuffer::BindPS(uint slot)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, slot, ubo);
}

void GLUniformBuffer::BindVS(uint slot)
{
	//TODO : DSA
	glBindBufferBase(GL_UNIFORM_BUFFER, slot, ubo);
}

void GLUniformBuffer::SubData(void* pData)
{
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glNamedBufferSubData(ubo, 0, mSize, pData);
	glBindBuffer(GL_UNIFORM_BUFFER, NULL);

}
