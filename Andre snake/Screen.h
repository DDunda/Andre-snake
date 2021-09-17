#pragma once
#include <SDL.hpp>

struct Screen {
	struct State {
		virtual bool Open(Screen& screen) = 0;
		virtual bool Close(Screen& screen) = 0;
		virtual void Update(Screen& screen) = 0;
		virtual void Render(Screen& screen) = 0;
	};

	State* next_state = NULL;
	State* state = NULL;

	Screen();
	Screen(State* state);
	~Screen();

	void SetNewState(State* state);

	void Update();
	void Render();
};