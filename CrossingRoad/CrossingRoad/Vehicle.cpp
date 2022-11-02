#include "Vehicle.h"

void Vehicle::Draw(CrossingRoadGame& game) {
	game.Fill(x + 0, y + 1, x + 7, y + 5, L' ', primaryColor);
	game.Fill(x + 3, y + 0, x + 6, y + 0, L' ', primaryColor);

	game.Fill(x + 0, y + 1, x + 1, y + 1, L' ', darkColor);
	game.Fill(x + 0, y + 5, x + 7, y + 5, L' ', darkColor);
	game.Fill(x + 3, y + 3, x + 6, y + 3, L' ', darkColor);

	game.Draw(x + 7, y + 1, L' ', darkColor);
	game.Draw(x + 2, y + 4, L' ', darkColor);
	game.Draw(x + 7, y + 4, L' ', darkColor);

	game.Fill(x + 3, y + 4, x + 6, y + 4, L' ', BG_WHITE);
	game.Fill(x + 2, y + 1, x + 2, y + 3, L' ', BG_WHITE);

	game.Fill(x + 1, y + 6, x + 2, y + 6, L' ', BG_BLACK);
	game.Fill(x + 6, y + 6, x + 7, y + 6, L' ', BG_BLACK);
}
void Vehicle::Update(CrossingRoadGame& game, float fElapsedTime) {
	time += fElapsedTime;

	if (time > speed) {
		Move(-1, 0);
		if (x + width < 0) {
			x = game.GetGameWidth();
		}
		time = 0;
	}
}