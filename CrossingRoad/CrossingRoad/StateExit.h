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
	void Bye(const int& _x, const int& _y,
		const short& fg, const short& bg);

private:
	static const int M_S_SRC_X0;
	static const int M_S_SRC_X1;
	static const int M_S_SRC_Y0;
	static const int M_S_SRC_Y1;

	bool m_bBack{ false };
};

#endif // !_STATE_EXIT_H_


