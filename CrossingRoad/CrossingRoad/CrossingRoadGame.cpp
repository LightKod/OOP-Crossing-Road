#pragma once
#include "CrossingRoadGame.h"
#include "Tile.h"
#include "Player.h"
int optionIndex = 0;
static Tile tile;
Player* pPlayer = nullptr;

#define VK_A 0x41
#define VK_D 0x44
#define VK_S 0x53
#define VK_W 0x57

static Tile tile,tile1[56];

bool CrossingRoadGame::OnUserCreate()
{
	SetStateMenu();
	pPlayer = new Player();

	return true;
}

bool CrossingRoadGame::OnUserUpdate(float fElapsedTime)
{

	switch (gameState) {
	case STATE_MENU:
		return MenuHandler(fElapsedTime);
	case STATE_PLAY:
		return GameHandler(fElapsedTime);
	case STATE_LOADGAME:
		return LoadHandler(fElapsedTime);
	case STATE_SETTING:
		return SettingHandler(fElapsedTime);
	case STATE_LEADERBOARD:
		return LeaderboardHandler (fElapsedTime);
	case STATE_CREDIT:
		return CreditHandler(fElapsedTime);
	case STATE_EXIT:
		return ExitHandler(fElapsedTime);
	default:
		return true;
	}

	//pPlayer->Draw();


	return 1;
}

void CrossingRoadGame::UpdateCollisionMatrix() {
	ClearCollsionMatrix();
	tile.SetCollisionMatrix(*this);
	//THEM MAY CAI SET COLLSION CUA MAY CAI OBJECT VAO
}

void CrossingRoadGame::UpdateGameScreen() {
	DrawGame();
	
	//THEM MAY CAI DRAW CUA MAY CAI OBJECT VAO
	pPlayer->Draw(*this);
}


void CrossingRoadGame::UpdateGameState(float fElapsedTime) {
	Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', COLOUR::BG_BLACK);
	/*tile1[0].Update1(*this, fElapsedTime);
	tile1[1].Update2(*this, fElapsedTime);*/
	for (int i = 0; i < 56; i++)
	{
		if (i % 2 == 0)
			tile1[i].Update1(*this, fElapsedTime);
		else tile1[i].Update2(*this, fElapsedTime);
	}
	//THEM MAY CAI UPDATE CUA MAY CAI OBJECT VAO
	if (m_keys[VK_W].bReleased) pPlayer->MoveUp(*this);
	if (m_keys[VK_S].bReleased) pPlayer->MoveDown(*this);
	if (m_keys[VK_A].bReleased) pPlayer->MoveLeft(*this);
	if (m_keys[VK_D].bReleased) pPlayer->MoveRight(*this);
}


//Handler

void CrossingRoadGame::SetStateMenu() {
	gameState = GameState::STATE_MENU;
	//VIET THEM BEN DUOI
	DrawMainMenu(optionIndex);
}
void CrossingRoadGame::SetStateNewGame() {
	gameState = GameState::STATE_PLAY;
	//VIET THEM BEN DUOI
	DrawGame();

	//Khoi tao may cai tile

	tile = { 8,8,16,16 };

	int h = 0;
	/*tile1[0] = { 0,64,8,8 };
	tile1[1] = { 8,64,8,8 };*/
	for(int f=0;f<=1;f++)
		for (int i = 0; i < 14; i++)
		{
			tile1[h] = { i * 8,32 + f * 8,8,8 };
			h++;
		}
	for (int f = 0; f <= 1; f++)
		for (int i = 0; i < 14; i++)
		{
			tile1[h] = { i * 8,64 + f * 8,8,8 };
			h++;
		}


}
void CrossingRoadGame::SetStateLoadGame() {
	gameState = GameState::STATE_LOADGAME;
	//VIET THEM BEN DUOI
	DrawLoadGame();
}
void CrossingRoadGame::SetStateSetting() {
	gameState = GameState::STATE_SETTING;
	//VIET THEM BEN DUOI
	DrawSetting();
}
void CrossingRoadGame::SetStateLeaderBoard() {
	gameState = GameState::STATE_LEADERBOARD;
	//VIET THEM BEN DUOI
	DrawLeaderboard();
}
void CrossingRoadGame::SetStateCredit() {
	gameState = GameState::STATE_CREDIT;
	//VIET THEM BEN DUOI
	DrawCredit();
}
void CrossingRoadGame::SetStateExit() {
	gameState = STATE_EXIT;
}

