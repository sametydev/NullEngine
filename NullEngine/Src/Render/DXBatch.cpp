#include "PCH.h"
#include "DXBatch.h"
#include <Graphics/Shader.h>
#include <Graphics/Buffer.h>
#include <Graphics/DX11/DX11Config.h>
#include <Graphics/Context.h>
#include <Graphics/DX11/DXTexture.h>

DXBatch::DXBatch()
{
}

void DXBatch::Init()
{
	mShader = ShaderCache::CreateShader("FontVS", "FontPS");

	ConstantBufferDesc cbd{};
	cbd.cbSize = sizeof(mat4x4);
	cbd.pData = nullptr;

	mScreenCbo = BufferCache::CreateConstantBuffer(cbd);

	Viewport v{};
	
	gContext->GetViewport(&v);
	
	mat4x4 screenMatrix = mat4x4::NDCToScreen(v.w,v.h);

	mScreenCbo->SubData(&screenMatrix);

	Create_Font("../data/font/arial.ttf", 16);
	CreateBuffer(); //Create Font Buffer

	//make a instancing data

	mVertices = std::unique_ptr<FontInstanceVertex[]>(
		new FontInstanceVertex[MAX_FONT_TEXT]
	);
}

void DXBatch::Begin()
{
}

void DXBatch::Render(const char* text, int x, int y, const vec4f& color = vec4f(1.f))
{
}

void DXBatch::End()
{
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
	if (Instance == nullptr)
	{
		Instance = this;
	}
}
