#include <PCH.h>
#include <Render/Font.h>
#include <freetype/freetype.h>

Font::Font()
{
}

void Font::Create(LPCSTR filename)
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
}