bool CrossingRoadGame::GameHandler(float fElapsedTime) {
	//VIET THEM BEN DUOI
	UpdateGameState(fElapsedTime);
	UpdateCollisionMatrix();
	UpdateGameScreen();
	return true;
}
bool CrossingRoadGame::MenuHandler(float fElapsedTime) {
	static float deltaTime = 0;
	static bool down = false;
	deltaTime += fElapsedTime;
	if(deltaTime > .5){
		deltaTime = 0;
		if (down)
			DrawMainMenu(optionIndex, 0, 0);
		else
			DrawMainMenu(optionIndex, 1, 0);
		down = !down;
	}

	if (m_keys[VK_UP].bReleased) {
		optionIndex--;
		if (optionIndex < 0) {
			optionIndex = 5;
		}
		if (down)
			DrawMainMenu(optionIndex, 0, 0);
		else
			DrawMainMenu(optionIndex, 1, 0);
	}
	if (m_keys[VK_DOWN].bReleased) {
		optionIndex++;
		if (optionIndex >= 6) {
			optionIndex = 0;
		}
		if (down)
			DrawMainMenu(optionIndex, 0, 0);
		else
			DrawMainMenu(optionIndex, 1, 0);
	}

	if (m_keys[VK_SPACE].bReleased) {
		switch (optionIndex)
		{
		case 0:
			SetStateNewGame();
			break;
		case 1:
			SetStateLoadGame();
			break;
		case 2:
			SetStateLeaderBoard();
			break;
		case 3:
			SetStateSetting();
			break;
		case 4:
			SetStateCredit();
			break;
		case 5:
			SetStateExit();
			break;
		default:
			SetStateNewGame();
			break;
		}
		return true;
	}
}
bool CrossingRoadGame::LoadHandler(float fElapsedTime) {
	if (m_keys[VK_ESCAPE].bReleased) {
		SetStateMenu();
	}
	return true;
}
bool CrossingRoadGame::LeaderboardHandler(float fElapsedTime) {
	if (m_keys[VK_ESCAPE].bReleased) {
		SetStateMenu();
	}
	return true;
}
bool CrossingRoadGame::CreditHandler(float fElapsedTime) {
	if (m_keys[VK_ESCAPE].bReleased) {
		SetStateMenu();
	}
	return true;
}
bool CrossingRoadGame::SettingHandler(float fElapsedTime) {
	if (m_keys[VK_ESCAPE].bReleased) {
		SetStateMenu();
	}
	return true;
}
bool CrossingRoadGame::ExitHandler(float fElapsedTime) {
	return false;
}



