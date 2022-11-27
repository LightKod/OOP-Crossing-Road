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
#include "StateDead.h"

using namespace std;

class StatePlay : public CrossingRoadGame::State 
{
private:
	int optionIndex = 0;
	int level = 0;
	float deltaTime = 0;
	vector<Lane*> lanes;
	Player* pPlayer = nullptr;
	bool pause = false;

	char laneSeed[10] = { 'R','R', 'R', 'R', 'R', 'R', 'W','W' ,'W' ,'W' };

public:
	StatePlay(CrossingRoadGame* game) : State(game) {};
	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();

	~StatePlay() {
		ClearCurrentLevel();
	}

private:
	void LevelUp(const int& x = -75, const int& y = 36);
	void LVUP_Border(const int& x, const int& y);
	void LVUP_TopColor(const int& x, const int& y, const short& fg, const short& bg);
	void LVUP_BotColor(const int& x, const int& y, const short& fg, const short& bg);
	void LVUP_MidLine(const int& x, const int& y);

	void UpdateCollisionMatrix();
	void UpdateGameScreen();
	void UpdateGameState(float fElapsedTime);
	void HandleInput();

	void GenerateNewLevel();
	void ClearCurrentLevel();
	void NextLevel();

	Data* ExportGameData();
	
};

#endif // !_STATE_PLAY_H_
