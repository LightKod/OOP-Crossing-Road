#include "Ambulance.h"
void Ambulance::Draw()
{
		//VE THAN XE CUU THUONG
		game->Fill(x + 0, y + 0, x + 4, y + 5, L' ', COLOUR::BG_WHITE);
		game->Draw(x + 5, y + 0, L' ', COLOUR::BG_WHITE);
		game->Fill(x + 5, y + 4, x + 7, y + 5, L' ', COLOUR::BG_WHITE);
		//VE BIEU TUONG CUU THUONG
		game->Fill(x + 2, y + 1, x + 2, y + 3, L' ', COLOUR::BG_RED);
		game->Fill(x + 1, y + 2, x + 3, y + 2, L' ', COLOUR::BG_RED);
		//VE KINH
		game->Fill(x + 5, y + 1, x + 5, y + 3, L' ', COLOUR::BG_BLACK);
		game->DrawLine(x + 5, y + 1, x + 7, y + 3, L' ', COLOUR::BG_BLACK);
		game->Draw(x + 6, y + 3, L' ', COLOUR::BG_BLACK);
		game->Fill(x + 0, y + 6, x + 7, y + 6, L' ', COLOUR::BG_GREY);
		game->Fill(x + 1, y + 7, x + 2, y + 7, L' ', COLOUR::BG_DARK_GREY);
		game->Fill(x + 5, y + 7, x + 6, y + 7, L' ', COLOUR::BG_DARK_GREY);

}
void Ambulance::AmbulanceUpdate(float fElapsedTime, bool STOP_OR_CONTINUE)
{
	if (STOP_OR_CONTINUE) {
		time += fElapsedTime;
		if (time > speed) {
			if (x == game->GetGameWidth() - 8);
			else {
				x = x + 1;
				time = 0;
			}
		}
	}
}