/// <summary>
/// DRAWERS
/// </summary>
void CrossingRoadGame::DrawMainMenu(int optionIndex,int titleInnerOfset, int titleOuterOfset) {
	Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', COLOUR::BG_BLUE);
	DrawMenuTitle(titleInnerOfset, titleOuterOfset);

	DrawMenuOptions();
	UpdateMousePosition(optionIndex);
	

	
}
void CrossingRoadGame::DrawMenuOptions() {
	DrawString(56, 35, L"▒█▄░▒█ ▒█▀▀▀ ▒█░░▒█    ▒█▀▀█ ░█▀▀█ ▒█▀▄▀█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	DrawString(56, 36, L"▒█▒█▒█ ▒█▀▀▀ ▒█▒█▒█    ▒█░▄▄ ▒█▄▄█ ▒█▒█▒█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	DrawString(56, 37, L"▒█░░▀█ ▒█▄▄▄ ▒█▄▀▄█    ▒█▄▄█ ▒█░▒█ ▒█░░▒█ ▒█▄▄▄", BG_BLACK + BG_BLUE);

	DrawString(44 + 16, 42, L"▒█▀▀█ ▒█▀▀▀ ▒█▀▀▀█ ▒█░▒█ ▒█▀▄▀█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	DrawString(44 + 16, 43, L"▒█▄▄▀ ▒█▀▀▀ ░▀▀▀▄▄ ▒█░▒█ ▒█▒█▒█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	DrawString(44 + 16, 44, L"▒█░▒█ ▒█▄▄▄ ▒█▄▄▄█ ░▀▄▄▀ ▒█░░▒█ ▒█▄▄▄", BG_BLACK + BG_BLUE);

	DrawString(32 + 16, 49, L"▒█░░░ ▒█▀▀▀ ░█▀▀█ ▒█▀▀▄ ▒█▀▀▀ ▒█▀▀█ ▒█▀▀█ ▒█▀▀▀█ ░█▀▀█ ▒█▀▀█ ▒█▀▀▄", BG_BLACK + BG_BLUE);
	DrawString(32 + 16, 50, L"▒█░░░ ▒█▀▀▀ ▒█▄▄█ ▒█░▒█ ▒█▀▀▀ ▒█▄▄▀ ▒█▀▀▄ ▒█░░▒█ ▒█▄▄█ ▒█▄▄▀ ▒█░▒█░", BG_BLACK + BG_BLUE);
	DrawString(32 + 16, 51, L"▒█▄▄█ ▒█▄▄▄ ▒█░▒█ ▒█▄▄▀ ▒█▄▄▄ ▒█░▒█ ▒█▄▄█ ▒█▄▄▄█ ▒█░▒█ ▒█░▒█ ▒█▄▄▀░", BG_BLACK + BG_BLUE);

	DrawString(42 + 16, 56, L"▒█▀▀▀█ ▒█▀▀▀ ▀▀█▀▀ ▀▀█▀▀ ▀█▀ ▒█▄░▒█ ▒█▀▀█", BG_BLACK + BG_BLUE);
	DrawString(42 + 16, 57, L"░▀▀▀▄▄ ▒█▀▀▀ ░▒█░░ ░▒█░░ ▒█░ ▒█▒█▒█ ▒█░▄▄", BG_BLACK + BG_BLUE);
	DrawString(42 + 16, 58, L"▒█▄▄▄█ ▒█▄▄▄ ░▒█░░ ░▒█░░ ▄█▄ ▒█░░▀█ ▒█▄▄█", BG_BLACK + BG_BLUE);

	DrawString(46 + 16, 63, L"▒█▀▀█ ▒█▀▀█ ▒█▀▀▀ ▒█▀▀▄ ▀█▀ ▀▀█▀▀", BG_BLACK + BG_BLUE);
	DrawString(46 + 16, 64, L"▒█░░░ ▒█▄▄▀ ▒█▀▀▀ ▒█░▒█ ▒█░ ░▒█░░", BG_BLACK + BG_BLUE);
	DrawString(46 + 16, 65, L"▒█▄▄█ ▒█░▒█ ▒█▄▄▄ ▒█▄▄▀ ▄█▄ ░▒█░░", BG_BLACK + BG_BLUE);

	DrawString(52 + 16, 70, L"▒█▀▀▀ ▀▄▒▄▀ ▀█▀ ▀▀█▀▀", BG_BLACK + BG_BLUE);
	DrawString(52 + 16, 71, L"▒█▀▀▀ ░▒█░░ ▒█░ ░▒█░░", BG_BLACK + BG_BLUE);
	DrawString(52 + 16, 72, L"▒█▄▄▄ ▄▀▒▀▄ ▄█▄ ░▒█░░", BG_BLACK + BG_BLUE);
}
void CrossingRoadGame::UpdateMousePosition(int index) {
	int ofset = index * 7;
	Fill(36, 36 + ofset, 42, 36 + ofset, L' ', COLOUR::BG_BLACK);
	Fill(138, 36 + ofset, 144, 36 + ofset, L' ', COLOUR::BG_BLACK);
}
void CrossingRoadGame::DrawMenuTitle(int innerOfset, int outerOfset) {
	//Inner
	//C
	int xOfset = 16;
	Fill(5 + xOfset, 12 + innerOfset, 7 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(4 + xOfset, 13 + innerOfset, 4 + xOfset, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(8 + xOfset, 12 + innerOfset, 11 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(9 + xOfset, 13 + innerOfset, 12 + xOfset, 13 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(8 + xOfset, 17 + innerOfset, 11 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(9 + xOfset, 16 + innerOfset, 12 + xOfset, 16 + innerOfset, L' ', COLOUR::BG_WHITE);

	//R
	Fill(14 + xOfset, 12 + innerOfset, 17 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(19 + xOfset, 12 + innerOfset, 21 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(22 + xOfset, 14 + innerOfset, 22 + xOfset, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(22 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(18 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(18 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);

	//O
	Fill(24 + xOfset, 13 + innerOfset, 27 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(29 + xOfset, 13 + innerOfset, 32 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(25 + xOfset, 12 + innerOfset, 31 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(25 + xOfset, 18 + innerOfset, 31 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);

	//S
	Fill(35 + xOfset, 12 + innerOfset, 42 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(34 + xOfset, 13 + innerOfset, 37 + xOfset, 14 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(35 + xOfset, 16 + innerOfset, 36 + xOfset, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(35 + xOfset, 15 + innerOfset, 41 + xOfset, 15 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(39 + xOfset, 16 + innerOfset, 42 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(39 + xOfset, 16 + innerOfset, 42 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(34 + xOfset, 18 + innerOfset, 41 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);

	//S
	Fill(35 + 10 + xOfset, 12 + innerOfset, 42 + 10 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(34 + 10 + xOfset, 13 + innerOfset, 37 + 10 + xOfset, 14 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(35 + 10 + xOfset, 16 + innerOfset, 36 + 10 + xOfset, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(35 + 10 + xOfset, 15 + innerOfset, 41 + 10 + xOfset, 15 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(39 + 10 + xOfset, 16 + innerOfset, 42 + 10 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(39 + 10 + xOfset, 16 + innerOfset, 42 + 10 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(34 + 10 + xOfset, 18 + innerOfset, 41 + 10 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);

	//I
	Fill(54 + xOfset, 12 + innerOfset, 57 + xOfset, 18, L' ', COLOUR::BG_WHITE);

	//N
	Fill(59 + xOfset, 12 + innerOfset, 61 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(62 + xOfset, 13 + innerOfset, 62 + xOfset, 15 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(63 + xOfset, 15 + innerOfset, 63 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(64 + xOfset, 12 + innerOfset, 66 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);


	//G
	Fill(70 + xOfset, 12 + innerOfset, 76 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(69 + xOfset, 13 + innerOfset, 72 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(70 + xOfset, 18 + innerOfset, 76 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(75 + xOfset, 15 + innerOfset, 77 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(74 + xOfset, 15 + innerOfset, L' ', COLOUR::BG_WHITE);

	//R
	Fill(14 + 71 + xOfset, 12 + innerOfset, 17 + 71 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(19 + 71 + xOfset, 12 + innerOfset, 21 + 71 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(22 + 71 + xOfset, 14 + innerOfset, 22 + 71 + xOfset, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(22 + 71 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(18 + 71 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(18 + 71 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);

	//O
	Fill(24 + 71 + xOfset, 13 + innerOfset, 27 + 71 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(29 + 71 + xOfset, 13 + innerOfset, 32 + 71 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(25 + 71 + xOfset, 12 + innerOfset, 31 + 71 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(25 + 71 + xOfset, 18 + innerOfset, 31 + 71 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);

	//A
	Fill(105 + xOfset, 13 + innerOfset, 108 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(110 + xOfset, 13 + innerOfset, 113 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(106 + xOfset, 12 + innerOfset, 112 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(109 + xOfset, 16 + innerOfset, L' ', COLOUR::BG_WHITE);

	//D
	Fill(115 + xOfset, 12 + innerOfset, 118 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(119 + xOfset, 12 + innerOfset, 122 + xOfset, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(119 + xOfset, 18 + innerOfset, 122 + xOfset, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(120 + xOfset, 13 + innerOfset, 123 + xOfset, 17 + innerOfset, L' ', COLOUR::BG_WHITE);

	//Outline
	//C
	Fill(4 + xOfset, 18 + outerOfset, 4 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(5 + xOfset, 20 + outerOfset, 12 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(12 + xOfset, 19 + outerOfset, 13 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(13 + xOfset, 14 + outerOfset, 13 + xOfset, 18 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(8 + xOfset, 14 + outerOfset, 8 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);

	//R
	Fill(14 + xOfset, 20 + outerOfset, 23 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(23 + xOfset, 14 + outerOfset, 23 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(18 + xOfset, 14 + outerOfset, 18 + xOfset, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(18 + xOfset, 14 + outerOfset, 18 + xOfset, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(22 + xOfset, 13 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(22 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(24 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);

	//0
	Fill(25 + xOfset, 20 + outerOfset, 32 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(32 + xOfset, 19 + outerOfset, 33 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(33 + xOfset, 14 + outerOfset, 33 + xOfset, 18 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(28 + xOfset, 14 + outerOfset, 28 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);

	//S
	Draw(34 + xOfset, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(43 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(42 + xOfset, 15 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(35 + xOfset, 17 + outerOfset, 35 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(34 + xOfset, 20 + outerOfset, 42 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(42 + xOfset, 18 + outerOfset, 43 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(43 + xOfset, 13 + outerOfset, 43 + xOfset, 15 + outerOfset, L' ', COLOUR::BG_BLACK);

	//S
	Draw(34 + 10 + xOfset, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(43 + 10 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(42 + 10 + xOfset, 15 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(35 + 10 + xOfset, 17 + outerOfset, 35 + 10 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(34 + 10 + xOfset, 20 + outerOfset, 42 + 10 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(42 + 10 + xOfset, 18 + outerOfset, 43 + 10 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(43 + 10 + xOfset, 13 + outerOfset, 43 + 10 + xOfset, 15 + outerOfset, L' ', COLOUR::BG_BLACK);

	//ING
	Fill(54 + xOfset, 20 + outerOfset, 62 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(58 + xOfset, 13 + outerOfset, 58 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(62 + xOfset, 17 + outerOfset, 62 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(63 + xOfset, 19 + outerOfset, 64 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(65 + xOfset, 20 + outerOfset, 68 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(68 + xOfset, 13 + outerOfset, 68 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(70 + xOfset, 20 + outerOfset, 77 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(77 + xOfset, 19 + outerOfset, 78 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(78 + xOfset, 15 + outerOfset, 78 + xOfset, 18 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(77 + xOfset, 13 + outerOfset, 77 + xOfset, 14 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(73 + xOfset, 15 + outerOfset, 73 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(69 + xOfset, 19 + outerOfset, 69 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);

	//R
	Fill(14 + xOfset + 71, 20 + outerOfset, 23 + 71 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(23 + xOfset + 71, 14 + outerOfset, 23 + 71 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(18 + xOfset + 71, 14 + outerOfset, 18 + 71 + xOfset, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(18 + xOfset + 71, 14 + outerOfset, 18 + 71 + xOfset, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(22 + xOfset + 71, 13 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(22 + xOfset + 71, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(24 + xOfset + 71, 19 + outerOfset, L' ', COLOUR::BG_BLACK);

	//0 
	Fill(25 + xOfset + 71, 20 + outerOfset, 32 + 71 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(32 + xOfset + 71, 19 + outerOfset, 33 + 71 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(33 + xOfset + 71, 14 + outerOfset, 33 + 71 + xOfset, 18 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(28 + xOfset + 71, 14 + outerOfset, 28 + 71 + xOfset, 17 + outerOfset, L' ', COLOUR::BG_BLACK);

	//AD
	Fill(105 + xOfset, 20 + outerOfset, 122 + xOfset, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(109 + xOfset, 18 + outerOfset, 109 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(109 + xOfset, 14 + outerOfset, 109 + xOfset, 15 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(114 + xOfset, 14 + outerOfset, 114 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(122 + xOfset, 19 + outerOfset, 123 + xOfset, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(123 + xOfset, 18 + outerOfset, 123 + xOfset, 18 + outerOfset, L' ', COLOUR::BG_BLACK);

}



void CrossingRoadGame::DrawGame() {
	//DrawString(5, 5, L"GAME SCREEN", BG_BLACK + BG_BLUE);
	//LANE XE
	//6,1 LA DIEM XUAT PHAT VA DIEM DUNG:0
	//2,4 LA LANE XE:1
	//3,5 LA LANE NUOC:2
	//Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', COLOUR::BG_BLACK);
	//LANE START VA END

	Fill(0, 0, m_nScreenWidth - 49, 15, L' ', COLOUR::BG_BLACK);
	Fill(0, m_nScreenHeight - 15, m_nScreenWidth - 49, m_nScreenHeight, L' ', COLOUR::BG_BLACK);

	//LANE XE
	int f = 8;
	Fill(0, 16, m_nScreenWidth - 49, 16 + 2, L' ', COLOUR::BG_GREEN);
	Fill(0, 19, m_nScreenWidth - 49, 13 + 16, L' ', COLOUR::BG_GREY);
	Fill(0, 29, m_nScreenWidth - 49, 31, L' ', COLOUR::BG_GREEN);
	Fill(f, 30, f + 7, 30, L' ', COLOUR::BG_DARK_GREY);
	f += 32;
	Fill(f, 30, f + 7, 30, L' ', COLOUR::BG_DARK_GREY);
	f += 32;
	Fill(f, 30, f + 7, 30, L' ', COLOUR::BG_DARK_GREY);
	f += 32;
	Fill(f, 30, f + 7, 30, L' ', COLOUR::BG_DARK_GREY);
	f += 32;

	Fill(0, 48, m_nScreenWidth - 49, 50, L' ', COLOUR::BG_GREEN);
	f = 8;
	Fill(f, 49, f + 7, 49, L' ', COLOUR::BG_DARK_GREY);
	f += 32;
	Fill(f, 49, f + 7, 49, L' ', COLOUR::BG_DARK_GREY);
	f += 32;
	Fill(f, 49, f + 7, 49, L' ', COLOUR::BG_DARK_GREY);
	f += 32;
	Fill(f, 49, f + 7, 49, L' ', COLOUR::BG_DARK_GREY);
	f += 32;
	Fill(0, 51, m_nScreenWidth - 49, 44 + 16, L' ', COLOUR::BG_GREY);
	Fill(0, 61, m_nScreenWidth - 49, 60 + 3, L' ', COLOUR::BG_GREEN);
	f = 8;
	Fill(f, 62, f + 7, 62, L' ', COLOUR::BG_DARK_GREY);
	f += 32;
	Fill(f, 62, f + 7, 62, L' ', COLOUR::BG_DARK_GREY);
	f += 32;
	Fill(f, 62, f + 7, 62, L' ', COLOUR::BG_DARK_GREY);
	f += 32;
	Fill(f, 62, f + 7, 62, L' ', COLOUR::BG_DARK_GREY);
	f += 32;
}
void CrossingRoadGame::DrawLoadGame() {
	Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', COLOUR::BG_BLUE);
	DrawString(5, 5, L"LOAD SCREEN", BG_BLACK + BG_BLUE);
}
void CrossingRoadGame::DrawLeaderboard() {
	Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', COLOUR::BG_BLUE);
	DrawString(5, 5, L"LEADERBOARD SCREEN", BG_BLACK + BG_BLUE);
}
void CrossingRoadGame::DrawSetting() {
	Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', COLOUR::BG_BLUE);
	DrawString(5, 5, L"SETTING SCREEN", BG_BLACK + BG_BLUE);
}
void CrossingRoadGame::DrawCredit() {
	Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', COLOUR::BG_BLUE);
	DrawString(5, 5, L"CREDIT SCREEN", BG_BLACK + BG_BLUE);
}