#pragma once
#include <iostream>
#include "GameEngine.h"


class CrossingRoadGame : public GameEngine {
public:
	CrossingRoadGame() {
		m_sAppName = L'CrossingRoad';
	}
protected:
	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float fElapsedTime);


private:
	//GameHandler
	void MenuHandler(float fElapsedTime);
	void LoadHandler(float fElapsedTime);
	void LeaderboardHandler(float fElapsedTime);
	void CreditHandler(float fElapsedTime);
	void SettingHandler(float fElapsedTime);

	void GameHandler(float fElapsedTime);

private:
	void SetStateMenu();
	void SetStateNewGame();
	void SetStateLoadGame();
	void SetStateLeaderBoard();
	void SetStateSetting();
	void SetStateCredit();
	void SetStateExit();

private:
	enum GameState {
		STATE_MENU,
		STATE_PLAY,
		STATE_SETTING,
		STATE_LOADGAME,
		STATE_LEADERBOARD,
		STATE_CREDIT,
	};
	GameState gameState = GameState::STATE_MENU;

private:
	//Drawer
	void DrawMainMenu(int optionIndex, int titleInnerOfset = 0, int titleOuterOfset = 0);
	void DrawMenuTitle(int innerOfset, int outerOfset);
	void DrawMenuOptions();
	void UpdateMousePosition(int index);

	void DrawGame();
	void DrawLoadGame();
	void DrawLeaderboard();
	void DrawSetting();
	void DrawCredit();
};