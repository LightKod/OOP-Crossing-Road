#pragma once
#include "StatePlay.h"

class StatePlay_Endless : public StatePlay
{
public:

	StatePlay_Endless(CrossingRoadGame* game) : StatePlay(game) {
		laneSeed[2] = 'G';
		laneSeed[3] = 'G';
		laneSeed[6] = 'G';
	}


	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();


	~StatePlay_Endless() {
		ClearCurrentLevel();
		if (pPlayer != nullptr) {
			delete pPlayer;
		}
	}

protected:
	void UpdateGameScreen() override;
	void GenerateNewLevel() override;
	void NextLane();
};

