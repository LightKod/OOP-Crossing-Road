#include "Tile.h"


void Tile::DrawWater1(CrossingRoadGame& game) {
	//Vi du ve 1 o 16x16 mau den
	/*game.Fill(x, y,x + 16, y+ 16 ,L' ', FG_BLACK);*/
	//LANE NUOC
	game.Fill(x, y, x + width-1, y + height-1, L' ', COLOUR::BG_BLUE);
	game.DrawLine(x, y + 2, x + 2, y, L' ', COLOUR::BG_CYAN);
	game.DrawLine(x+2, y, x + 3, y+1, L' ', COLOUR::BG_CYAN);
	game.Draw(x + 5, y+1, L' ', COLOUR::BG_CYAN);
	game.DrawLine(x + 6, y + 2, x + 7, y + 2, L' ', COLOUR::BG_CYAN);
	game.DrawLine(x + 1, y + 5, x + 3, y + 7, L' ', COLOUR::BG_CYAN);
	game.DrawLine(x+3,y+7,x+5,y+5,L' ',COLOUR::BG_CYAN);
	game.DrawLine(x + 6, y + 5, x + 7, y + 6, L' ', COLOUR::BG_CYAN);
	game.Draw(x, y + 6, L' ', COLOUR::BG_WHITE);
	game.Draw(x + 4, y + 2, L' ', COLOUR::BG_WHITE);
}
void Tile::DrawWater2(CrossingRoadGame& game) {
	//Vi du ve 1 o 16x16 mau den
	/*game.Fill(x, y,x + 16, y+ 16 ,L' ', FG_BLACK);*/
	//LANE NUOC
	game.Fill(x, y, x + width-1, y + height-1, L' ', COLOUR::BG_BLUE);
	game.DrawLine(x, y + 2, x + 1, y + 3, L' ', COLOUR::BG_CYAN);
	game.DrawLine(x + 1, y + 3, x + 3, y + 1, L' ', COLOUR::BG_CYAN);
	game.DrawLine(x + 3, y + 1, x + 4, y + 2, L' ', COLOUR::BG_CYAN);
	game.DrawLine(x + 5, y + 1, x + 6, y + 1, L' ', COLOUR::BG_CYAN);
	game.Draw(x + 7, y + 2, L' ', COLOUR::BG_WHITE);

	game.DrawLine(x, y + 6, x + 1, y + 7, L' ', COLOUR::BG_CYAN);
	game.DrawLine(x + 3, y + 6, x + 4, y + 5, L' ', COLOUR::BG_CYAN);
	game.Draw(x + 5, y + 6, L' ', COLOUR::BG_CYAN);
	game.DrawLine(x + 6, y + 7, x + 7, y + 6, L' ', COLOUR::BG_CYAN);
	game.Draw(x + 2, y + 6, L' ', COLOUR::BG_WHITE);
}
void Tile::Draw1(CrossingRoadGame& game, float time)
{
	int n = (int)time % 2;
	switch (n) {
	case 0:
		DrawWater1(game);
		break;
	case 1:
		DrawWater2(game);
		break;
	}
}

void Tile::Update1(CrossingRoadGame& game, float fElapsedTime) {
	//Cai nay la vi du thoi, ong Vu lam thi tu sua lai nha
	time += fElapsedTime;
	Draw1(game, time);
}
void Tile::Draw2(CrossingRoadGame& game, float time)
{
	int n = (int)time % 2;
	switch (n) {
	case 0:
		DrawWater2(game);
		break;
	case 1:
		DrawWater1(game);
		break;
	}
}

void Tile::Update2(CrossingRoadGame& game, float fElapsedTime) {
	//Cai nay la vi du thoi, ong Vu lam thi tu sua lai nha
	time += fElapsedTime;
	Draw1(game, time);
}