#pragma once
#include <Math/vec4f.h>
#include <Graphics/DX11/DX11Config.h>
#include <Graphics/Context.h>

#include <wrl.h>
#include <vector>

using namespace Microsoft::WRL;

typedef ComPtr<ID3D11VertexShader> VertexShaderPtr;
typedef ComPtr<ID3D11PixelShader> PixelShaderPtr;
//typedef ComPtr<ID3D11Buffer> BufferPtr;

enum class SortType : uint {
	BackToFront,
	FrontToBack,
	TextureIndex
};

/*
	LT(0) ----- RT(1)
	|				|
	|				|
	LB(2) ----- RB(3)
*/

struct SpriteRect{
	VertexPS LT, RT, LB, RB;
	vec4f color;
};


#define DEFAULT_SPRITE_SIZE 1024
#define INDEX_PER_QUAD 6
#define VERTEX_PER_QUAD 4

class BasicBatch
{
public:
	BasicBatch(ID3D11Device* device, ID3D11DeviceContext* context);
	void Init();
	void Begin();
	void Render(int x, int y, int w,int h,
		const vec4f& color = vec4f(1.f));
	void End();

	static BasicBatch* Instance;

private:
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mContext;

	Shader* mShader;
	Viewport mVp;

	ComPtr<ID3D11Buffer> mConstantBuffer;
	ComPtr<ID3D11Buffer> mColorBuffer;


	ComPtr<ID3D11Buffer> mVertexBuffer;
	ComPtr<ID3D11Buffer> mIndexBuffer;

	void CreateShader();
	void CreateBuffer();

	std::vector<SpriteRect> mSprite;
	bool mIsBegin = false;
	uint mQueueIndex = 0;

	mat4x4 screenNDC;

	SortType mType = SortType::BackToFront;
};

