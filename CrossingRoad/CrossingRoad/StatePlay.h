#pragma once
#include "CrossingRoadGame.h"
#include "Road.h"
#include "River.h"
#include "Frog.h"
#include <vector>

using namespace std;

class StatePlay : public CrossingRoadGame::State
{
private:
	int optionIndex = 0;
	float deltaTime = 0;
	vector<CrossingRoadGame::Object*> objects;
	Player* pPlayer = nullptr;

public:
	StatePlay(CrossingRoadGame* game) : State(game) {};
	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();

private:
	void UpdateCollisionMatrix();
	void UpdateGameScreen();
	void UpdateGameState(float fElapsedTime);
};