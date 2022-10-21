#pragma once
#include "CrossingRoadGame.h"
#include <iostream>

int optionIndex = 0;

bool CrossingRoadGame::OnUserCreate()
{
	SetStateMenu();
	return true;
}

bool CrossingRoadGame::OnUserUpdate(float fElapsedTime)
{
	switch (gameState) {
	case STATE_MENU:
		MenuHandler(fElapsedTime);
		break;
	case STATE_PLAY:
		GameHandler(fElapsedTime);
		break;
	case STATE_LOADGAME:
		LoadHandler(fElapsedTime);
		break;
	case STATE_SETTING:
		SettingHandler(fElapsedTime);
		break;
	case STATE_LEADERBOARD:
		LeaderboardHandler (fElapsedTime);
		break;
	case STATE_CREDIT:
		CreditHandler(fElapsedTime);
		break;
	}
	return true;
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
	m_bAtomActive = false;
}


void CrossingRoadGame::GameHandler(float fElapsedTime) {
	gameState = GameState::STATE_MENU;
	//VIET THEM BEN DUOI
}
void CrossingRoadGame::MenuHandler(float fElapsedTime) {
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
	}
}
void CrossingRoadGame::LoadHandler(float fElapsedTime) {
	if (m_keys[VK_ESCAPE].bReleased) {
		SetStateMenu();
	}
}
void CrossingRoadGame::LeaderboardHandler(float fElapsedTime) {
	if (m_keys[VK_ESCAPE].bReleased) {
		SetStateMenu();
	}
}
void CrossingRoadGame::CreditHandler(float fElapsedTime) {
	if (m_keys[VK_ESCAPE].bReleased) {
		SetStateMenu();
	}
}
void CrossingRoadGame::SettingHandler(float fElapsedTime) {
	if (m_keys[VK_ESCAPE].bReleased) {
		SetStateMenu();
	}
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
	Fill(20, 36 + ofset, 26, 36 + ofset, L' ', COLOUR::BG_BLACK);
	Fill(102, 36 + ofset, 108, 36 + ofset, L' ', COLOUR::BG_BLACK);
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
	Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', COLOUR::BG_BLUE);
	DrawString(5, 5, L"GAME SCREEN", BG_BLACK + BG_BLUE);
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