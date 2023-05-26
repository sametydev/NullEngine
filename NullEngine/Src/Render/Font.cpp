#include <PCH.h>
#include <Render/Font.h>
#include <freetype/freetype.h>
#include <Graphics/DX11/DX11Config.h>
#include <Graphics/Context.h>
#include <Graphics/DX11/DXTexture.h>

#include <Graphics/Texture.h>

Font::Font()
{
}

void Font::Create(LPCSTR filename,uint size)
{
	FT_Library lib;
	FT_Face face;
	if (FT_Init_FreeType(&lib))
	{
		LOG_ERROR("FAILED TO LOAD FT LIBRARY");
	}
	if (FT_New_Face(lib,filename,0,&face))
	{
		LOG_ERROR("FAILED TO LOAD FONT FACE");
	}

	FT_Set_Pixel_Sizes(face,0,size);

	if (FT_Load_Char(face,'X',FT_LOAD_RENDER))
	{
		LOG_ERROR("FAILED TO LOAD FT Character");
	}
	FT_GlyphSlot glyph = face->glyph;

	uint width = 0;
	uint height = 0;

	//calc total with height
	for (int c = FONT_MIN_CHAR; c < FONT_MAX_CHAR; c++)
	{
		if (FT_Load_Char(face,c,FT_LOAD_RENDER))
		{
			continue;
		}
		width += glyph->bitmap.width;
		height = std::max(height,glyph->bitmap.rows);

	}

	byte* buffer = new byte[width*height];

	memset(buffer, byte(0), sizeof(byte) * width * height);
	memset(mFont, byte(0), sizeof(mFont));

	int offsetx = 0;
	int offsety = 0;

	for (int c = FONT_MIN_CHAR; c < FONT_MAX_CHAR; c++)
	{
		if (FT_Load_Char(face,c,FT_LOAD_RENDER))
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
		mFont[c].ax = (float)(glyph->advance.x >> 6);
		mFont[c].ay = (float)(glyph->advance.y >> 6);

		mFont[c].w = (float)glyph->bitmap.width;
		mFont[c].h = (float)glyph->bitmap.rows;

		mFont[c].bl = (float)glyph->bitmap_left;
		mFont[c].bt = (float)glyph->bitmap_top;

		mFont[c].uvx1 = (float)offsetx / (float)width;
		mFont[c].uvy1 = (float)offsety / (float)height;

		mFont[c].uvx2 = (float)(offsetx + glyph->bitmap.width) / (float)width;
		mFont[c].uvy2 = (float)(offsety + glyph->bitmap.rows) /  (float)height;

		offsetx += glyph->bitmap.width;
	}

	mWidth = width;
	mHeight = height;
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

	auto texture = std::make_shared<DXTexture>();
	HR(gDXDevice->CreateShaderResourceView(dump, &srvd, &texture->mSRV));
	mTexture = texture;
	SAFE_RELEASE(dump);

	FT_Done_Face(face);
	FT_Done_FreeType(lib);

	delete[] buffer;
}

Texture* Font::GetFontTexture() const
{
	return mTexture.get();
}
