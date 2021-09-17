#include "Andre.h"
#include "Globals.h"

using namespace SDL;
using namespace std;

Point GetDelta(Direction dir) {
	switch (dir)
	{
	case UP: return { 0, -1 };
	case RIGHT: return { 1, 0 };
	case DOWN: return { 0, 1 };
	case LEFT: return { -1, 0 };
	}
}

Direction FlipDir(Direction dir) {
	switch (dir)
	{
	case UP: return DOWN;
	case DOWN: return UP;
	case RIGHT: return LEFT;
	case LEFT: return RIGHT;
	}
}

Andre::Andre(Board& board) : board(board) { last_moved = cur_time; }

void Andre::Spawn(const Point& _tail, const std::initializer_list<Direction>& _segments) {
	tail = _tail;
	head = _tail;
	board.Set(_tail, ANDRE);

	for(Direction dir : _segments) {
		head += GetDelta(dir);
		board.Set(head, ANDRE);
	}

	segments = _segments;
	alive = true;
}

void Andre::Despawn() {
	board.Set(tail, EMPTY);
	board.Set(head, EMPTY);
}

void Andre::MoveTail() {
	last_moved = cur_time;
	if (growth_ticks == 0) {
		board.Set(tail, EMPTY);
		tail += GetDelta(segments.front());
		segments.pop_front();
	}
	else growth_ticks--;
}

void Andre::Move(Direction dir) {
	Point delta = GetDelta(dir);
	Point new_head = head + delta;
	CellState eaten = board[new_head];

	if (board.ValidCell(new_head) && eaten != ANDRE) {
		segments.push_back(dir);
		head = new_head;
		board.Set(new_head, ANDRE);

		switch (eaten)
		{
		case FRUIT:
			fruits_collected++;
			growth_ticks++;
			break;
		case SUPER_FRUIT:
			super_fruits_collected++;
			growth_ticks += 5;
			break;
		}
	}
	else {
		alive = false;
		growth_ticks = 0;
	}
	MoveTail();
}

void Andre::Update() {
	if (alive) {
		Uint32 latest_press = 0;
		Direction dir = (Direction)0;
		Direction cur_dir = segments.back();
		Uint32 tmp_latest = 0;

		if (KeyDown(Scancode::LEFT) || KeyDown(Scancode::A)) {
			dir = LEFT;
			latest_press = max(KeyDownAt(Scancode::LEFT), KeyDownAt(Scancode::A));
		}

		tmp_latest = max(KeyDownAt(Scancode::RIGHT), KeyDownAt(Scancode::D));
		if (tmp_latest > latest_press) {
			if (KeyDown(Scancode::RIGHT) || KeyDown(Scancode::D)) {
				dir = RIGHT;
				latest_press = tmp_latest;
			}
		}
		tmp_latest = max(KeyDownAt(Scancode::UP), KeyDownAt(Scancode::W));
		if (tmp_latest > latest_press) {
			if (KeyDown(Scancode::UP) || KeyDown(Scancode::W)) {
				dir = UP;
				latest_press = tmp_latest;
			}
		}
		tmp_latest = max(KeyDownAt(Scancode::DOWN), KeyDownAt(Scancode::S));
		if (tmp_latest > latest_press) {
			if (KeyDown(Scancode::DOWN) || KeyDown(Scancode::S)) {
				dir = DOWN;
				latest_press = tmp_latest;
			}
		}

		if (dir != 0 && dir != cur_dir && dir != FlipDir(cur_dir)) {
			Move(dir);
		}
		else {
			if (cur_time - last_moved > 250)
				Move(cur_dir);
		}
	}
	else {
		if (cur_time - last_moved > 50)
			MoveTail();
	}
}

void Andre::Render() {
	if (segments.empty()) return;
	Point pos = tail;
	Direction lastDir = (Direction)0;

	for (Direction dir : segments) {
		sprites[lastDir | FlipDir(dir)].Copy(r, pos * cellSize + board.pos);

		pos += GetDelta(dir);


		lastDir = dir;
	}

	sprites[(~lastDir) & 0b1111].Copy(r, pos * cellSize + board.pos);
}