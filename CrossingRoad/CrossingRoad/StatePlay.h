#pragma once
#ifndef _STATE_PLAY_H_
#define _STATE_PLAY_H_
#include "CrossingRoadGame.h"
#include "Road.h"
#include "River.h"
#include "Frog.h"
#include "Dog.h"
#include "RestLane.h"
#include "Data.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "StateDead.h"
#include "TrafficLane.h"

using namespace std;

class StatePlay : public CrossingRoadGame::State 
{
private:
	int optionIndex = 0;
	float deltaTime = 0;

	vector<Lane*> lanes;
	Player* pPlayer = nullptr;
	bool pause = false;
	bool endState = false;

	wstring saveName = L"";
	int level = 1;
	int score = 0;
	int charIdx = 0;

	wstring date;

	char laneSeed[10] = { 'R','R', 'R', 'R', 'G', 'G', 'T','T' ,'W' ,'W' };

public:
	StatePlay(CrossingRoadGame* game) : State(game) {}
	StatePlay(CrossingRoadGame* game, const wstring& savedName,
		const wstring& lv, const wstring& score, const wstring& cIdx) : State(game) {
		this->saveName = savedName;
		this->level = stoi(lv);
		this->score = stoi(score);
		this->charIdx = stoi(cIdx);
	}
	
	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();

	~StatePlay() {
		ClearCurrentLevel();
	}

private:
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

	void LevelUp(const int& x = -75, const int& y = 36);
	void LVUP_Border(const int& x, const int& y);
	void LVUP_TopColor(const int& x, const int& y, const short& fg, const short& bg);
	void LVUP_BotColor(const int& x, const int& y, const short& fg, const short& bg);
	void LVUP_MidLine(const int& x, const int& y);

	void DrawSaveBox(const int& x, const int& y);

	void UpdateCollisionMatrix();
	void UpdateGameScreen();
	void UpdateGameState(float fElapsedTime);
	void HandleInput();
	void HandleSaveInput();

	void GenerateNewLevel();
	void ClearCurrentLevel();
	void NextLevel();

	void LoadLevel(wstring fileName);

	Data* ExportGameData();
	
};

#endif // !_STATE_PLAY_H_
