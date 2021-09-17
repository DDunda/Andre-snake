#pragma once
#include "Board.h"
#include <deque>

struct Andre {
	std::deque<Direction> segments = { RIGHT };
	SDL::Point tail;
	SDL::Point head;
	Uint32 last_moved;
	Uint8 growth_ticks = 0;
	bool alive;
	Board& board;

	int fruits_collected = 0;
	int super_fruits_collected = 0;

	Andre(Board& board);
	
	void Despawn();
	void Spawn(const SDL::Point& tail, const std::initializer_list<Direction>& segments);

	void MoveTail();
	void Move(Direction dir);

	void Update();
	void Render();
};