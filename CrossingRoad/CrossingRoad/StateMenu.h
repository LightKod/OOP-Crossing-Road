#pragma once
#include "CrossingRoadGame.h"

class StateMenu : public CrossingRoadGame::State
{
private:
	int optionIndex = 0;
	float deltaTime = 0;
    bool down = false;
	void DrawMainMenu( int optionIndex, int titleInnerOfset, int titleOuterOfset);
	void DrawMenuTitle(int innerOfset, int outerOfset);
	void DrawMenuOptions();
	void UpdateMousePosition(int index);
public:
	StateMenu(CrossingRoadGame* game);
	StateMenu() : State() {}
	~StateMenu();
	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();
};