#pragma once
#include "StatePlay.h"


class StatePlay_Deadline : public StatePlay
{
private:
	float counter = 2;
public:

	StatePlay_Deadline(CrossingRoadGame* game) : StatePlay(game) {
		laneSeed[2] = 'G';
		laneSeed[3] = 'G';
		laneSeed[6] = 'G';
	}
	

	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();


	~StatePlay_Deadline() {
		ClearCurrentLevel();
		game->ClearCollsionMatrix();
		if (pPlayer != nullptr) {
			delete pPlayer;
		}
	}

protected:
	void UpdateGameScreen() override;
	void GenerateNewLevel() override;
	virtual void NextLane();
	void HandleDeadline(float fElapsedTime);
};

