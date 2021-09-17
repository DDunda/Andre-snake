#include "NineSlice.h"

using namespace SDL;

TiledNineSlice::TiledNineSlice(Point size, Point tile_size, Point ulm, Point lrm) :
	size(size), tile_size(tile_size), ulm(ulm), lrm(lrm) {

	top    = new Sprite[size.w];
	bottom = new Sprite[size.w];
	left   = new Sprite[size.h];
	right  = new Sprite[size.h];
	center = new Sprite[size.w * size.h];
}

TiledNineSlice::~TiledNineSlice() {
	delete[] top;
	delete[] bottom;
	delete[] left;
	delete[] right;
	delete[] center;
}

void TiledNineSlice::Render(SDL::Renderer& r, SDL::Point pos) {		
	// Center
	for (int y = 0, i = 0; y < size.h; y++)
		for (int x = 0; x < size.w; x++, i++)
			center[i].Copy(r, pos + Point(x, y) * tile_size + ulm);

	// Sides
	for (int x = 0; x < size.w; x++) {
		top[x]   .Copy(r, pos + Point(x * tile_size.w + ulm.w, 0));
		bottom[x].Copy(r, pos + Point(x, size.h) * tile_size + ulm);
	}
	for (int y = 0; y < size.h; y++) {
		left[y] .Copy(r, pos + Point(0, y * tile_size.h + ulm.h));
		right[y].Copy(r, pos + Point(size.w, y) * tile_size + ulm);
	}

	// Corners
	upper_left .Copy(r, pos);
	upper_right.Copy(r, pos + Point(size.w * tile_size.w + ulm.w, 0));
	lower_left .Copy(r, pos + Point(0, size.h * tile_size.h + ulm.h));
	lower_right.Copy(r, pos + size * tile_size + ulm);
}

Point TiledNineSlice::GetPixelSize() {
	return ulm + lrm + size * tile_size;
}