#include "Screen.h"

Screen::Screen() : next_state(NULL), state(NULL) {}
Screen::Screen(State* state) : next_state(state), state(NULL) {}
Screen::~Screen() {
	if (next_state != NULL) delete next_state;
	if (state != NULL) delete state;
}

void Screen::SetNewState(State* state) {
	if (next_state != NULL)
		delete next_state;
	next_state = state;
}

void Screen::Update() {
	if (next_state != NULL && next_state->Open(*this)) {
		if (state != NULL && state->Close(*this)) {
			delete state;
			state = NULL;
		}
		if (state == NULL) {
			state = next_state;
			next_state = NULL;
		}
	}

	if (state != NULL)
		state->Update(*this);
}

void Screen::Render() {
	if (state != NULL)
		state->Render(*this);
}