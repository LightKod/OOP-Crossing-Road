#include "StateMenu.h"
#include "StatePlay.h"
#include "StateLoad.h"
#include "Menu.h"

Menu* p_Menu = nullptr;

bool StateMenu::Update(float fElapsedTime) {
	static int optionIndex = 0;
	static float deltaTime = 0;
	deltaTime += fElapsedTime;

	if (game->GetKey(VK_SPACE).bReleased) {
		p_Menu->SplashAnimation(game, optionIndex);

		switch (optionIndex)
		{
		case 0:
			game->SetState(new StatePlay(game));
;			break;
		case 1:
			//SetStateLoadGame();
			game->SetState(new StateLoad(game));
			break;
		case 2:
			//SetStateLeaderBoard();
			break;
		case 3:
			//SetStateSetting();
			break;
		case 4:
			//SetStateCredit();
			break;
		case 5:
			//SetStateExit();
			break;
		default:
			//SetStateNewGame();
			game->SetState(new StatePlay(game));
			break;
		}
		return true;
	}

	if (deltaTime > .5) {
		deltaTime = 0;
		if (down)
			DrawMainMenu(optionIndex, 0, 0);
		else
			DrawMainMenu(optionIndex, 1, 0);
		down = !down;
	}

	if (game->GetKey(VK_UP).bReleased) {
		optionIndex--;
		if (optionIndex < 0) {
			optionIndex = 5;
		}
		if (down)
			DrawMainMenu(optionIndex, 0, 0);
		else
			DrawMainMenu(optionIndex, 1, 0);
	}

	if (game->GetKey(VK_DOWN).bReleased) {
		optionIndex++;
		if (optionIndex >= 6) {
			optionIndex = 0;
		}
		if (down)
			DrawMainMenu(optionIndex, 0, 0);
		else
			DrawMainMenu(optionIndex, 1, 0);
	}

	if(optionIndex == 1)
		game->Draw(2, 2, L'1', FG_BLACK + BG_BLUE);
	else
		game->Draw(2, 2, L'0', FG_BLACK + BG_BLUE);

	return true;
}
bool StateMenu::OnStateEnter() {
	this->game = game;
	DrawMainMenu(0, 0 ,0);
	return true;
}
bool StateMenu::OnStateExit() {
	return true;
}

void StateMenu::DrawMainMenu(int optionIndex, int titleInnerOfset = 0, int titleOuterOfset = 0) {
	
	//DrawMenuTitle(titleInnerOfset, titleOuterOfset);

	p_Menu->UpdateMenuUI(game, optionIndex, titleInnerOfset, titleOuterOfset);
}

