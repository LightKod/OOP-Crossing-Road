#include "Tile.h"


void Tile::Draw(CrossingRoadGame& game) {
	//Vi du ve 1 o 16x16 mau den
	game.Fill(x, y,x + 16, y+ 16 ,L' ', FG_BLACK);
}

void Tile::Update(CrossingRoadGame& game, float fElapsedTime) {
	//Cai nay la vi du thoi, ong Vu lam thi tu sua lai nha
	static float time = 0;
	time += fElapsedTime;

	if (time > 0.1f) {
		Move(-1, 0);
		if (x + width < 0) {
			x = game.GetGameWidth();
		}
		time = 0;
	}
}