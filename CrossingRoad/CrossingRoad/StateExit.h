#pragma once
#ifndef _STATE_EXIT_H_
#define _STATE_EXIT_H_
#include "CrossingRoadGame.h"

class StateExit : public CrossingRoadGame::State
{
public:
	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();

	StateExit(CrossingRoadGame* game) : State(game) {};

protected:
	void HeartsEffect();

	void Heart3(const int& _x, const int& _y);
	void Heart3_SubHeart(const int& _x, const int& _y);
	void Heart3_LeftWing(const int& _x, const int& _y);
	void Heart3_MainHeart(const int& _x, const int& _y);
	void Heart3_RightWing(const int& _x, const int& _y);

	void Heart2(const int& _x, const int& _y);
	void Heart2_SubHeart(const int& _x, const int& _y);
	void Heart2_LeftWing(const int& _x, const int& _y);
	void Heart2_MainHeart(const int& _x, const int& _y);
	void Heart2_RightWing(const int& _x, const int& _y);

	void Heart1(const int& _x, const int& _y);
	void Heart1_SubHeart(const int& _x, const int& _y);
	void Heart1_LeftWing(const int& _x, const int& _y);
	void Heart1_MainHeart(const int& _x, const int& _y);
	void Heart1_RightWing(const int& _x, const int& _y);

	void Plus(const int& _x, const int& _y);
	void MiniHeart(const int& _x, const int& _y);

	void OpenWindowEffect();
	void DrawShadow1(const short& fg, const short& bg);
	void DrawShadow2(const short& fg, const short& bg);
	void DrawShadow3(const short& fg, const short& bg);
	void DrawShadow4(const short& fg, const short& bg);

	void DrawExitScreen();

	void DecorateExitScreen();
	void DrawTopButton(const int& x0, const int& y0,
		const short& fg, const short& bg);
	void DrawHeartButton();
	void DrawCommentButton();
	void DrawSaveButton();

	void DrawMessage();
	void Thanks(const int& _x, const int& _y,
		const short& fg, const short& bg);
	void For(const int& _x, const int& _y,
		const short& fg, const short& bg);
	void Playing(const int& _x, const int& _y,
		const short& fg, const short& bg);
	void ByeBye();
	void Bye(const int& _x, const int& _y,
		const short& fg, const short& bg);

private:
	static const int M_S_SRC_X0;
	static const int M_S_SRC_X1;
	static const int M_S_SRC_Y0;
	static const int M_S_SRC_Y1;

	Sound ByeSound;
};

#endif // !_STATE_EXIT_H_


