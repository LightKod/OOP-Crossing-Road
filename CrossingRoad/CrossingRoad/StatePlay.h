#pragma once
#include "CrossingRoadGame.h"
#include "Road.h"
#include "River.h"
#include "Frog.h"
#include"RestLane.h"
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
	void UpdateCollisionMatrix();
	void UpdateGameScreen();
	void UpdateGameState(float fElapsedTime);
	void HandleInput();

	void GenerateNewLevel();
	void ClearCurrentLevel();
	void NextLevel();

	Data* ExportGameData();

	
};