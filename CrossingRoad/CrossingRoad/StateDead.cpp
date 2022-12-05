#include "StateDead.h"
bool StateDead::OnStateEnter()
{
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);
	ambulance=new Ambulance(game, 0, pPlayer->GetY(), 0.01f);
	game->Fill(0, 0, 120, 96, L' ', COLOUR::BG_BLUE);
	pPlayer->Standing();
	ambulance->Draw();
	saveName = L"   ";

	optionIndex = 0;
	return true;
}
bool StateDead::Update(float fElapsedTime) {

	if (h == 0) {
		DrawDeadBoard(fElapsedTime);
		if (game->GetKey(VK_SPACE).bPressed) {
			switch (optionIndex) {
			case 0: {
				h++;
				DeadChoice = true;
				break;
			}
			case 1: {
				h++;
				DeadChoice = false;
				break;
			}
			}
		}
		if (game->GetKey(VK_W).bPressed) {
			optionIndex--;
			if (optionIndex < 0)
				optionIndex = 1;
		}
		if (game->GetKey(VK_S).bPressed) {
			optionIndex++;
			if (optionIndex >= 2)
				optionIndex = 0;
		}
	}
	else {
		DeadAnimation(fElapsedTime, DeadChoice);
	}



	return true;
}
void StateDead::DeadAnimation(float fElapsedTime,bool Option)
{
	if (ambulance->GetX() == game->GetGameWidth()-8) {
		if (Option) {
			time += fElapsedTime;
			if (time > 2.0f) {
				// Reset player's position 
				pPlayer->ResetPosition();

				game->SetState(new StatePlay(game));
			}
		}
		else {
			DrawDeadScreen();
			time += fElapsedTime;
			if (time > 2.0f)
				game->SetState(new StateMenu(game));
		}
	}
	else {
		game->Fill(0, 0, 120, 96, L' ', COLOUR::BG_BLUE);
		if (optionIndex != 2) {
			if (pPlayer->GetX() <= ambulance->GetX())
				if (Option);
				else pPlayer->Standing();
			else pPlayer->Standing();
			ambulance->Draw();
			ambulance->AmbulanceUpdate(fElapsedTime, true);
			if (Option)
			{
				if (ambulance->GetX() == pPlayer->GetX())
				{
					ambulance->AmbulanceUpdate(fElapsedTime, false);
					ambulance->AmbulanceUpdate(fElapsedTime, true);
				}
			}

		}
	}
}
void StateDead::DrawDeadScreen()
{
	game->Fill(0, 0, 160, 96, L' ', COLOUR::BG_BLACK);
	string2Pixel(L"REJECTED", 160 / 2 - 20, 96 / 2, COLOUR::FG_RED, COLOUR::BG_BLACK);
}
void StateDead::DrawDeadBoard(float fElapsedTime)
{
	//WHITE BOARD

	int x = ambulance->GetX() + 10;
	int y = ambulance->GetY() - 44 - 2;
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
	time += fElapsedTime;
	if (time > 0.5f)
	{
		switch (optionIndex)
		{
		case 0:
		{
			switch (m)
			{
			case 0:
				col = COLOUR::BG_BLACK;
				m = 1;
				break;
			case 1:
				col = COLOUR::BG_YELLOW;
				m = 0;
				break;
			}
			break;
		}
		case 1:
		{
			switch (m)
			{
			case 0:
				col = COLOUR::BG_BLACK;
				m = 1;
				break;
			case 1:
				col = COLOUR::BG_RED;
				m = 0;
				break;
			}
			break;
		}
		}
		time = 0;
	}
	//OPTION
	this->string2Pixel(L"DO YOU WANT", x + 8, y + 8, COLOUR::FG_BLACK, COLOUR::BG_WHITE);
	this->string2Pixel(L"TO SAVE IT", x + 10, y + 12, COLOUR::FG_BLACK, COLOUR::BG_WHITE);
	this->string2Pixel(L"Y TO PLAY", x + 8, y + 20, COLOUR::BG_BLACK, COLOUR::BG_WHITE);
	this->string2Pixel(L"N TO EXIT", x + 8, y + 28, COLOUR::FG_BLACK, COLOUR::BG_WHITE);
	switch (optionIndex)
	{
	case 0:
	{
		DrawOption(x + 64, y + 18, col);
		break;
	}
	case 1:
	{
		DrawOption(x + 64, y + 26, col);
		break;
	}
	}
}
void StateDead::DrawOption(int x, int y, short col)
{
	game->Fill(x -2, y, x -1, y + 1, L' ', col);
	game->Fill(x -9, y + 2, x -1, y + 3, L' ', col);
	game->Fill(x-5, y + 3, x, y + 5, L' ', col);
	game->Fill(x -4, y + 6, x -1, y + 6, L' ', col);
}
bool StateDead::OnStateExit()
{
	return true;
}