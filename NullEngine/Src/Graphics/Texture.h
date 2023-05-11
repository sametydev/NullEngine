#pragma once
#include <Core/TypeDecl.h>
#include <unordered_map>
#include <Core/FileSystem.h>


class Texture
{
public:
	Texture();
	virtual ~Texture();

	virtual void Load(LPCSTR filename) = 0;
	virtual void BindPipeline(uint slot = 0) = 0;
	virtual void UnBind() {};

	uint bytePerPixel = 0; //Optional;
	uint width;
	uint height;
};

class TextureCache {
public:
	static Texture* Load(LPCSTR filename);
	static std::unordered_map<std::string, std::shared_ptr<Texture>> mCache;
};