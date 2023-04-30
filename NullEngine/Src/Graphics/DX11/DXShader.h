#pragma once
#include <Graphics/DX11/DXContext.h>

#define VS_ENTRY	"VS"
#define PS_ENTRY	"PS"
#define VS_VERSION	"vs_5_0"
#define PS_VERSION	"ps_5_0"

enum class ShaderType : uint
{
	Vertex,
	Pixel,
	Hull,
	Geometry,
	Compute
};

struct ShaderDesc {
	LPCSTR filename;
	LPCSTR code;
	ShaderType type;
};

class IShader
{
public:
	IShader() = default;
	virtual ~IShader(){}
	virtual void BindPipeline() = 0;
	void Compile(LPCSTR code,LPCSTR entry,LPCSTR version,ID3DBlob** blob);

};


class VertexShader : public IShader {
public:
	VertexShader();
	~VertexShader();

	//void Create(const ShaderDesc& desc);
	void Create(LPCSTR code);
	void BindPipeline() override;
	ID3D11VertexShader* mVS;
	ID3DBlob* byteBinary; //vs code binary
};

class PixelShader : public IShader {
public:
	PixelShader();
	~PixelShader();

	void BindPipeline() override;
	void Create(LPCSTR code);
	
	ID3D11PixelShader* mPS;
};


#include <unordered_map>

//Todo: ECS Subsystem Shader Cache
class ShaderCache {

	static IShader* Create(const ShaderDesc& desc);
	static std::unordered_map<std::string, std::shared_ptr<IShader>> mCache;
};