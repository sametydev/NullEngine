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
enum DrawType {
	LINE, QUAD, TRIANGLE, LINESTRIP
};
struct BatchCommandList {
	DrawType type;
	uint bufferOffset; //vertex curr pos
	uint drawCount;
};


#define DEFAULT_SPRITE_SIZE 1024
#define BATCH_MAX_VERTEX   1024*4
#define INDEX_PER_QUAD 6
#define VERTEX_PER_QUAD 4
#define VERTEX_PER_LINE 2

class BasicBatch
{
public:
	BasicBatch(ID3D11Device* device, ID3D11DeviceContext* context);
	void Init();
	void Begin();
	void DrawRect(int x, int y, int w,int h,
		const vec3f& color = vec3f(1.f));
	void DrawLine(const vec2f& p1, const vec2f& p2,
		const vec3f& color = vec3f(1.f));
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

	std::unique_ptr<vec4f[]> mQueuedVertices;
	std::vector<BatchCommandList> mCmdList;

	bool mIsBegin = false;
	uint mQueueIndex = 0;


	//graphic design?
	mat4x4 screenNDC;

	SortType mType = SortType::BackToFront;
};

