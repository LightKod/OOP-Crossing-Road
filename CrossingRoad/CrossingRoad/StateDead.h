#pragma once
#ifndef _STATE_DEAD_H_
#define _STATE_DEAD_H_
#include "CrossingRoadGame.h"
#include "Frog.h"
#include "StatePlay.h"
#include "StateMenu.h"
#include "Ambulance.h"

class StateDead: public CrossingRoadGame::State
{
	Player* pPlayer = nullptr;
	int optionIndex=0;
	Ambulance* ambulance=nullptr;
	//DUMMY
	int h = 0;
	bool DeadChoice;
	float time = 0;
	short col=COLOUR::BG_BLACK;
	int m=0;

public:
	StateDead(CrossingRoadGame* game, Player* pplayer) {
		this->game = game;
		pPlayer = pplayer;
	}
	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();

	void DeadAnimation(float fElapsedTime, bool Option);
	bool DeadOption(float fElapsedTime);
	void DrawDeadBoard(float fElapsedTime);
	void DrawOption(int x,int y,short col);
	void DrawDeadScreen();
	void DrawSavedScreen();

};

#endif
