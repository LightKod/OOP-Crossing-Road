#pragma once
#include "StatePlay_Deadline.h"

class StatePlay_Versus : public StatePlay_Deadline
{
private:
	Player* pPlayer2;
public:

	StatePlay_Versus(CrossingRoadGame* game) : StatePlay_Deadline(game) {
		pPlayer2 = nullptr;
	}

	virtual bool OnStateEnter();
	virtual bool Update(float fElapsedTime);
	virtual void DrawGameScreen();
	virtual void UpdateGameState(float fElapsedTime);
	virtual void NextLane();

	~StatePlay_Versus() {
		ClearCurrentLevel();
		game->ClearCollsionMatrix();
		if (pPlayer != nullptr) {
			delete pPlayer;
		}
		if (pPlayer2 != nullptr) {
			delete pPlayer2;
		}
	}
};

