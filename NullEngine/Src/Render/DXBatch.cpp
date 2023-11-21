#include "PCH.h"
#include "DXBatch.h"
#include <Graphics/Shader.h>
#include <Graphics/Buffer.h>
#include <Graphics/DX11/DX11Config.h>
#include <Graphics/DX11/DXContext.h>
#include <Graphics/Context.h>
#include <Graphics/DX11/DXShader.h>

#include <Graphics/DX11/DXTexture.h>
DXBatch* DXBatch::Instance = nullptr;
DXBatch::DXBatch()
{
	if (Instance == nullptr)
	{
		Instance = this;
	}
}

void DXBatch::Init()
{
	mShader = ShaderCache::CreateShader("FontVS", "FontPS");
	Viewport v{};

	auto blob = static_cast<DXShader*>(mShader)->mBlob;

	gContext->GetViewport(&v);

	mat4x4 screenMatrix = mat4x4::NDCToScreen(v.w, v.h);


	ConstantBufferDesc cbd{};
	cbd.cbSize = sizeof(mat4x4);
	cbd.pData = &screenMatrix;

	mScreenCbo = BufferCache::CreateConstantBuffer(cbd);



	mScreenCbo->SubData(&screenMatrix);


	std::vector<D3D11_INPUT_ELEMENT_DESC> inputs = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_INSTANCE_DATA},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_INSTANCE_DATA},
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_INSTANCE_DATA}
	};

	HR(gDXDevice->CreateInputLayout(inputs.data(), inputs.size(),
		blob->GetBufferPointer(),blob->GetBufferSize(),
		&inputLayout));



	Create_Font("../data/font/arial.ttf", 16);
	CreateBuffer(); //Create Font Buffer

	//make a instancing data

	mVertices = std::unique_ptr<FontInstanceVertex[]>(
		new FontInstanceVertex[MAX_FONT_TEXT]
	);
}

void DXBatch::Begin()
{
	mIsBegin = true;
	mCurVtxIndex = 0;
	pCurrentVertex = mVertices.get();
}

void DXBatch::Render(const char* text, int x, int y, const vec4f& color)
{
	if (!mIsBegin)return;

	const unsigned char* ch = nullptr;
	for (ch=(const unsigned char*)text; *ch; ++ch)
	{
		if (mCurVtxIndex >= FONT_MAX_CHAR)
		{
			break;
		}

		auto& font = fonts[*ch];

		float posx = x + font.bl;
		float posy = y - (font.h - font.bt) + m_height;

		float w = font.w;
		float h = font.h;

		FontInstanceVertex fontVtx;
		fontVtx.pswh = { posx,posy,w,h };
		fontVtx.uv = { font.uvx1,font.uvy1,font.uvx2,font.uvy2 };
		fontVtx.color = color;


		*pCurrentVertex++ = fontVtx;
		x += font.ax;
	}
}

void DXBatch::End()
{ 
	if (!mIsBegin || mCurVtxIndex == 0) return;

	D3D11_MAPPED_SUBRESOURCE mapped{};
	gDXContext->Map(mVbo, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, mVertices.get(), sizeof(FontInstanceVertex)*mCurVtxIndex);

	gDXContext->Unmap(mVbo,0);

	mShader->Bind();
	mScreenCbo->BindVS(1);

	uint stride = sizeof(FontInstanceVertex);
	uint offset = 0;

	gDXContext->IASetInputLayout(inputLayout);
	
	gDXContext->IASetVertexBuffers(0, 1, &mVbo, &stride, &offset);

	gDXContext->PSSetShaderResources(0, 1, &mTexture);

	auto sampler = static_cast<DXContext*>(gContext)->mStates.SSWrap;

	gDXContext->PSSetSamplers(0, 1, &sampler);

	gDXContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	gContext->SetBlendState(BlendState::Transparent);
	gDXContext->DrawInstanced(6, mCurVtxIndex, 0, 0);
	gContext->SetBlendState(BlendState::Disable);

}

