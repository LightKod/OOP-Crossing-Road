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
	DrawString(40, 35, L"▒█▄░▒█ ▒█▀▀▀ ▒█░░▒█    ▒█▀▀█ ░█▀▀█ ▒█▀▄▀█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	DrawString(40, 36, L"▒█▒█▒█ ▒█▀▀▀ ▒█▒█▒█    ▒█░▄▄ ▒█▄▄█ ▒█▒█▒█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	DrawString(40, 37, L"▒█░░▀█ ▒█▄▄▄ ▒█▄▀▄█    ▒█▄▄█ ▒█░▒█ ▒█░░▒█ ▒█▄▄▄", BG_BLACK + BG_BLUE);

	DrawString(44, 42, L"▒█▀▀█ ▒█▀▀▀ ▒█▀▀▀█ ▒█░▒█ ▒█▀▄▀█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	DrawString(44, 43, L"▒█▄▄▀ ▒█▀▀▀ ░▀▀▀▄▄ ▒█░▒█ ▒█▒█▒█ ▒█▀▀▀", BG_BLACK + BG_BLUE);
	DrawString(44, 44, L"▒█░▒█ ▒█▄▄▄ ▒█▄▄▄█ ░▀▄▄▀ ▒█░░▒█ ▒█▄▄▄", BG_BLACK + BG_BLUE);

	DrawString(32, 49, L"▒█░░░ ▒█▀▀▀ ░█▀▀█ ▒█▀▀▄ ▒█▀▀▀ ▒█▀▀█ ▒█▀▀█ ▒█▀▀▀█ ░█▀▀█ ▒█▀▀█ ▒█▀▀▄", BG_BLACK + BG_BLUE);
	DrawString(32, 50, L"▒█░░░ ▒█▀▀▀ ▒█▄▄█ ▒█░▒█ ▒█▀▀▀ ▒█▄▄▀ ▒█▀▀▄ ▒█░░▒█ ▒█▄▄█ ▒█▄▄▀ ▒█░▒█░", BG_BLACK + BG_BLUE);
	DrawString(32, 51, L"▒█▄▄█ ▒█▄▄▄ ▒█░▒█ ▒█▄▄▀ ▒█▄▄▄ ▒█░▒█ ▒█▄▄█ ▒█▄▄▄█ ▒█░▒█ ▒█░▒█ ▒█▄▄▀░", BG_BLACK + BG_BLUE);

	DrawString(42, 56, L"▒█▀▀▀█ ▒█▀▀▀ ▀▀█▀▀ ▀▀█▀▀ ▀█▀ ▒█▄░▒█ ▒█▀▀█", BG_BLACK + BG_BLUE);
	DrawString(42, 57, L"░▀▀▀▄▄ ▒█▀▀▀ ░▒█░░ ░▒█░░ ▒█░ ▒█▒█▒█ ▒█░▄▄", BG_BLACK + BG_BLUE);
	DrawString(42, 58, L"▒█▄▄▄█ ▒█▄▄▄ ░▒█░░ ░▒█░░ ▄█▄ ▒█░░▀█ ▒█▄▄█", BG_BLACK + BG_BLUE);

	DrawString(46, 63, L"▒█▀▀█ ▒█▀▀█ ▒█▀▀▀ ▒█▀▀▄ ▀█▀ ▀▀█▀▀", BG_BLACK + BG_BLUE);
	DrawString(46, 64, L"▒█░░░ ▒█▄▄▀ ▒█▀▀▀ ▒█░▒█ ▒█░ ░▒█░░", BG_BLACK + BG_BLUE);
	DrawString(46, 65, L"▒█▄▄█ ▒█░▒█ ▒█▄▄▄ ▒█▄▄▀ ▄█▄ ░▒█░░", BG_BLACK + BG_BLUE);

	DrawString(52, 70, L"▒█▀▀▀ ▀▄▒▄▀ ▀█▀ ▀▀█▀▀", BG_BLACK + BG_BLUE);
	DrawString(52, 71, L"▒█▀▀▀ ░▒█░░ ▒█░ ░▒█░░", BG_BLACK + BG_BLUE);
	DrawString(52, 72, L"▒█▄▄▄ ▄▀▒▀▄ ▄█▄ ░▒█░░", BG_BLACK + BG_BLUE);
}
void CrossingRoadGame::UpdateMousePosition(int index) {
	int ofset = index * 7;
	Fill(20, 36 + ofset, 26, 36 + ofset, L' ', COLOUR::BG_BLACK);
	Fill(102, 36 + ofset, 108, 36 + ofset, L' ', COLOUR::BG_BLACK);
}
void CrossingRoadGame::DrawMenuTitle(int innerOfset, int outerOfset){
	//Inner
	//C
	Fill(5, 12 + innerOfset, 7, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(4, 13 + innerOfset, 4, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(8, 12 + innerOfset, 11, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(9, 13 + innerOfset, 12, 13 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(8, 17 + innerOfset, 11, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(9, 16 + innerOfset, 12, 16 + innerOfset, L' ', COLOUR::BG_WHITE);

	//R
	Fill(14, 12 + innerOfset, 17, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(19, 12 + innerOfset, 21, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(22, 14 + innerOfset, 22, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(22, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(18, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(18, 17 + innerOfset, L' ', COLOUR::BG_WHITE);

	//O
	Fill(24, 13 + innerOfset, 27, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(29, 13 + innerOfset, 32, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(25, 12 + innerOfset, 31, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(25, 18 + innerOfset, 31, 18 + innerOfset, L' ', COLOUR::BG_WHITE);

	//S
	Fill(35, 12 + innerOfset, 42, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(34, 13 + innerOfset, 37, 14 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(35, 16 + innerOfset, 36, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(35, 15 + innerOfset, 41, 15 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(39, 16 + innerOfset, 42, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(39, 16 + innerOfset, 42, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(34, 18 + innerOfset, 41, 18 + innerOfset, L' ', COLOUR::BG_WHITE);

	//S
	Fill(35 + 10, 12 + innerOfset, 42 + 10, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(34 + 10, 13 + innerOfset, 37 + 10, 14 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(35 + 10, 16 + innerOfset, 36 + 10, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(35 + 10, 15 + innerOfset, 41 + 10, 15 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(39 + 10, 16 + innerOfset, 42 + 10, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(39 + 10, 16 + innerOfset, 42 + 10, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(34 + 10, 18 + innerOfset, 41 + 10, 18 + innerOfset, L' ', COLOUR::BG_WHITE);

	//I
	Fill(54, 12 + innerOfset, 57, 18, L' ', COLOUR::BG_WHITE);

	//N
	Fill(59, 12 + innerOfset, 61, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(62, 13 + innerOfset, 62, 15 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(63, 15 + innerOfset, 63, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(64, 12 + innerOfset, 66, 18 + innerOfset, L' ', COLOUR::BG_WHITE);


	//G
	Fill(70, 12 + innerOfset, 76, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(69, 13 + innerOfset, 72, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(70, 18 + innerOfset, 76, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(75, 15 + innerOfset, 77, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(74, 15 + innerOfset, L' ', COLOUR::BG_WHITE);

	//R
	Fill(14 + 71, 12 + innerOfset, 17 + 71, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(19 + 71, 12 + innerOfset, 21 + 71, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(22 + 71, 14 + innerOfset, 22 + 71, 16 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(22 + 71, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(18 + 71, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(18 + 71, 17 + innerOfset, L' ', COLOUR::BG_WHITE);

	//O
	Fill(24 + 71, 13 + innerOfset, 27 + 71, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(29 + 71, 13 + innerOfset, 32 + 71, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(25 + 71, 12 + innerOfset, 31 + 71, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(25 + 71, 18 + innerOfset, 31 + 71, 18 + innerOfset, L' ', COLOUR::BG_WHITE);

	//A
	Fill(105, 13 + innerOfset, 108, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(110, 13 + innerOfset, 113, 17 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(106, 12 + innerOfset, 112, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Draw(109, 16 + innerOfset, L' ', COLOUR::BG_WHITE);

	//D
	Fill(115, 12 + innerOfset, 118, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(119, 12 + innerOfset, 122, 12 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(119, 18 + innerOfset, 122, 18 + innerOfset, L' ', COLOUR::BG_WHITE);
	Fill(120, 13 + innerOfset, 123, 17 + innerOfset, L' ', COLOUR::BG_WHITE);

	//Outline
	//C
	Fill(4, 18 + outerOfset, 4, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(5, 20 + outerOfset, 12, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(12, 19 + outerOfset, 13, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(13, 14 + outerOfset, 13, 18 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(8, 14 + outerOfset, 8, 17 + outerOfset, L' ', COLOUR::BG_BLACK);

	//R
	Fill(14, 20 + outerOfset, 23, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(23, 14 + outerOfset, 23, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(18, 14 + outerOfset, 18, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(18, 14 + outerOfset, 18, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(22, 13 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(22, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(24, 19 + outerOfset, L' ', COLOUR::BG_BLACK);

	//0
	Fill(25, 20 + outerOfset, 32, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(32, 19 + outerOfset, 33, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(33, 14 + outerOfset, 33, 18 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(28, 14 + outerOfset, 28, 17 + outerOfset, L' ', COLOUR::BG_BLACK);

	//S
	Draw(34, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(43, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(42, 15 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(35, 17 + outerOfset, 35, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(34, 20 + outerOfset, 42, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(42, 18 + outerOfset, 43, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(43, 13 + outerOfset, 43, 15 + outerOfset, L' ', COLOUR::BG_BLACK);

	//S
	Draw(34 + 10, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(43 + 10, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(42 + 10, 15 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(35 + 10, 17 + outerOfset, 35 + 10, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(34 + 10, 20 + outerOfset, 42 + 10, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(42 + 10, 18 + outerOfset, 43 + 10, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(43 + 10, 13 + outerOfset, 43 + 10, 15 + outerOfset, L' ', COLOUR::BG_BLACK);

	//ING
	Fill(54, 20 + outerOfset, 62, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(58, 13 + outerOfset, 58, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(62, 17 + outerOfset, 62, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(63, 19 + outerOfset, 64, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(65, 20 + outerOfset, 68, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(68, 13 + outerOfset, 68, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(70, 20 + outerOfset, 77, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(77, 19 + outerOfset, 78, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(78, 15 + outerOfset, 78, 18 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(77, 13 + outerOfset, 77, 14 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(73, 15 + outerOfset, 73, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(69, 19 + outerOfset, 69, 19 + outerOfset, L' ', COLOUR::BG_BLACK);

	//R
	Fill(14 + 71, 20 + outerOfset, 23 + 71, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(23 + 71, 14 + outerOfset, 23 + 71, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(18 + 71, 14 + outerOfset, 18 + 71, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(18 + 71, 14 + outerOfset, 18 + 71, 16 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(22 + 71, 13 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(22 + 71, 17 + outerOfset, L' ', COLOUR::BG_BLACK);
	Draw(24 + 71, 19 + outerOfset, L' ', COLOUR::BG_BLACK);

	//0
	Fill(25 + 71, 20 + outerOfset, 32 + 71, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(32 + 71, 19 + outerOfset, 33 + 71, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(33 + 71, 14 + outerOfset, 33 + 71, 18 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(28 + 71, 14 + outerOfset, 28 + 71, 17 + outerOfset, L' ', COLOUR::BG_BLACK);

	//AD
	Fill(105, 20 + outerOfset, 122, 20 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(109, 18 + outerOfset, 109, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(109, 14 + outerOfset, 109, 15 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(114, 14 + outerOfset, 114, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(122, 19 + outerOfset, 123, 19 + outerOfset, L' ', COLOUR::BG_BLACK);
	Fill(123, 18 + outerOfset, 123, 18 + outerOfset, L' ', COLOUR::BG_BLACK);

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