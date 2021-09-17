#pragma once
#include "Direction.h"
#include <SDL.hpp>

enum CellState {
	EMPTY,
	ANDRE,
	FRUIT,
	SUPER_FRUIT
};

struct Board {
	SDL::Point pos;
	SDL::Point size;
	CellState* cells = NULL;
	int emptys = 0;
	int fruits = 0;

	Board();
	Board(const SDL::Point& pos, const SDL::Point& size);
	Board(Board&& board) noexcept;
	~Board();

	Board& operator=(Board&& board) noexcept;

	CellState operator[](const SDL::Point& pos);
	CellState operator[](int i);

	bool ValidCell(const SDL::Point& pos);
	CellState Get(const SDL::Point& pos);
	void Set(const SDL::Point& pos, CellState state);
	CellState Get(int i);
	void Set(int i, CellState state);
};