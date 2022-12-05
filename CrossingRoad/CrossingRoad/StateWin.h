#pragma once
#include "StateMenu.h"
class StateWin : public CrossingRoadGame::State
{
	int score;
	wstring saveName = L"";
	int optionIndex;
public:
	StateWin(CrossingRoadGame* game, int score) {
		this->game = game;
		this->score = score;
		saveName = L"   ";
	}

	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit() { return true; }


	void DrawSaveBox(const int& x = 35, const int& y = 4);
	void HandleEnterName();

	void ForestBG();
	void MiniGrass(const int& x, const int& y);
	void MiniMushroom(const int& x, const int& y);

	void OpenWinProcess();
	void WinProcess();

	void CompleteCGBanner(const int& x, const int& y);

	void DrawTrainWheel(const int& x = 20, const int& y = 20);
	void MiniWheel(const int& x = 20, const int& y = 20);
	void TrainLocomotive(const int& x = 20, const int& y = 20);
	void TrainWagon(const int& x = 1, const int& y = 20);
	void Smoke(const int& x = 1, const int& y = 20);

	void CompleteWinBanner();
	void YouWin(const int& x = 20, const int& y = 20);
	void WinBorder();
	void WinningCup(const int& x = 50, const int& y = 50);

	void Congratulations(const int& x = 10, const int& y = 10);
	void CG_BannerBorder(const int& x = 10, const int& y = 10);
	void DrawCGBanner(const int& x = 10, const int& y = 10);
};

