#include "Vehicle.h"

void Vehicle::Draw1() {
	game->Fill(x + 0, y + 1, x + 7, y + 5, L' ', primaryColor);
	game->Fill(x + 3, y + 0, x + 6, y + 0, L' ', primaryColor);

	game->Fill(x + 0, y + 1, x + 1, y + 1, L' ', darkColor);
	game->Fill(x + 0, y + 5, x + 7, y + 5, L' ', darkColor);
	game->Fill(x + 3, y + 3, x + 6, y + 3, L' ', darkColor);

	game->Draw(x + 7, y + 1, L' ', darkColor);
	game->Draw(x + 2, y + 4, L' ', darkColor);
	game->Draw(x + 7, y + 4, L' ', darkColor);

	game->Fill(x + 3, y + 4, x + 6, y + 4, L' ', BG_WHITE);
	game->Fill(x + 2, y + 1, x + 2, y + 3, L' ', BG_WHITE);
	game->Fill(x + 1, y + 6, x + 2, y + 6, L' ', BG_BLACK);
	game->Fill(x + 6, y + 6, x + 7, y + 6, L' ', BG_BLACK);
}
void Vehicle::Draw2() {
	game->Fill(x + 0, y + 1, x + 7, y + 5, L' ', primaryColor);
	game->Fill(x + 1, y + 0, x + 4, y + 0, L' ', primaryColor);

	game->Fill(x + 6, y + 1, x + 7, y + 1, L' ', darkColor);
	game->Fill(x + 0, y + 5, x + 7, y + 5, L' ', darkColor);
	game->Fill(x + 1, y + 3, x + 4, y + 3, L' ', darkColor);

	game->Draw(x + 0, y + 1, L' ', darkColor);
	game->Draw(x + 5, y + 4, L' ', darkColor);
	game->Draw(x + 0, y + 4, L' ', darkColor);

	game->Fill(x + 1, y + 4, x + 4, y + 4, L' ', BG_WHITE);
	game->Fill(x + 5, y + 1, x + 5, y + 3, L' ', BG_WHITE);
	game->Fill(x + 0, y + 6, x + 1, y + 6, L' ', BG_BLACK);
	game->Fill(x + 5, y + 6, x + 6, y + 6, L' ', BG_BLACK);
}
void Vehicle::Draw()
{
	if (speed > 0.00f)
		Draw1();
	else Draw2();
}
void Vehicle::DrawAmbulance()
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
void Vehicle::AmbulanceUpdate(float fElapsedTime , bool STOP_OR_CONTINUE)
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
void Vehicle::Update(float fElapsedTime) {
	time += fElapsedTime;
	if (speed > 0) {
		if (time > speed) {
			x = x - 1;
			if (x + width < 0) {
				x = game->GetGameWidth();
			}
			time = 0;
		}
	}
	else
	{
		if (time > (abs)(speed)) {
			x = x + 1;
			if (x >game->GetGameWidth()) {
				x =0;
			}
			time = 0;
		}
	}
}
void Vehicle::DrawTree()
{
	game->Fill(x + 3, y + 6, x + 4, y + 6, L' ', COLOUR::BG_GREY);
	game->Fill(x + 1, y + 2, x + 6, y + 4, L' ', COLOUR::BG_MAGENTA);
	game->Fill(x + 2, y + 1, x + 5, y + 1, L' ', COLOUR::BG_MAGENTA);
	game->Fill(x + 3, y, x + 4, y, L' ', COLOUR::BG_MAGENTA);

	game->Fill(x + 1, y + 5, x + 6, y + 5, L' ', COLOUR::BG_DARK_MAGENTA);
	game->Fill(x + 2, y + 3, x + 5, y + 3, L' ', COLOUR::BG_DARK_MAGENTA);
	game->Fill(x + 3, y + 1, x + 4, y + 1, L' ', COLOUR::BG_DARK_MAGENTA);

}

void Vehicle::SetCollisionMatrix() {
	game->FillCollisionMatrix(x, y, x + width - 1, y + height-1, true);
}