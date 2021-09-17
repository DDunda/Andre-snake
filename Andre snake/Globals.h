#pragma once

#include <SDL.hpp>
#include "Sprite.h"
#include "Screen.h"
#include "WeightedArray.h"

const int STX_SIZE = 16;
const int SPR_SCALE = 4;
const int SPR_SIZE = STX_SIZE * SPR_SCALE;

const int FRUIT_INDEX = 0;
const int SUPER_FRUIT_INDEX = 15;

extern int cellSize;

extern Uint32 cur_time;
extern Uint32 delta_time;

extern Uint32 true_cur_time;
extern Uint32 true_delta_time;

extern SDL::Window w;
extern SDL::Renderer r;

extern SDL::Input input;

extern TextureManager textures;

extern Sprite sprites[16];

extern WeightedArray<Sprite> grass_up;
extern WeightedArray<Sprite> grass_right;
extern WeightedArray<Sprite> grass_down;
extern WeightedArray<Sprite> grass_left;
extern Sprite grass_up_left, grass_up_right, grass_down_left, grass_down_right;
extern WeightedArray<Sprite> grass_center;

extern Screen screen;

bool KeyDown(SDL::Scancode scancode);
Uint32 KeyDownAt(SDL::Scancode scancode);

bool MouseInArea(const SDL::Rect& area);