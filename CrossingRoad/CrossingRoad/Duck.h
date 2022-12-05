#pragma once
#include "CrossingRoadGame.h"
#include "Vehicle.h"
class Duck: public Vehicle
{
	float speed = 0.05f;
	float time = 0;
	bool spriteIndex=false;
public:
	Duck(CrossingRoadGame* game, int x, int y, float speed) : Vehicle(game, x, y, speed) {
		width = 16;
		height = 8;
		this->speed = speed;
		id = L'D';
	}
	Duck(CrossingRoadGame* game, wstring dataString) : Vehicle(game, dataString) {
		wstringstream stream(dataString);
		wstring temp;
		getline(stream, temp, L'|');
		x = stoi(temp);
		getline(stream, temp, L'|');
		y = stoi(temp);
		getline(stream, temp, L'|');
		speed = stof(temp);
		getline(stream, temp, L'|');
		primaryColor = (COLOUR)stoi(temp);
		getline(stream, temp, L'|');
		darkColor = (COLOUR)stoi(temp);
		width = 16;
		height = 8;

		id = L'D';
	}
	void Draw()
	{
		if (speed > 0.00f)
			Draw1();
		else Draw2();
	}
	void Draw1()
	{
		game->Fill(x, y + 2, x + 1, y + 5, L' ', COLOUR::BG_DARK_MAGENTA);
		game->Fill(x + 2, y + 1, x + 14, y + 6, L' ', COLOUR::BG_YELLOW);
		game->Fill(x + 3, y, x + 6, y, L' ', COLOUR::BG_YELLOW);
		game->Fill(x + 3, y + 7, x + 6, y + 7, L' ', COLOUR::BG_YELLOW);
		game->Fill(x + 8, y, x + 13, y, L' ', COLOUR::BG_YELLOW);
		game->Fill(x + 8, y + 7, x + 13, y + 7, L' ', COLOUR::BG_YELLOW);
		game->Fill(x + 15, y + 2, x + 15, y + 5, L' ', COLOUR::BG_YELLOW);
		game->Fill(x + 3, y + 1, x + 4, y + 2, L' ', COLOUR::BG_WHITE);
		game->Fill(x + 3, y + 5, x + 4, y + 6, L' ', COLOUR::BG_WHITE);
		game->Draw(x + 3, y + 2, L' ', COLOUR::BG_BLACK);
		game->Draw(x + 3, y + 5, L' ', COLOUR::BG_BLACK);
		game->Draw(x + 7, y + 1, L' ', COLOUR::BG_DARK_YELLOW);
		game->Draw(x + 7, y + 6, L' ', COLOUR::BG_DARK_YELLOW);
		game->Fill(x + 8, y + 2, x + 8, y + 5, L' ', COLOUR::BG_DARK_YELLOW);
		game->Fill(x + 10, y + 1, x + 12, y + 1, L' ', COLOUR::BG_DARK_YELLOW);
		game->Fill(x + 10, y + 6, x + 12, y + 6, L' ', COLOUR::BG_DARK_YELLOW);
		game->Draw(x + 13, y, L' ', COLOUR::BG_DARK_YELLOW);
		game->Draw(x + 13, y + 7, L' ', COLOUR::BG_DARK_YELLOW);
		game->Fill(x + 15, y + 3, x + 15, y + 4, L' ', COLOUR::BG_DARK_YELLOW);
	}
	void Draw2()
	{
		game->Fill(x + 16 - 1, y + 2, x + 16, y + 5, L' ', COLOUR::BG_DARK_MAGENTA);
		game->Fill(x + 16 - 14, y + 1, x + 16 - 2, y + 6, L' ', COLOUR::BG_YELLOW);
		game->Fill(x + 16 - 6, y, x + 16 - 3, y, L' ', COLOUR::BG_YELLOW);
		game->Fill(x + 16 - 6, y + 7, x + 16 - 3, y + 7, L' ', COLOUR::BG_YELLOW);
		game->Fill(x + 16 - 13, y, x + 16 - 8, y, L' ', COLOUR::BG_YELLOW);
		game->Fill(x + 16 - 13, y + 7, x + 16 - 8, y + 7, L' ', COLOUR::BG_YELLOW);
		game->Fill(x + 16 - 15, y + 2, x + 16 - 15, y + 5, L' ', COLOUR::BG_YELLOW);
		game->Fill(x + 16 - 4, y + 1, x + 16 - 3, y + 2, L' ', COLOUR::BG_WHITE);
		game->Fill(x + 16 - 4, y + 5, x + 16 - 3, y + 6, L' ', COLOUR::BG_WHITE);
		game->Draw(x + 16 - 3, y + 2, L' ', COLOUR::BG_BLACK);
		game->Draw(x + 16 - 3, y + 5, L' ', COLOUR::BG_BLACK);
		game->Draw(x + 16 - 7, y + 1, L' ', COLOUR::BG_DARK_YELLOW);
		game->Draw(x + 16 - 7, y + 6, L' ', COLOUR::BG_DARK_YELLOW);
		game->Fill(x + 16 - 8, y + 2, x + 16 - 8, y + 5, L' ', COLOUR::BG_DARK_YELLOW);
		game->Fill(x + 16 - 12, y + 1, x + 16 - 10, y + 1, L' ', COLOUR::BG_DARK_YELLOW);
		game->Fill(x + 16 - 12, y + 6, x + 16 - 10, y + 6, L' ', COLOUR::BG_DARK_YELLOW);
		game->Draw(x + 16 - 13, y, L' ', COLOUR::BG_DARK_YELLOW);
		game->Draw(x + 16 - 13, y + 7, L' ', COLOUR::BG_DARK_YELLOW);
		game->Fill(x + 16 - 15, y + 3, x + 16 - 15, y + 4, L' ', COLOUR::BG_DARK_YELLOW);
	}
	void Update(float fElapsedTime)
	{
		time += fElapsedTime;
		if (speed > 0) {
			if (time > speed) {
				x = x - 8;
				if (x + width < 0) {
					x = game->GetGameWidth();
				}
				spriteIndex = !spriteIndex;
				time = 0;
			}
		}
		else
		{
			if (time > (abs)(speed)) {
				x = x + 8;
				if (x > game->GetGameWidth()) {
					x = 0;
				}
				spriteIndex = !spriteIndex;
				time = 0;
			}
		}

	}

	void SetCollisionMatrix() {
		game->FillCollisionMatrix(x, y, x + width - 1, y + height - 1, false);
	}
};

