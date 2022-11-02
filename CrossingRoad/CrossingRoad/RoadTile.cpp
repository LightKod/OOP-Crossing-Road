#include "RoadTile.h"

void RoadTile::Draw(CrossingRoadGame& game)
{
	game.Fill(x, y, x + width - 1, y + height - 1, L' ', COLOUR::BG_GREY);
	game.Fill(x, y + 8, x + 4 - 1, y + 8, L' ', COLOUR::BG_WHITE);
	game.Fill(x + width - 4, y + 8, x + width - 1, y + 8, L' ', COLOUR::BG_WHITE);
	game.Fill(x, y, x + width - 1, y, L' ', COLOUR::BG_DARK_GREY);
	game.Fill(x, y + height - 1, x + width - 1, y + height - 1, L' ', COLOUR::BG_DARK_GREY);
}
