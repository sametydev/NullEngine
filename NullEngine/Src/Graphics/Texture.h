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
	virtual void Bind(uint slot = 0) = 0;
	virtual void UnBind() {};
	ID3D11ShaderResourceView* mSRV;
	uint bytePerPixel = 0; //Optional;
	uint width;
	uint height;
};

class TextureCache {
public:
	[[nodiscard]]static Texture* Load(LPCSTR filename);
	static std::unordered_map<std::string, std::shared_ptr<Texture>> mCache;
};