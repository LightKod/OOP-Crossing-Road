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
	StateMenu(): State() {}
	~StateMenu();

	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();

	virtual void UpdateMenuUI(CrossingRoadGame* game, const int& opt,
		const int& innerOfset, const int& outerOfset) {}
	virtual void PressButtonAnimation(CrossingRoadGame* game, const int& x,
		const int& y, vector<wstring>& Strings) {}
	virtual void SplashAnimation(CrossingRoadGame* game, const int& opt) {}
	
	StateMenu* p_Menu = nullptr;

};

#endif // !_STATE_MENU_H_
