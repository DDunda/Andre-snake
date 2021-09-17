#include "TextureAtlas.h"

using namespace SDL;

Uint32 TextureAtlas::LoadUint32(std::ifstream& ifs) {
	union {
		Uint32 num;
		Uint8 dat[4];
	};
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	dat[0] = ifs.get();
	dat[1] = ifs.get();
	dat[2] = ifs.get();
	dat[3] = ifs.get();
#else
	dat[3] = ifs.get();
	dat[2] = ifs.get();
	dat[1] = ifs.get();
	dat[0] = ifs.get();
#endif
	return num;
}

Sint32 TextureAtlas::LoadInt32(std::ifstream& ifs) {
	union {
		Sint32 num;
		Uint8 dat[4];
	};
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	dat[0] = ifs.get();
	dat[1] = ifs.get();
	dat[2] = ifs.get();
	dat[3] = ifs.get();
#else
	dat[3] = ifs.get();
	dat[2] = ifs.get();
	dat[1] = ifs.get();
	dat[0] = ifs.get();
#endif
	return num;
}

float TextureAtlas::LoadFloat(std::ifstream& ifs) {
	union {
		float num;
		Uint8 dat[4];
	};
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	dat[0] = ifs.get();
	dat[1] = ifs.get();
	dat[2] = ifs.get();
	dat[3] = ifs.get();
#else
	dat[3] = ifs.get();
	dat[2] = ifs.get();
	dat[1] = ifs.get();
	dat[0] = ifs.get();
#endif
	return num;
}

std::string TextureAtlas::LoadNullString(std::ifstream& ifs) {
	std::string str;
	char c;
	while ((c = ifs.get()) != 0)
		str += c;
	return str;
}

Texture TextureAtlas::LoadTexture(std::ifstream& ifs) {
	return IMG::LoadTexture(r, LoadNullString(ifs).c_str());
}

Point TextureAtlas::LoadPoint(std::ifstream& ifs) {
	return {
		(int)LoadUint32(ifs),
		(int)LoadUint32(ifs)
	};
}

Rect TextureAtlas::LoadRect(std::ifstream& ifs) {
	return {
		LoadPoint(ifs),
		LoadPoint(ifs)
	};
}

SubTexture TextureAtlas::LoadSubTexture(std::ifstream& ifs) {
	return {
		textures[LoadUint32(ifs)],
		LoadRect(ifs)
	};
}

TextureAtlas::SubTextureGroup TextureAtlas::LoadSubTextureGroup(std::ifstream& ifs) {
	Uint32 n = LoadUint32(ifs);
	SubTexture* subtextures = new SubTexture[n];
	for (Uint64 i = 0; i < n; i++) {
		subtextures[i] = LoadSubTexture(ifs);
	}
	return { n, subtextures };
}

void TextureAtlas::Clear() {
	textures.clear();
	subtextures.clear();
	for (auto pair : subtexture_groups) delete[] pair.second.subtextures;
	subtexture_groups.clear();
}

void TextureAtlas::Load(const std::string& filename) {
	std::ifstream ifs(filename);
	Clear();
	
	Uint32 texture_count = LoadUint32(ifs);
	textures.reserve(texture_count);
	for (Uint64 i = 0; i < texture_count; i++) {
		textures[i] = LoadTexture(ifs);
	}

	Uint32 sprite_count = LoadUint32(ifs);
	for (Uint64 i = 0; i < sprite_count; i++) {
		subtextures[LoadNullString(ifs)] = LoadSubTexture(ifs);
	}
}

SubTexture TextureAtlas::GetSubTexture(std::string& name) {
	if (subtextures.count(name))
		return subtextures[name];
	else
		return { Texture(), {} };
}