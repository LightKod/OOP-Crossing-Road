#pragma once
#include "CrossingRoadGame.h"
#include "Road.h"
#include "River.h"
#include "Frog.h"
#include "StateMenu.h"
int optionIndex = 0;
Player* pPlayer = nullptr;

static vector<CrossingRoadGame::Object*> objects;
static CrossingRoadGame::State* state;


bool CrossingRoadGame::OnUserCreate()
{
	SetState(new StateMenu(this));
	return true;
}


bool CrossingRoadGame::OnUserUpdate(float fElapsedTime)
{
	if (state != nullptr) {
		return state->Update(fElapsedTime);
	}
	return true;
}