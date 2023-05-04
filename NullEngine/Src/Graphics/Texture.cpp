#include <PCH.h>
#include <Graphics/Texture.h>
#include <filesystem>

Texture::Texture()
{
}
Texture::~Texture()
{
}

Texture* TextureCache::Load(LPCSTR filename)
{
	std::string name = std::filesystem::path(filename).filename();
	return nullptr;
}
