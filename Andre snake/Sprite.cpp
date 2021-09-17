#include "Sprite.h"

using namespace SDL;

void SubTexture::Copy(Renderer& r, const Rect& dst) {
	r.Copy(txt, src, dst);
}

void SubTexture::CopyF(Renderer& r, const FRect& dst) {
	r.CopyF(txt, src, dst);
}

void SubTexture::CopyEx(Renderer& r, const Rect& dst, const Point& center, double angle, Renderer::Flip flipType) {
	r.CopyEx(txt, src, dst, center, angle, flipType);
}
void SubTexture::CopyEx(Renderer& r, const Rect& dst, double angle, Renderer::Flip flipType) {
	r.CopyEx(txt, src, dst, angle, flipType);
}

void SubTexture::CopyExF(Renderer& r, const FRect& dst, const FPoint& center, double angle, Renderer::Flip flipType) {
	r.CopyExF(txt, src, dst, center, angle, flipType);
}
void SubTexture::CopyExF(Renderer& r, const FRect& dst, double angle, Renderer::Flip flipType) {
	r.CopyExF(txt, src, dst, angle, flipType);
}

void Sprite::Copy(Renderer& r, const Point& pos) {
	txt.Copy(r, { pos,size });
}

void Sprite::CopyF(Renderer& r, const FPoint& pos) {
	txt.CopyF(r, { pos,size });
}

void Sprite::CopyEx(Renderer& r, const Point& pos, const Point& center, double angle, Renderer::Flip flipType) {
	txt.CopyEx(r, { pos,size }, center, angle, flipType);
}
void Sprite::CopyEx(Renderer& r, const Point& pos, double angle, Renderer::Flip flipType) {
	txt.CopyEx(r, { pos,size }, angle, flipType);
}

void Sprite::CopyExF(Renderer& r, const FPoint& pos, const FPoint& center, double angle, Renderer::Flip flipType) {
	txt.CopyExF(r, { pos,size }, center, angle, flipType);
}
void Sprite::CopyExF(Renderer& r, const FPoint& pos, double angle, Renderer::Flip flipType) {
	txt.CopyExF(r, { pos,size }, angle, flipType);
}

TextureManager::~TextureManager() { UnloadAll(); }

Texture TextureManager::Load(SDL::Renderer& r, std::string name, const char* file_name) {
	return textures[name] = IMG::LoadTexture(r, file_name);
}

void TextureManager::UnloadAll() {
	textures.clear();
}

Texture TextureManager::operator[](std::string name) {
	return textures[name];
}