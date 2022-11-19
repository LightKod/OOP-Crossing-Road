#include "RoadTile.h"

void RoadTile::Draw()
{
	game->Fill(x, y, x + width - 1, y + height - 1, L' ', COLOUR::BG_GREY);
	game->Fill(x, y + 4, x + 1, y + 4, L' ', COLOUR::BG_WHITE);
	game->Fill(x + width - 2, y + 4, x + width - 1, y + 4, L' ', COLOUR::BG_WHITE);
	//game->Fill(x, y, x + width - 1, y, L' ', COLOUR::BG_DARK_GREY);
	game->Fill(x, y + height - 1, x + width - 1, y + height - 1, L' ', COLOUR::BG_DARK_GREY);
}
