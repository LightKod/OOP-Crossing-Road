#include "StateMenu.h"
#include "StatePlay.h"

bool StateMenu::Update(float fElapsedTime) {
	static int optionIndex = 0;
	static float deltaTime = 0;
	deltaTime += fElapsedTime;
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

	if (game->GetKey(VK_SPACE).bReleased) {
		switch (optionIndex)
		{
		case 0:
			game->SetState(new StatePlay(game));
;			break;
		case 1:
			//SetStateLoadGame();
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
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);
	DrawMenuTitle(titleInnerOfset, titleOuterOfset);

	DrawMenuOptions();
	UpdateMousePosition(optionIndex);



}
void StateMenu::DrawMenuOptions() {
	game->DrawString(56, 35, L"▒█▄░▒█ ▒█▀▀▀ ▒█░░▒█    ▒█▀▀█ ░█▀▀█ ▒█▀▄▀█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	game->DrawString(56, 36, L"▒█▒█▒█ ▒█▀▀▀ ▒█▒█▒█    ▒█░▄▄ ▒█▄▄█ ▒█▒█▒█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	game->DrawString(56, 37, L"▒█░░▀█ ▒█▄▄▄ ▒█▄▀▄█    ▒█▄▄█ ▒█░▒█ ▒█░░▒█ ▒█▄▄▄", BG_BLACK + BG_BLUE);
	game->DrawString(44 + 16, 42, L"▒█▀▀█ ▒█▀▀▀ ▒█▀▀▀█ ▒█░▒█ ▒█▀▄▀█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	game->DrawString(44 + 16, 43, L"▒█▄▄▀ ▒█▀▀▀ ░▀▀▀▄▄ ▒█░▒█ ▒█▒█▒█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	game->DrawString(44 + 16, 44, L"▒█░▒█ ▒█▄▄▄ ▒█▄▄▄█ ░▀▄▄▀ ▒█░░▒█ ▒█▄▄▄", BG_BLACK + BG_BLUE);
	game->DrawString(32 + 16, 49, L"▒█░░░ ▒█▀▀▀ ░█▀▀█ ▒█▀▀▄ ▒█▀▀▀ ▒█▀▀█ ▒█▀▀█ ▒█▀▀▀█ ░█▀▀█ ▒█▀▀█ ▒█▀▀▄", BG_BLACK + BG_BLUE);
	game->DrawString(32 + 16, 50, L"▒█░░░ ▒█▀▀▀ ▒█▄▄█ ▒█░▒█ ▒█▀▀▀ ▒█▄▄▀ ▒█▀▀▄ ▒█░░▒█ ▒█▄▄█ ▒█▄▄▀ ▒█░▒█░", BG_BLACK + BG_BLUE);
	game->DrawString(32 + 16, 51, L"▒█▄▄█ ▒█▄▄▄ ▒█░▒█ ▒█▄▄▀ ▒█▄▄▄ ▒█░▒█ ▒█▄▄█ ▒█▄▄▄█ ▒█░▒█ ▒█░▒█ ▒█▄▄▀░", BG_BLACK + BG_BLUE);
	game->DrawString(42 + 16, 56, L"▒█▀▀▀█ ▒█▀▀▀ ▀▀█▀▀ ▀▀█▀▀ ▀█▀ ▒█▄░▒█ ▒█▀▀█", BG_BLACK + BG_BLUE);
	game->DrawString(42 + 16, 57, L"░▀▀▀▄▄ ▒█▀▀▀ ░▒█░░ ░▒█░░ ▒█░ ▒█▒█▒█ ▒█░▄▄", BG_BLACK + BG_BLUE);
	game->DrawString(42 + 16, 58, L"▒█▄▄▄█ ▒█▄▄▄ ░▒█░░ ░▒█░░ ▄█▄ ▒█░░▀█ ▒█▄▄█", BG_BLACK + BG_BLUE);
	game->DrawString(46 + 16, 63, L"▒█▀▀█ ▒█▀▀█ ▒█▀▀▀ ▒█▀▀▄ ▀█▀ ▀▀█▀▀", BG_BLACK + BG_BLUE);
	game->DrawString(46 + 16, 64, L"▒█░░░ ▒█▄▄▀ ▒█▀▀▀ ▒█░▒█ ▒█░ ░▒█░░", BG_BLACK + BG_BLUE);
	game->DrawString(46 + 16, 65, L"▒█▄▄█ ▒█░▒█ ▒█▄▄▄ ▒█▄▄▀ ▄█▄ ░▒█░░", BG_BLACK + BG_BLUE);
	game->DrawString(52 + 16, 70, L"▒█▀▀▀ ▀▄▒▄▀ ▀█▀ ▀▀█▀▀", BG_BLACK + BG_BLUE);
	game->DrawString(52 + 16, 71, L"▒█▀▀▀ ░▒█░░ ▒█░ ░▒█░░", BG_BLACK + BG_BLUE);
	game->DrawString(52 + 16, 72, L"▒█▄▄▄ ▄▀▒▀▄ ▄█▄ ░▒█░░", BG_BLACK + BG_BLUE);
}
void StateMenu::UpdateMousePosition(int index) {
	int ofset = index * 7;
	game->Fill(36, 36 + ofset, 42, 36 + ofset, L' ', COLOUR::BG_BLACK);
	game->Fill(138, 36 + ofset, 144, 36 + ofset, L' ', COLOUR::BG_BLACK);
}
void StateMenu::DrawMenuTitle(int innerOfset, int outerOfset) {
	//Inner
	//C
	int xOfset = 16;
	game->Fill(5 + xOfset, 12 + innerOfset, 7 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(4 + xOfset, 13 + innerOfset, 4 + xOfset, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(8 + xOfset, 12 + innerOfset, 11 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(9 + xOfset, 13 + innerOfset, 12 + xOfset, 13 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(8 + xOfset, 17 + innerOfset, 11 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(9 + xOfset, 16 + innerOfset, 12 + xOfset, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	//->
	game->Fill(14 + xOfset, 12 + innerOfset, 17 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(19 + xOfset, 12 + innerOfset, 21 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(22 + xOfset, 14 + innerOfset, 22 + xOfset, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Draw(22 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Draw(18 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Draw(18 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	//->
	game->Fill(24 + xOfset, 13 + innerOfset, 27 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(29 + xOfset, 13 + innerOfset, 32 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(25 + xOfset, 12 + innerOfset, 31 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(25 + xOfset, 18 + innerOfset, 31 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	//->
	game->Fill(35 + xOfset, 12 + innerOfset, 42 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(34 + xOfset, 13 + innerOfset, 37 + xOfset, 14 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(35 + xOfset, 16 + innerOfset, 36 + xOfset, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(35 + xOfset, 15 + innerOfset, 41 + xOfset, 15 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(39 + xOfset, 16 + innerOfset, 42 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(39 + xOfset, 16 + innerOfset, 42 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(34 + xOfset, 18 + innerOfset, 41 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	//->
	game->Fill(35 + 10 + xOfset, 12 + innerOfset, 42 + 10 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(34 + 10 + xOfset, 13 + innerOfset, 37 + 10 + xOfset, 14 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(35 + 10 + xOfset, 16 + innerOfset, 36 + 10 + xOfset, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(35 + 10 + xOfset, 15 + innerOfset, 41 + 10 + xOfset, 15 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(39 + 10 + xOfset, 16 + innerOfset, 42 + 10 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(39 + 10 + xOfset, 16 + innerOfset, 42 + 10 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(34 + 10 + xOfset, 18 + innerOfset, 41 + 10 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	//->
	game->Fill(54 + xOfset, 12 + innerOfset, 57 + xOfset, 18, L' ', COLOUR::BG_WHITE); //N
	game->Fill(59 + xOfset, 12 + innerOfset, 61 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(62 + xOfset, 13 + innerOfset, 62 + xOfset, 15 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(63 + xOfset, 15 + innerOfset, 63 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(64 + xOfset, 12 + innerOfset, 66 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	//->
	game->Fill(70 + xOfset, 12 + innerOfset, 76 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(69 + xOfset, 13 + innerOfset, 72 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(70 + xOfset, 18 + innerOfset, 76 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(75 + xOfset, 15 + innerOfset, 77 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Draw(74 + xOfset, 15 + innerOfset, L' ', COLOUR::BG_WHITE);
	//->
	game->Fill(14 + 71 + xOfset, 12 + innerOfset, 17 + 71 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(19 + 71 + xOfset, 12 + innerOfset, 21 + 71 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(22 + 71 + xOfset, 14 + innerOfset, 22 + 71 + xOfset, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Draw(22 + 71 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Draw(18 + 71 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Draw(18 + 71 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	//->
	game->Fill(24 + 71 + xOfset, 13 + innerOfset, 27 + 71 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(29 + 71 + xOfset, 13 + innerOfset, 32 + 71 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(25 + 71 + xOfset, 12 + innerOfset, 31 + 71 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(25 + 71 + xOfset, 18 + innerOfset, 31 + 71 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	//->
	game->Fill(105 + xOfset, 13 + innerOfset, 108 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(110 + xOfset, 13 + innerOfset, 113 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(106 + xOfset, 12 + innerOfset, 112 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Draw(109 + xOfset, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	//->
	game->Fill(115 + xOfset, 12 + innerOfset, 118 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(119 + xOfset, 12 + innerOfset, 122 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(119 + xOfset, 18 + innerOfset, 122 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	game->Fill(120 + xOfset, 13 + innerOfset, 123 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	//Ou->line
	//->
	game->Fill(4 + xOfset, 18 + outerOfset, 4 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(5 + xOfset, 20 + outerOfset, 12 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(12 + xOfset, 19 + outerOfset, 13 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(13 + xOfset, 14 + outerOfset, 13 + xOfset, 18 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(8 + xOfset, 14 + outerOfset, 8 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	//->
	game->Fill(14 + xOfset, 20 + outerOfset, 23 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(23 + xOfset, 14 + outerOfset, 23 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(18 + xOfset, 14 + outerOfset, 18 + xOfset, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(18 + xOfset, 14 + outerOfset, 18 + xOfset, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Draw(22 + xOfset, 13 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Draw(22 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Draw(24 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	//->
	game->Fill(25 + xOfset, 20 + outerOfset, 32 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(32 + xOfset, 19 + outerOfset, 33 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(33 + xOfset, 14 + outerOfset, 33 + xOfset, 18 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(28 + xOfset, 14 + outerOfset, 28 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	//->
	game->Draw(34 + xOfset, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Draw(43 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Draw(42 + xOfset, 15 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(35 + xOfset, 17 + outerOfset, 35 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(34 + xOfset, 20 + outerOfset, 42 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(42 + xOfset, 18 + outerOfset, 43 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(43 + xOfset, 13 + outerOfset, 43 + xOfset, 15 + outerOfset, L' ', COLOUR::BG_BLACK);
	//->
	game->Draw(34 + 10 + xOfset, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Draw(43 + 10 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Draw(42 + 10 + xOfset, 15 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(35 + 10 + xOfset, 17 + outerOfset, 35 + 10 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(34 + 10 + xOfset, 20 + outerOfset, 42 + 10 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(42 + 10 + xOfset, 18 + outerOfset, 43 + 10 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(43 + 10 + xOfset, 13 + outerOfset, 43 + 10 + xOfset, 15 + outerOfset, L' ', COLOUR::BG_BLACK);
	//IN->
	game->Fill(54 + xOfset, 20 + outerOfset, 62 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(58 + xOfset, 13 + outerOfset, 58 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(62 + xOfset, 17 + outerOfset, 62 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(63 + xOfset, 19 + outerOfset, 64 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(65 + xOfset, 20 + outerOfset, 68 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(68 + xOfset, 13 + outerOfset, 68 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(70 + xOfset, 20 + outerOfset, 77 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(77 + xOfset, 19 + outerOfset, 78 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(78 + xOfset, 15 + outerOfset, 78 + xOfset, 18 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(77 + xOfset, 13 + outerOfset, 77 + xOfset, 14 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(73 + xOfset, 15 + outerOfset, 73 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(69 + xOfset, 19 + outerOfset, 69 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	//->
	game->Fill(14 + xOfset + 71, 20 + outerOfset, 23 + 71 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(23 + xOfset + 71, 14 + outerOfset, 23 + 71 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(18 + xOfset + 71, 14 + outerOfset, 18 + 71 + xOfset, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(18 + xOfset + 71, 14 + outerOfset, 18 + 71 + xOfset, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Draw(22 + xOfset + 71, 13 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Draw(22 + xOfset + 71, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Draw(24 + xOfset + 71, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	//0->
	game->Fill(25 + xOfset + 71, 20 + outerOfset, 32 + 71 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(32 + xOfset + 71, 19 + outerOfset, 33 + 71 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(33 + xOfset + 71, 14 + outerOfset, 33 + 71 + xOfset, 18 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(28 + xOfset + 71, 14 + outerOfset, 28 + 71 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	//A->
	game->Fill(105 + xOfset, 20 + outerOfset, 122 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(109 + xOfset, 18 + outerOfset, 109 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(109 + xOfset, 14 + outerOfset, 109 + xOfset, 15 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(114 + xOfset, 14 + outerOfset, 114 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(122 + xOfset, 19 + outerOfset, 123 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	game->Fill(123 + xOfset, 18 + outerOfset, 123 + xOfset, 18 + outerOfset, L' ', COLOUR::BG_BLACK);
}