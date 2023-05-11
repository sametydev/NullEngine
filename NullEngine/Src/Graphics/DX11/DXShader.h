#pragma once
#include <Graphics/Shader.h>
#include <vector>

#define VS_ENTRY	"VS"
#define PS_ENTRY	"PS"
#define VS_VERSION	"vs_5_0"
#define PS_VERSION	"ps_5_0"


class DXVertexShader : public Shader {
public:
	DXVertexShader();
	~DXVertexShader();

	//void Create(const ShaderDesc& desc);
	void Create(LPCSTR code) override;
	void BindPipeline() override;

	//void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* element,uint numOfElements);

	ID3D11VertexShader* mVS;
};

class DXPixelShader : public Shader {
public:
	DXPixelShader();
	~DXPixelShader();

	void BindPipeline() override;
	void Create(LPCSTR code) override;
	
	ID3D11PixelShader* mPS;
};


