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
}


//Index
GLIndexBuffer::GLIndexBuffer()
{
}

GLIndexBuffer::~GLIndexBuffer()
{
}
