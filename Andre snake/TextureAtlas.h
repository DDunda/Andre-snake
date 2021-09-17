#pragma once
#include "Sprite.h"

struct TextureAtlas {
	struct SubTextureGroup {
		Uint32 n;
		SubTexture* subtextures;
	};

	SDL::Renderer& r;
	std::vector<SDL::Texture> textures;
	std::map<std::string, SubTexture> subtextures;
	std::map<std::string, SubTextureGroup> subtexture_groups;

	Uint32 LoadUint32(std::ifstream& ifs);
	Sint32 LoadInt32(std::ifstream& ifs);
	float LoadFloat(std::ifstream& ifs);

	std::string LoadNullString(std::ifstream& ifs);

	SDL::Texture LoadTexture(std::ifstream& ifs);
	SubTexture LoadSubTexture(std::ifstream& ifs);
	SubTextureGroup LoadSubTextureGroup(std::ifstream& ifs);

	SDL::Point LoadPoint(std::ifstream& ifs);
	SDL::Rect LoadRect(std::ifstream& ifs);

	void Clear();

	void Load(const std::string& filename);

	SubTexture GetSubTexture(std::string& name);
};