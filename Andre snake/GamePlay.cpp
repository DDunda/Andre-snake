#include "GamePlay.h"
#include "GameOver.h"
#include "Globals.h"

#include <SDL.hpp>
#include <iostream>

using namespace SDL;
using namespace std;

GamePlay::GamePlay(const Point& board_size) : board({ SPR_SIZE, SPR_SIZE }, board_size), andre(board), grass(board_size, { SPR_SIZE, SPR_SIZE }, { SPR_SIZE,SPR_SIZE }, { SPR_SIZE,SPR_SIZE }) {
	w.SetSize(grass.GetPixelSize());
	sky = textures["sky_gradient"];
	SpawnAndre();

	grass.upper_left = grass_up_left;
	grass.upper_right = grass_up_right;
	grass.lower_left = grass_down_left;
	grass.lower_right = grass_down_right;

	grass_up.FillRandom(grass.top, board_size.w);
	grass_down.FillRandom(grass.bottom, board_size.w);
	grass_left.FillRandom(grass.left, board_size.h);
	grass_right.FillRandom(grass.right, board_size.h);

	grass_center.FillRandom(grass.center, board_size.w * board_size.h);
}

void GamePlay::SpawnAndre() {
	andre.Spawn(
		board.size / 2,
		{ Direction::RIGHT }
	);
}

void GamePlay::UpdateFruits() {
	if (board.fruits == 0) {
		int fruits_to_spawn = min(board.emptys, 2);
		for (int i = 0; i < fruits_to_spawn; i++) SpawnRandom(FRUIT);
		int super_fruits_to_spawn = min(board.emptys, andre.fruits_collected / 5);
		for (int i = 0; i < super_fruits_to_spawn; i++) SpawnRandom(SUPER_FRUIT);
	}
}

void GamePlay::RenderFruits() {
	for (int y = 0; y < board.size.h; y++) {
		for (int x = 0; x < board.size.w; x++) {
			switch (board[{x, y}])
			{
			case FRUIT:
				sprites[FRUIT_INDEX].Copy(r, Point(x, y) * cellSize + board.pos);
				break;
			case SUPER_FRUIT:
				sprites[SUPER_FRUIT_INDEX].Copy(r, Point(x, y) * cellSize + board.pos);
				break;
			}
		}
	}
}

void GamePlay::SpawnRandom(CellState state) {
	int empty_index = 0;
	int spawn_index = rand() % board.emptys;
	for (int i = 0; i < board.size.w * board.size.h; i++) {
		if (board[i] != EMPTY) continue;
		if (empty_index++ != spawn_index) continue;

		board.Set(i, state);
		return;
	}
}

bool GamePlay::Open(Screen& screen) {
	return true;
}
bool GamePlay::Close(Screen& screen) {
	return true;
}
void GamePlay::Update(Screen& screen) {
	if (andre.segments.empty()) {
		//screen.SetNewState(new GameOver());
		//return;
		if (cur_time - andre.last_moved > 500) {
			andre.Despawn();
			SpawnAndre();
		}
		else {
			return;
		}
	}
	UpdateFruits();
	andre.Update();
}
void GamePlay::Render(Screen& screen) {
	r.Copy_Fill(sky);
	grass.Render(r, {});
	RenderFruits();
	andre.Render();
}