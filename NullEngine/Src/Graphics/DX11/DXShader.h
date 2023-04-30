#pragma once
#include <Graphics/DX11/DX11Config.h>

enum class ShaderType : uint
{
	Vertex,
	Pixel,
	Hull,
	Geometry,
	Compute
};
class IShader
{
public:
	IShader() = default;
	virtual ~IShader(){}

	void Compile(LPCSTR code,LPCSTR entry,LPCSTR version,ID3DBlob** blob);

};


class VertexShader : public IShader {
public:
	VertexShader();
	~VertexShader();

	ID3D11VertexShader* mVS;
};

