#pragma once
#include "Screen.h"

struct GameOver : public Screen::State {
	bool Open(Screen& screen);
	bool Close(Screen& screen);
	void Update(Screen& screen);
	void Render(Screen& screen);
};