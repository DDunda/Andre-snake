#pragma once
#include "sprite.h"
#include <SDL.hpp>

struct TiledNineSlice {
	SDL::Point pos, size, tile_size, ulm, lrm;

	Sprite upper_left, upper_right, lower_left, lower_right;
	Sprite *top, *left, *right, *bottom, *center;

	TiledNineSlice(SDL::Point size, SDL::Point tile_size, SDL::Point upper_left_margin, SDL::Point lower_right_margin);
	~TiledNineSlice();

	void Render(SDL::Renderer& r, SDL::Point pos);

	SDL::Point GetPixelSize();
};