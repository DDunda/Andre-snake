#include "GameOver.h"
#include "Globals.h"
#include <SDL.hpp>

using namespace SDL;

bool GameOver::Open(Screen& screen) {
	return true;
}
bool GameOver::Close(Screen& screen) {
	return true;
}
void GameOver::Update(Screen& screen) {
}
void GameOver::Render(Screen& screen) {
	r.SetDrawColour(DARK_GREY).Clear();
}