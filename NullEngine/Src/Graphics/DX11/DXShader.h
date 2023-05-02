#pragma once
#include <Graphics/DX11/DXContext.h>
#include <vector>

#define VS_ENTRY	"VS"
#define PS_ENTRY	"PS"
#define VS_VERSION	"vs_5_0"
#define PS_VERSION	"ps_5_0"

struct Vertex {
	vec3f pos;
};

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

	//Optional
	D3D11_INPUT_ELEMENT_DESC* element;
	uint					  numberOfElements;
};

class IShader
{
public:
	IShader() = default;
	virtual ~IShader(){}
	virtual void BindPipeline() = 0;
	static void Compile(LPCSTR code,LPCSTR entry,LPCSTR version,ID3DBlob** blob);

};


class VertexShader : public IShader {
public:
	VertexShader();
	~VertexShader();

	//void Create(const ShaderDesc& desc);
	void Create(LPCSTR code);
	void BindPipeline() override;

	void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* element,uint numOfElements);

	ID3D11VertexShader* mVS;
	ID3DBlob* mBinary; //vs code binary

	//input for temporary at the moment;
	ID3D11InputLayout* mLayout = nullptr;
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
public:
	static IShader* Create(LPCSTR name,ShaderDesc* desc);
	static std::unordered_map<std::string, std::shared_ptr<IShader>> mCache;
	static std::vector<std::shared_ptr<IShader>> mShaders;
};