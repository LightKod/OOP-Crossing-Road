#include "Tile.h"


void Tile::Draw(CrossingRoadGame & game, int x, int y) {
	game.Draw(x, y, L' ', FG_BLACK);
}