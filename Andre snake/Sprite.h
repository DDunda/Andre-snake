#pragma once
#include <SDL.hpp>
#include <map>
#include <fstream>
#include <string>

struct SubTexture {
	SDL::Texture txt;
	SDL::Rect src;

	void Copy   (SDL::Renderer& r, const SDL::Rect& dst);
	void CopyF  (SDL::Renderer& r, const SDL::FRect& dst);

	void CopyEx (SDL::Renderer& r, const SDL::Rect& dst, const SDL::Point& center, double angle, SDL::Renderer::Flip flipType);
	void CopyEx (SDL::Renderer& r, const SDL::Rect& dst, double angle, SDL::Renderer::Flip flipType);

	void CopyExF(SDL::Renderer& r, const SDL::FRect& dst, const SDL::FPoint& center, double angle, SDL::Renderer::Flip flipType);
	void CopyExF(SDL::Renderer& r, const SDL::FRect& dst, double angle, SDL::Renderer::Flip flipType);
};

struct Sprite {
	SubTexture txt;
	SDL::Point size;

	void Copy   (SDL::Renderer& r, const SDL::Point& dst);
	void CopyF  (SDL::Renderer& r, const SDL::FPoint& dst);

	void CopyEx (SDL::Renderer& r, const SDL::Point& dst, const SDL::Point& center, double angle, SDL::Renderer::Flip flipType);
	void CopyEx (SDL::Renderer& r, const SDL::Point& dst, double angle, SDL::Renderer::Flip flipType);

	void CopyExF(SDL::Renderer& r, const SDL::FPoint& dst, const SDL::FPoint& center, double angle, SDL::Renderer::Flip flipType);
	void CopyExF(SDL::Renderer& r, const SDL::FPoint& dst, double angle, SDL::Renderer::Flip flipType);
};

struct SpriteLoader {
	SDL::Texture txt;
	SDL::Point stx_size;
	SDL::Point stx_origin;
	SDL::Point spr_size;

	SpriteLoader(const SDL::Texture& texture, const SDL::Point& subtexture_size, const SDL::Point& sprite_size, const SDL::Point& subtexture_origin = { 0,0 })
		: txt(texture), stx_size(subtexture_size), stx_origin(subtexture_origin), spr_size(sprite_size) {}

	SubTexture GetSubTexture(const SDL::Point& pos) {
		return { txt, { pos * stx_size + stx_origin, stx_size } };
	}

	Sprite GetSprite(const SDL::Point& pos) {
		return { GetSubTexture(pos), spr_size };
	}
};

class TextureManager {
public:
	std::map<std::string, SDL::Texture> textures;

	~TextureManager();

	SDL::Texture Load(SDL::Renderer& r, std::string name, const char* file_name);

	void UnloadAll();

	SDL::Texture operator[](std::string name);
};