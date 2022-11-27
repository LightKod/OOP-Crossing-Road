#pragma once
#ifndef _STATE_MENU_H_
#define _STATE_MENU_H_

#include "CrossingRoadGame.h"

class StateMenu : public CrossingRoadGame::State
{
private:
	static int		m_s_OptionIdx;
	static float	m_s_DeltaTime;
	bool down = false;

	void DrawMainMenu();

public:
	StateMenu(CrossingRoadGame* game);
	StateMenu() : State() {}
	~StateMenu();

	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();

};

#endif // !_STATE_MENU_H_
