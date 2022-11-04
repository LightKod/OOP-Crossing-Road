#pragma once
#ifndef _STATE_LOAD_H_
#define _STATE_LOAD_H_
#include "CrossingRoadGame.h"

class StateLoad : public CrossingRoadGame::State
{
public:
	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();

	StateLoad(CrossingRoadGame* game) : State(game) {};

	void LoadingThread(CrossingRoadGame*& game, const int&);

protected:
	void DrawLoadingScreen(CrossingRoadGame*& game);
	void DrawCheckbox(CrossingRoadGame*& game, const COORD&);
	void DrawArrow(CrossingRoadGame*& game);
						     
	void LS_FillBackground(CrossingRoadGame*& game);
	void LS_DrawBorder(CrossingRoadGame*& game);
	void LS_DecorateScreen(CrossingRoadGame*& game);

	void UpdateArrowCoord(const int&);
	void SetArrowCoord(const COORD&);
	void MoveArrow(const int&);

	void LoadingAnimation(CrossingRoadGame*& game);

private:
	COORD m_ArrowCoord{0,0};
	
	static const int m_s_OFFSET_X;
	static const int m_s_X0;
	static const int m_s_X1;
	static const int m_s_Y0;
	static const int m_s_Y1;

	static const COORD m_s_LINE_1;
	static const COORD m_s_LINE_2;
	static const COORD m_s_LINE_3;
	static const COORD m_s_LINE_4;

};

#endif // !_STATE_LOAD_H_


