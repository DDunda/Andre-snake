#include "Board.h"

using namespace SDL;
using namespace std;

Board::Board() {}
Board::Board(const Point& pos, const Point& size) : pos(pos), size(size), cells(new CellState[size.w * size.h]{ EMPTY }), emptys(size.w * size.h) {}
Board::Board(Board&& board) noexcept { *this = move(board); }
Board::~Board() { if (cells != NULL) delete[] cells; }

Board& Board::operator=(Board&& board) noexcept { swap(size, board.size); swap(cells, board.cells); swap(emptys, board.emptys); swap(fruits, board.fruits); return *this; }

CellState Board::operator[](const SDL::Point& pos) { return cells[pos.x + pos.y * size.w]; }
CellState Board::operator[](int i) { return cells[i]; }

bool Board::ValidCell(const Point& pos) { return pos.inRect({ 0, 0, size }); }
CellState Board::Get(const Point& pos) { return (*this)[pos]; }
void Board::Set(const Point& pos, CellState state) {
	CellState old_state = (*this)[pos];

	if (old_state == EMPTY && state != EMPTY) emptys--;
	if (old_state != EMPTY && state == EMPTY) emptys++;

	else if (old_state == FRUIT || old_state == SUPER_FRUIT) fruits--;

	else if (state == FRUIT || state == SUPER_FRUIT) fruits++;

	cells[pos.x + pos.y * size.w] = state;
}
CellState Board::Get(int i) { return (*this)[i]; }
void Board::Set(int i, CellState state) {
	CellState old_state = (*this)[i];

	if (old_state == EMPTY) emptys--;
	else if (old_state == FRUIT || old_state == SUPER_FRUIT) fruits--;

	if (state == EMPTY) emptys++;
	else if (state == FRUIT || state == SUPER_FRUIT) fruits++;

	cells[i] = state;
}