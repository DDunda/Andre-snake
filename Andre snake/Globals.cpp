#include "Globals.h"

using namespace SDL;

int cellSize = SPR_SIZE;

Uint32 cur_time = 0;
Uint32 delta_time = 10;

Window w;
Renderer r;

Input input;

TextureManager textures;

Sprite sprites[16];

WeightedArray<Sprite> grass_up(2,2);
WeightedArray<Sprite> grass_right(2,2);
WeightedArray<Sprite> grass_down(2,2);
WeightedArray<Sprite> grass_left(2,2);
Sprite grass_up_left, grass_up_right, grass_down_left, grass_down_right;
WeightedArray<Sprite> grass_center(4,20);

Screen screen;

bool KeyDown(Scancode scancode) {
	return input.GetScancode(scancode);
}

Uint32 KeyDownAt(Scancode scancode) {
	return input.scancode_down_at[scancode];
}

bool MouseInArea(SDL::Rect area) {
	return area.contains(input.mouse.pos);
}