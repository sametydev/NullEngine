#include <PCH.h>
#include <Graphics/Texture.h>
#include <filesystem>
#include <Graphics/DX11/DXTexture.h>

Texture::Texture()
{
}
Texture::~Texture()
{
}
std::unordered_map<std::string, std::shared_ptr<Texture>> TextureCache::mCache;
Texture* TextureCache::Load(LPCSTR filename)
{
	std::string name = FileSystem::GetNameFromPath(filename);

	auto found = mCache.find(name);

	if (found != mCache.end())
	{
		return found->second.get();
	}

	auto texture = std::make_shared<DXTexture>();
	texture->Load(filename);

	mCache.insert(std::make_pair(name,texture));

	return texture.get();
}
