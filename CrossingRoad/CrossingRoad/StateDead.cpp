#include "StateDead.h"
bool StateDead::OnStateEnter()
{
	Sound DeadSound;
	DeadSound.OpenImpactsSound();
	DeadSound.PlayImpactsSound();
	DeadSound.CloseSound();
	Ambulance = new Vehicle(game, 0, pPlayer->GetY());
	game->Fill(0, 0, 120, 96, L' ', COLOUR::BG_BLUE);
	pPlayer->Draw();
	Ambulance->DrawAmbulance();
	return true;
}
bool StateDead::Update(float fElapsedTime)
{
	if (h == 0) {
		DrawDeadBoard();
		if (game->GetKey(VK_SPACE).bReleased)
		{
			switch (optionIndex)
			{
			case 0:
			{
				h++;
				DeadChoice = true;
				break;
			}
			case 1:
			{
				h++;
				DeadChoice = false;
				break;
			}
			}
		}
		if (game->GetKey(VK_UP).bReleased)
		{
			optionIndex--;
			if (optionIndex < 0)
				optionIndex = 1;
		}
		if (game->GetKey(VK_DOWN).bReleased)
		{
			optionIndex++;
			if (optionIndex >= 2)
				optionIndex = 0;
		}
	}else DeadAnimation(fElapsedTime, DeadChoice);
	return true;
}
void StateDead::DeadAnimation(float fElapsedTime,bool Option)
{
	if (Ambulance->GetX() == game->GetGameWidth()-8)
	{
		if (Option)
		{
			DrawSaveScreen();
			time += fElapsedTime;
			if (time > 1.0f)
				game->SetState(new StatePlay(game));
		}
		else
		{
			DrawDeadScreen();
			time += fElapsedTime;
			if (time > 1.0f)
				game->SetState(new StateMenu(game));
		}
	}
	else {
		game->Fill(0, 0, 120, 96, L' ', COLOUR::BG_BLUE);
		if (optionIndex != 2)
		{
			if (pPlayer->GetX() <= Ambulance->GetX())
				if (Option);
				else pPlayer->Draw();
			else pPlayer->Draw();
			Ambulance->DrawAmbulance();
			Ambulance->AmbulanceUpdate(fElapsedTime, true);
			if (Option)
			{
				if (Ambulance->GetX() == pPlayer->GetX())
				{
					Ambulance->AmbulanceUpdate(fElapsedTime, false);
					Ambulance->AmbulanceUpdate(fElapsedTime, true);
				}
			}

		}
	}
}
void StateDead::DrawSaveScreen()
{
	game->Fill(0, 0, 160, 96, L' ', COLOUR::BG_WHITE);
	string2Pixel(L"NICE", 160 / 2-8, 96 / 2, COLOUR::FG_YELLOW, COLOUR::BG_WHITE);
}
void StateDead::DrawDeadScreen()
{
	game->Fill(0, 0, 160, 96, L' ', COLOUR::BG_BLACK);
	string2Pixel(L"REJECTED", 160 / 2 - 20, 96 / 2, COLOUR::FG_RED, COLOUR::BG_BLACK);
}
void StateDead::DrawCryFrog(int x,int y)
{
	game->Fill(x + 1, y, x + 2, y, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 5, y, x + 6, y, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x, y + 1, x, y + 2, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 3, y + 1, x + 4, y + 2, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 7, y + 1, x + 7, y + 2, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 1, y + 3, x + 6, y + 3, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 2, y + 4, x + 5, y + 4, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 1, y + 5, x + 6, y + 6, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x, y + 7, x + 2, y + 7, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 5, y + 7, x + 7, y + 7, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 3, y + 4, x + 4, y + 4, L' ', COLOUR::BG_RED);
	game->Fill(x + 2, y + 5, x + 5, y + 6, L' ', COLOUR::BG_GREEN);
	game->Fill(x + 3, y + 6, x + 4, y + 6, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 2, y + 2, x + 2, y + 2, L' ', COLOUR::BG_BLACK);
	game->Fill(x + 5, y + 2, x + 5, y + 2, L' ', COLOUR::BG_BLACK);
	game->Fill(x + 2, y + 3, x + 2, y + 3, L' ', COLOUR::BG_BLUE);
	game->Fill(x + 5, y + 3, x + 5, y + 3, L' ', COLOUR::BG_BLUE);
}
void StateDead::DrawHappyFrog(int x, int y)
{
	game->Fill(x + 1, y, x + 2, y, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 5, y, x + 6, y, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x, y + 1, x, y + 2, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 3, y + 1, x + 4, y + 2, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 7, y + 1, x + 7, y + 2, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 1, y + 3, x + 6, y + 3, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 2, y + 4, x + 5, y + 4, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 1, y + 5, x + 6, y + 6, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x, y + 7, x + 2, y + 7, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 5, y + 7, x + 7, y + 7, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 3, y + 4, x + 4, y + 4, L' ', COLOUR::BG_RED);
	game->Fill(x + 2, y + 5, x + 5, y + 6, L' ', COLOUR::BG_GREEN);
	game->Fill(x + 3, y + 6, x + 4, y + 6, L' ', COLOUR::BG_DARK_GREEN);
	game->Fill(x + 2, y + 2, x + 2, y + 2, L' ', COLOUR::BG_BLACK);
	game->Fill(x + 5, y + 2, x + 5, y + 2, L' ', COLOUR::BG_BLACK);
	game->Fill(x + 1, y + 3, x + 1, y + 3, L' ', COLOUR::BG_RED);
	game->Fill(x + 6, y + 3, x + 6, y + 3, L' ', COLOUR::BG_RED);
}
void StateDead::DrawDeadBoard()
{
	//WHITE BOARD
	int x = Ambulance->GetX() + 10;
	int y = Ambulance->GetY() - 44 - 2;
	if (x > game->GetGameWidth() - 55)
		x = game->GetGameWidth() / 2 - 15;
	if (y < 0)
		y = game->GetGameHeight() / 2 - 20;
	game->Fill(x + 8, y + 4, x + 64 - 1, y + 36, L' ', COLOUR::BG_WHITE);
	game->Fill(x + 4, y + 8, x + 12, y + 32, L' ', COLOUR::BG_WHITE);
	game->Fill(x + 64 - 1, y + 8, x + 68 - 1, y + 32, L' ', COLOUR::BG_WHITE);
	game->Fill(x - 1, y + 44, x, y + 45, L' ', COLOUR::BG_WHITE);
	game->Fill(x + 1, y + 41, x + 3, y + 43, L' ', COLOUR::BG_WHITE);
	game->Fill(x + 4, y + 37, x + 7, y + 40, L' ', COLOUR::BG_WHITE);

	//OPTION
	this->string2Pixel(L"DO YOU WANT", x + 8, y + 8, COLOUR::FG_BLACK, COLOUR::BG_WHITE);
	this->string2Pixel(L"TO SAVE IT", x + 10, y + 12, COLOUR::FG_BLACK, COLOUR::BG_WHITE);
	this->string2Pixel(L"YES", x + 8, y + 20, COLOUR::BG_BLACK, COLOUR::BG_WHITE);
	this->string2Pixel(L"NO", x + 8, y + 28, COLOUR::FG_BLACK, COLOUR::BG_WHITE);

	switch (optionIndex) 
	{
	case 0:
	{
		DrawHappyFrog(x + 36, y + 17);
		break;
	}
	case 1:
	{
		DrawCryFrog(x + 36, y + 25);
		break;
	}
	}
}
bool StateDead::OnStateExit()
{
	return true;
}