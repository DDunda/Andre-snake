#pragma once
#include "Andre.h"
#include "Screen.h"
#include "Board.h"
#include "NineSlice.h"
#include <SDL.hpp>

struct GamePlay : public Screen::State {
	Board board;
	Andre andre;
	TiledNineSlice grass;
	SDL::Texture sky;

	GamePlay(const SDL::Point& board_size);

	void SpawnAndre();

	void UpdateFruits();
	void RenderFruits();

	void SpawnRandom(CellState state);

	bool Open(Screen& screen);
	bool Close(Screen& screen);
	void Update(Screen& screen);
	void Render(Screen& screen);
};