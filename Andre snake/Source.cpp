#include "Direction.h"
#include "MainMenu.h"
#include "GamePlay.h"
#include "Globals.h"
#include <SDL.hpp>
#include <iostream>

using namespace SDL;
using namespace std;

void LoadResources() {
	textures.Load(r, "spritesheet", "spritesheet.png");
	textures.Load(r, "sky_gradient", "sky_gradient.png");
}

void CreateSprites() {
	SpriteLoader loader = SpriteLoader(textures["spritesheet"], {STX_SIZE, STX_SIZE}, {SPR_SIZE, SPR_SIZE});

	sprites[UP   | LEFT ] = loader.GetSprite({ 0,0 }); // 9
	sprites[UP   | RIGHT] = loader.GetSprite({ 1,0 }); // 3
	sprites[DOWN | RIGHT] = loader.GetSprite({ 1,1 }); // 6
	sprites[DOWN | LEFT ] = loader.GetSprite({ 0,1 }); // 12

	sprites[DOWN | UP   ] = loader.GetSprite({ 2,0 }); // 5
	sprites[LEFT | RIGHT] = loader.GetSprite({ 2,1 }); // 10

	sprites[DOWN ] = loader.GetSprite({ 0,2 }); // 4
	sprites[LEFT ] = loader.GetSprite({ 1,2 }); // 8
	sprites[UP   ] = loader.GetSprite({ 1,3 }); // 1
	sprites[RIGHT] = loader.GetSprite({ 0,3 }); // 2

	sprites[(~UP)    & 0b1111] = loader.GetSprite({ 2,2 }); // 14
	sprites[(~RIGHT) & 0b1111] = loader.GetSprite({ 3,2 }); // 13
	sprites[(~DOWN)  & 0b1111] = loader.GetSprite({ 3,3 }); // 11
	sprites[(~LEFT)  & 0b1111] = loader.GetSprite({ 2,3 }); // 7

	sprites[FRUIT_INDEX]       = loader.GetSprite({ 3,0 }); // 0
	sprites[SUPER_FRUIT_INDEX] = loader.GetSprite({ 3,1 }); // 15

	grass_up_left    =   loader.GetSprite({4,0});
	grass_up.data[0] = { loader.GetSprite({5,0}), 1 };
	grass_up.data[1] = { loader.GetSprite({6,0}), 2 };
	grass_up_right   =   loader.GetSprite({7,0});

	grass_left.data[0]   = { loader.GetSprite({4,1}), 1 };
	grass_center.data[0] = { loader.GetSprite({5,1}), 3 };
	grass_center.data[1] = { loader.GetSprite({6,1}), 5 };
	grass_right.data[0]  = { loader.GetSprite({7,1}), 1 };

	grass_left.data[1]   = { loader.GetSprite({4,2}), 2 };
	grass_center.data[2] = { loader.GetSprite({5,2}), 12 };
	grass_center.data[3] = { loader.GetSprite({6,2}), 20 };
	grass_right.data[1]  = { loader.GetSprite({7,2}), 2 };

	grass_down_left    =   loader.GetSprite({4,3});
	grass_down.data[0] = { loader.GetSprite({5,3}), 1 };
	grass_down.data[1] = { loader.GetSprite({6,3}), 2 };
	grass_down_right   =   loader.GetSprite({7,3});
}

int main(int argc, char* argv[]) {
	srand(time(0));

	Init();
	IMG::Init((int)IMG::InitFlags::PNG);

	CreateWindowAndRenderer(input.windowSize = { 500, 500 }, w, r);

	LoadResources();
	CreateSprites();
	
	w.SetTitle("Andre snake");

	screen.SetNewState(new GamePlay({ 15,10 })); // new MainMenu()

	// "True time" refers to the real world time, however the rest of the game is fixed update and uses an ideal time
	Uint32 true_cur_time = GetTicks();

	for (int frame = 0; input.running; frame++) {
		input.Update();

		Uint32 true_delta_time = GetTicks() - true_cur_time;
		while (true_delta_time > delta_time) {
			cur_time += delta_time;
			true_cur_time += delta_time;
			true_delta_time -= delta_time;

			screen.Update();
		}

		screen.Render();

		r.Present();

		Delay(8);
	}

	textures.UnloadAll();

	IMG::Quit();
	Quit();

	return 0;
}