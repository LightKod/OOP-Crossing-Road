#include "GrassTile.h"
void GrassTile::Draw() {
	game->Fill(x, y, x + 7, y + 7, L' ', BG_GREEN);
	game->Draw(x + 1, y + 2, L' ', BG_DARK_GREEN);
	game->Draw(x + 2, y + 1, L' ', BG_DARK_GREEN);
	game->Draw(x + 3, y + 2, L' ', BG_DARK_GREEN);
	game->Draw(x + 5, y + 4, L' ', BG_DARK_GREEN);
	game->Draw(x + 6, y + 3, L' ', BG_DARK_GREEN);
	game->Draw(x + 7, y + 4, L' ', BG_DARK_GREEN);
	game->Draw(x + 1, y + 6, L' ', BG_DARK_GREEN);
	game->Draw(x + 2, y + 5, L' ', BG_DARK_GREEN);
	game ->Draw(x + 3, y + 6, L' ', BG_DARK_GREEN);
}
void GrassTile::Update(float fElapsedTime) {
}