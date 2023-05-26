#include <PCH.h>
#include <Render/Font.h>
#include <freetype/freetype.h>

Font::Font()
{
}

void Font::Create(LPCSTR filename,uint size)
{
	FT_Library lib;
	FT_Face face;
	if (FT_Init_FreeType(&lib))
	{
		//assert
	}
	if (FT_New_Face(lib,filename,0,&face))
	{
		//assert
	}

	FT_Set_Pixel_Sizes(face,0,size);

	if (FT_Load_Char(face,'X',FT_LOAD_RENDER))
	{
		//assert
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
	}
}
