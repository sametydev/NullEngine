#include <PCH.h>
#include <Graphics/DX11/DXShader.h>

void IShader::Compile(LPCSTR code, LPCSTR entry, LPCSTR version, ID3DBlob** blob)
{
}

VertexShader::VertexShader() : mVS(nullptr)
{
}

VertexShader::~VertexShader()
{
	SAFE_RELEASE(mVS);
}