void DXBatch::Create_Font(const char* filename, uint size)
{

	FT_Library lib;
	FT_Face face;
	if (FT_Init_FreeType(&lib))
	{
		LOG_ERROR("FAILED TO LOAD FT LIBRARY");
	}
	if (FT_New_Face(lib, filename, 0, &face))
	{
		LOG_ERROR("FAILED TO LOAD FONT FACE");
	}

	FT_Set_Pixel_Sizes(face, 0, size);

	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
	{
		LOG_ERROR("FAILED TO LOAD FT Character");
	}
	FT_GlyphSlot glyph = face->glyph;

	uint width = 0;
	uint height = 0;

	//calc total with height
	for (int c = FONT_MIN_CHAR; c < FONT_MAX_CHAR; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			continue;
		}
		width += glyph->bitmap.width;
		height = std::max(height, glyph->bitmap.rows);

	}

	byte* buffer = new byte[width * height];

	memset(buffer, byte(0), sizeof(byte) * width * height);
	memset(fonts, byte(0), sizeof(fonts));

	int offsetx = 0;
	int offsety = 0;

	for (int c = FONT_MIN_CHAR; c < FONT_MAX_CHAR; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			continue;
		}

		FT_Bitmap& bitmap = glyph->bitmap;

		for (int y = 0; y < bitmap.rows; y++)
		{
			for (int x = 0; x < bitmap.width; x++)
			{
				buffer[(y * width) + (offsetx + x)] = bitmap.buffer[y * bitmap.width + x];
			}
		}
		if (c == 36)
		{
			int a = 0;
		}
		fonts[c].ax = (float)(glyph->advance.x >> 6);
		fonts[c].ay = (float)(glyph->advance.y >> 6);

		fonts[c].w = (float)glyph->bitmap.width;
		fonts[c].h = (float)glyph->bitmap.rows;

		fonts[c].bl = (float)glyph->bitmap_left;
		fonts[c].bt = (float)glyph->bitmap_top;

		fonts[c].uvx1 = (float)offsetx / (float)width;
		fonts[c].uvy1 = (float)offsety / (float)height;

		fonts[c].uvx2 = (float)(offsetx + glyph->bitmap.width) / (float)width;
		fonts[c].uvy2 = (float)(offsety + glyph->bitmap.rows) / (float)height;

		offsetx += glyph->bitmap.width;
	}

	m_width = width;
	m_height = height;
	D3D11_TEXTURE2D_DESC t2d{};
	t2d.CPUAccessFlags = 0;
	t2d.Width = width;
	t2d.Height = height;
	t2d.Format = DXGI_FORMAT_R8_UNORM;
	t2d.MipLevels = 1;
	t2d.ArraySize = 1;
	t2d.SampleDesc.Count = 1;
	t2d.SampleDesc.Quality = 0;
	t2d.MiscFlags = 0;
	t2d.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	ID3D11Texture2D* dump = nullptr;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = buffer;
	sd.SysMemPitch = width;
	sd.SysMemSlicePitch = width * height;

	HR(gDXDevice->CreateTexture2D(&t2d, &sd, &dump));

	D3D11_SHADER_RESOURCE_VIEW_DESC srvd{};
	srvd.Format = t2d.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MipLevels = 1;
	srvd.Texture2D.MostDetailedMip = 0;

	HR(gDXDevice->CreateShaderResourceView(dump, &srvd, &mTexture));

	SAFE_RELEASE(dump);

	FT_Done_Face(face);
	FT_Done_FreeType(lib);

	delete[] buffer;
	
}

void DXBatch::CreateBuffer()
{
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(FontInstanceVertex) * FONT_MAX_CHAR;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;

	HR(gDXDevice->CreateBuffer(&bd, nullptr, &mVbo));
}


Batch::Batch()
{

}

Batch::~Batch()
{
}
