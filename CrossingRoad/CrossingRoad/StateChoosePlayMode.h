#pragma once
#ifndef _CHOOSE_MODE_H_
#define _CHOOSE_MODE_H_
#include "CrossingRoadGame.h"

class StateChoosePlayMode : public CrossingRoadGame::State 
{
public:
	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();

	StateChoosePlayMode(CrossingRoadGame* game) : State(game) {}

private:
	void ChangeStateAnimation();
	void OpenLand(const int& desX);
	void UpdateUserChoice();

	void DrawLoadingState(const int& x, const int& y);
	void DrawLoadingState1(const int& x, const int& y);
	void DrawLoadingState2(const int& x, const int& y);

	void DrawTextBorder(const int& x, const int& y, const short& bg);
	void DrawText_();
	void DrawText_CASUAL();
	void DrawText_DEADLINE();
	void DrawText_ENDLESS();
	void DrawText_VERSUS();

	void UpdatePointerCoord();
	void DrawPointer();
	void ClearPointer();

	void DrawTitleBorder();
	void DrawTitle();

	static const vector<COORD> BORDER_COORD_LIST;
	static const vector<COORD> TEXT_COORD_LIST;
	static const short BG_COLOR;

	COORD C_Pointer = { 0,0 };
	int UserChoice = 0;
};

#endif // !_CHOOSE_MODE_H_
