#pragma once
#ifndef _STATE_LB_H_
#define _STATE_LB_H_
#include "CrossingRoadGame.h"
#include "Data.h"

class StateLB : public CrossingRoadGame::State
{
public:
	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();

	StateLB(CrossingRoadGame* game) : State(game) {};

protected:
	void Intro();

	void PostEffect();
	void DrawCrown(const int& _x, const int& _y);
	void Firework(const int& _x, const int& _y);

	void DrawPodium(const int& x, const int& y);
	void DrawMedal(const int& x, const int& y,
		const int& rank);

	void DrawGoldMedal(const int& x, const int& y);
	void DrawSilverMedal(const int& x, const int& y);
	void DrawCopperMedal(const int& x, const int& y);
	
	void ShowRank3();
	void ShowRank2();
	void ShowRank1();

	void ShowDataEffect(const COORD&);

private:
	Sound LBSound;
	void GetDataRecord();

	vector<Data> m_Datas;
	int m_CurrIndex = 2;

	static const int M_S_SRC_X0;
	static const int M_S_SRC_X1;
	static const int M_S_SRC_Y0;
	static const int M_S_SRC_Y1;

	static const COORD M_S_COL_1;
	static const COORD M_S_COL_2;
	static const COORD M_S_COL_3;

	void AnimationThread();
	bool m_bBack{ false };
};

#endif // !_STATE_LB_H_