void StateMenu::DrawMenuOptions() {
	//game->DrawString(56, 35, L"▒█▄░▒█ ▒█▀▀▀ ▒█░░▒█    ▒█▀▀█ ░█▀▀█ ▒█▀▄▀█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	//game->DrawString(56, 36, L"▒█▒█▒█ ▒█▀▀▀ ▒█▒█▒█    ▒█░▄▄ ▒█▄▄█ ▒█▒█▒█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	//game->DrawString(56, 37, L"▒█░░▀█ ▒█▄▄▄ ▒█▄▀▄█    ▒█▄▄█ ▒█░▒█ ▒█░░▒█ ▒█▄▄▄", BG_BLACK + BG_BLUE);
	//game->DrawString(44 + 16, 42, L"▒█▀▀█ ▒█▀▀▀ ▒█▀▀▀█ ▒█░▒█ ▒█▀▄▀█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	//game->DrawString(44 + 16, 43, L"▒█▄▄▀ ▒█▀▀▀ ░▀▀▀▄▄ ▒█░▒█ ▒█▒█▒█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	//game->DrawString(44 + 16, 44, L"▒█░▒█ ▒█▄▄▄ ▒█▄▄▄█ ░▀▄▄▀ ▒█░░▒█ ▒█▄▄▄", BG_BLACK + BG_BLUE);
	//game->DrawString(32 + 16, 49, L"▒█░░░ ▒█▀▀▀ ░█▀▀█ ▒█▀▀▄ ▒█▀▀▀ ▒█▀▀█ ▒█▀▀█ ▒█▀▀▀█ ░█▀▀█ ▒█▀▀█ ▒█▀▀▄", BG_BLACK + BG_BLUE);
	//game->DrawString(32 + 16, 50, L"▒█░░░ ▒█▀▀▀ ▒█▄▄█ ▒█░▒█ ▒█▀▀▀ ▒█▄▄▀ ▒█▀▀▄ ▒█░░▒█ ▒█▄▄█ ▒█▄▄▀ ▒█░▒█░", BG_BLACK + BG_BLUE);
	//game->DrawString(32 + 16, 51, L"▒█▄▄█ ▒█▄▄▄ ▒█░▒█ ▒█▄▄▀ ▒█▄▄▄ ▒█░▒█ ▒█▄▄█ ▒█▄▄▄█ ▒█░▒█ ▒█░▒█ ▒█▄▄▀░", BG_BLACK + BG_BLUE);
	//game->DrawString(42 + 16, 56, L"▒█▀▀▀█ ▒█▀▀▀ ▀▀█▀▀ ▀▀█▀▀ ▀█▀ ▒█▄░▒█ ▒█▀▀█", BG_BLACK + BG_BLUE);
	//game->DrawString(42 + 16, 57, L"░▀▀▀▄▄ ▒█▀▀▀ ░▒█░░ ░▒█░░ ▒█░ ▒█▒█▒█ ▒█░▄▄", BG_BLACK + BG_BLUE);
	//game->DrawString(42 + 16, 58, L"▒█▄▄▄█ ▒█▄▄▄ ░▒█░░ ░▒█░░ ▄█▄ ▒█░░▀█ ▒█▄▄█", BG_BLACK + BG_BLUE);
	//game->DrawString(46 + 16, 63, L"▒█▀▀█ ▒█▀▀█ ▒█▀▀▀ ▒█▀▀▄ ▀█▀ ▀▀█▀▀", BG_BLACK + BG_BLUE);
	//game->DrawString(46 + 16, 64, L"▒█░░░ ▒█▄▄▀ ▒█▀▀▀ ▒█░▒█ ▒█░ ░▒█░░", BG_BLACK + BG_BLUE);
	//game->DrawString(46 + 16, 65, L"▒█▄▄█ ▒█░▒█ ▒█▄▄▄ ▒█▄▄▀ ▄█▄ ░▒█░░", BG_BLACK + BG_BLUE);
	//game->DrawString(52 + 16, 70, L"▒█▀▀▀ ▀▄▒▄▀ ▀█▀ ▀▀█▀▀", BG_BLACK + BG_BLUE);
	//game->DrawString(52 + 16, 71, L"▒█▀▀▀ ░▒█░░ ▒█░ ░▒█░░", BG_BLACK + BG_BLUE);
	//game->DrawString(52 + 16, 72, L"▒█▄▄▄ ▄▀▒▀▄ ▄█▄ ░▒█░░", BG_BLACK + BG_BLUE);
}
void StateMenu::UpdateMousePosition(int index) {

}
void StateMenu::DrawMenuTitle(int innerOfset, int outerOfset) {
	//static const int _deltaY = -10;
	////Inner
	////C
	//int xOfset = 16;
	//game->Fill(5 + xOfset, 12 + innerOfset + _deltaY, 7 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(4 + xOfset, 13 + innerOfset + _deltaY, 4 + xOfset, 16 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(8 + xOfset, 12 + innerOfset + _deltaY, 11 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(9 + xOfset, 13 + innerOfset + _deltaY, 12 + xOfset, 13 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(8 + xOfset, 17 + innerOfset + _deltaY, 11 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(9 + xOfset, 16 + innerOfset + _deltaY, 12 + xOfset, 16 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	////R
	//game->Fill(14 + xOfset, 12 + innerOfset + _deltaY, 17 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(19 + xOfset, 12 + innerOfset + _deltaY, 21 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(22 + xOfset, 14 + innerOfset + _deltaY, 22 + xOfset, 16 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Draw(22 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Draw(18 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Draw(18 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	////O
	//game->Fill(24 + xOfset, 13 + innerOfset + _deltaY, 27 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(29 + xOfset, 13 + innerOfset + _deltaY, 32 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(25 + xOfset, 12 + innerOfset + _deltaY, 31 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(25 + xOfset, 18 + innerOfset + _deltaY, 31 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	////S
	//game->Fill(35 + xOfset, 12 + innerOfset + _deltaY, 42 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(34 + xOfset, 13 + innerOfset + _deltaY, 37 + xOfset, 14 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(35 + xOfset, 16 + innerOfset + _deltaY, 36 + xOfset, 16 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(35 + xOfset, 15 + innerOfset + _deltaY, 41 + xOfset, 15 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(39 + xOfset, 16 + innerOfset + _deltaY, 42 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(39 + xOfset, 16 + innerOfset + _deltaY, 42 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(34 + xOfset, 18 + innerOfset + _deltaY, 41 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	////S
	//game->Fill(35 + 10 + xOfset, 12 + innerOfset + _deltaY, 42 + 10 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(34 + 10 + xOfset, 13 + innerOfset + _deltaY, 37 + 10 + xOfset, 14 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(35 + 10 + xOfset, 16 + innerOfset + _deltaY, 36 + 10 + xOfset, 16 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(35 + 10 + xOfset, 15 + innerOfset + _deltaY, 41 + 10 + xOfset, 15 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(39 + 10 + xOfset, 16 + innerOfset + _deltaY, 42 + 10 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(39 + 10 + xOfset, 16 + innerOfset + _deltaY, 42 + 10 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(34 + 10 + xOfset, 18 + innerOfset + _deltaY, 41 + 10 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	////I
	//game->Fill(54 + xOfset, 12 + innerOfset + _deltaY, 57 + xOfset, 18 + _deltaY, L' ', COLOUR::BG_WHITE);

	////N
	//game->Fill(59 + xOfset, 12 + innerOfset + _deltaY, 61 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(62 + xOfset, 13 + innerOfset + _deltaY, 62 + xOfset, 15 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(63 + xOfset, 15 + innerOfset + _deltaY, 63 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(64 + xOfset, 12 + innerOfset + _deltaY, 66 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);


	////G
	//game->Fill(70 + xOfset, 12 + innerOfset + _deltaY, 76 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(69 + xOfset, 13 + innerOfset + _deltaY, 72 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(70 + xOfset, 18 + innerOfset + _deltaY, 76 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(75 + xOfset, 15 + innerOfset + _deltaY, 77 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Draw(74 + xOfset, 15 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	////R
	//game->Fill(14 + 71 + xOfset, 12 + innerOfset + _deltaY, 17 + 71 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(19 + 71 + xOfset, 12 + innerOfset + _deltaY, 21 + 71 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(22 + 71 + xOfset, 14 + innerOfset + _deltaY, 22 + 71 + xOfset, 16 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Draw(22 + 71 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Draw(18 + 71 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Draw(18 + 71 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	////O
	//game->Fill(24 + 71 + xOfset, 13 + innerOfset + _deltaY, 27 + 71 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(29 + 71 + xOfset, 13 + innerOfset + _deltaY, 32 + 71 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(25 + 71 + xOfset, 12 + innerOfset + _deltaY, 31 + 71 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(25 + 71 + xOfset, 18 + innerOfset + _deltaY, 31 + 71 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	////A
	//game->Fill(105 + xOfset, 13 + innerOfset + _deltaY, 108 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(110 + xOfset, 13 + innerOfset + _deltaY, 113 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(106 + xOfset, 12 + innerOfset + _deltaY, 112 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Draw(109 + xOfset, 16 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	////D
	//game->Fill(115 + xOfset, 12 + innerOfset + _deltaY, 118 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(119 + xOfset, 12 + innerOfset + _deltaY, 122 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(119 + xOfset, 18 + innerOfset + _deltaY, 122 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	//game->Fill(120 + xOfset, 13 + innerOfset + _deltaY, 123 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	////Outline
	////C
	//game->Fill(4 + xOfset, 18 + outerOfset + _deltaY, 4 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(5 + xOfset, 20 + outerOfset + _deltaY, 12 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(12 + xOfset, 19 + outerOfset + _deltaY, 13 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(13 + xOfset, 14 + outerOfset + _deltaY, 13 + xOfset, 18 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(8 + xOfset, 14 + outerOfset + _deltaY, 8 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	////R
	//game->Fill(14 + xOfset, 20 + outerOfset + _deltaY, 23 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(23 + xOfset, 14 + outerOfset + _deltaY, 23 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(18 + xOfset, 14 + outerOfset + _deltaY, 18 + xOfset, 16 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(18 + xOfset, 14 + outerOfset + _deltaY, 18 + xOfset, 16 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Draw(22 + xOfset, 13 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Draw(22 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Draw(24 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	////0
	//game->Fill(25 + xOfset, 20 + outerOfset + _deltaY, 32 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(32 + xOfset, 19 + outerOfset + _deltaY, 33 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(33 + xOfset, 14 + outerOfset + _deltaY, 33 + xOfset, 18 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(28 + xOfset, 14 + outerOfset + _deltaY, 28 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	////S
	//game->Draw(34 + xOfset, 16 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Draw(43 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Draw(42 + xOfset, 15 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(35 + xOfset, 17 + outerOfset + _deltaY, 35 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(34 + xOfset, 20 + outerOfset + _deltaY, 42 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(42 + xOfset, 18 + outerOfset + _deltaY, 43 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(43 + xOfset, 13 + outerOfset + _deltaY, 43 + xOfset, 15 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	////S
	//game->Draw(34 + 10 + xOfset, 16 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Draw(43 + 10 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Draw(42 + 10 + xOfset, 15 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(35 + 10 + xOfset, 17 + outerOfset + _deltaY, 35 + 10 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(34 + 10 + xOfset, 20 + outerOfset + _deltaY, 42 + 10 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(42 + 10 + xOfset, 18 + outerOfset + _deltaY, 43 + 10 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(43 + 10 + xOfset, 13 + outerOfset + _deltaY, 43 + 10 + xOfset, 15 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	////ING
	//game->Fill(54 + xOfset, 20 + outerOfset + _deltaY, 62 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(58 + xOfset, 13 + outerOfset + _deltaY, 58 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(62 + xOfset, 17 + outerOfset + _deltaY, 62 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(63 + xOfset, 19 + outerOfset + _deltaY, 64 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(65 + xOfset, 20 + outerOfset + _deltaY, 68 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(68 + xOfset, 13 + outerOfset + _deltaY, 68 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(70 + xOfset, 20 + outerOfset + _deltaY, 77 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(77 + xOfset, 19 + outerOfset + _deltaY, 78 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(78 + xOfset, 15 + outerOfset + _deltaY, 78 + xOfset, 18 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(77 + xOfset, 13 + outerOfset + _deltaY, 77 + xOfset, 14 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(73 + xOfset, 15 + outerOfset + _deltaY, 73 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(69 + xOfset, 19 + outerOfset + _deltaY, 69 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	////R
	//game->Fill(14 + xOfset + 71, 20 + outerOfset + _deltaY, 23 + 71 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(23 + xOfset + 71, 14 + outerOfset + _deltaY, 23 + 71 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(18 + xOfset + 71, 14 + outerOfset + _deltaY, 18 + 71 + xOfset, 16 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(18 + xOfset + 71, 14 + outerOfset + _deltaY, 18 + 71 + xOfset, 16 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Draw(22 + xOfset + 71, 13 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Draw(22 + xOfset + 71, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Draw(24 + xOfset + 71, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	////0 
	//game->Fill(25 + xOfset + 71, 20 + outerOfset + _deltaY, 32 + 71 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(32 + xOfset + 71, 19 + outerOfset + _deltaY, 33 + 71 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(33 + xOfset + 71, 14 + outerOfset + _deltaY, 33 + 71 + xOfset, 18 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(28 + xOfset + 71, 14 + outerOfset + _deltaY, 28 + 71 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	////AD
	//game->Fill(105 + xOfset, 20 + outerOfset + _deltaY, 122 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(109 + xOfset, 18 + outerOfset + _deltaY, 109 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(109 + xOfset, 14 + outerOfset + _deltaY, 109 + xOfset, 15 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(114 + xOfset, 14 + outerOfset + _deltaY, 114 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(122 + xOfset, 19 + outerOfset + _deltaY, 123 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	//game->Fill(123 + xOfset, 18 + outerOfset + _deltaY, 123 + xOfset, 18 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
}


StateMenu::StateMenu(CrossingRoadGame* game) : State(game) {
	if (!p_Menu)
		p_Menu = new Menu(game);
};
StateMenu::~StateMenu() {
	if (p_Menu) {
		delete p_Menu;
		p_Menu = nullptr;
	}
}
