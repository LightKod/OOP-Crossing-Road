#pragma once
#ifndef _STATE_SETTING_H_
#define _STATE_SETTING_H_
#include "CrossingRoadGame.h"

class StateSetting : public CrossingRoadGame::State
{
public:
	virtual bool Update(float fElapsedTime);
	virtual bool OnStateEnter();
	virtual bool OnStateExit();

	StateSetting(CrossingRoadGame* game) : State(game) {};

	friend class CuncurrentThread;

protected:
	StateSetting() {};
	
	void UpdateMainBorder();

	void DrawFrogFrame(const int& offsetX);
	void DrawDogFrame(const int& offsetX);
	void Dog(const int& x, const int& y,
		const short& fg, const short& bg);
	void Frog(const int& x, const int& y,
		const short& fg, const short& bg);
	void F(const int& x, const int& y,
		const short& fg, const short& bg);
	void R(const int& x, const int& y,
		const short& fg, const short& bg);
	void O(const int& x, const int& y,
		const short& fg, const short& bg);
	void G(const int& x, const int& y,
		const short& fg, const short& bg);
	void D(const int& x, const int& y,
		const short& fg, const short& bg);

	void ClearFrame(const int& x, const int& y);
	void FrameFlowAnimation(const COORD& _C,
		void(StateSetting::*pFunc)(const int&));
	void SelectedFrame(const int& x, const int& y);
	void UnselectedFrame(const int& x, const int& y);
	void UIFrame(const int& x, const int& y,
		const short& borderFg, const short& borderBg,
		const short& topLayerFg, const short& topLayerBg,
		const short& botLayerFg, const short& botLayerBg,
		const short& mainFg, const short& mainBg);

	void PointerHandle();
	void ClearPointer();
	void UpdatePointerCoord();
	void DrawMousePointer();
	void Clicking();


	void UpdateRing1();
	void UpdateRing2();
	void SelectedAnimation(const int& x, const int& y);
	void UnselectedAnimation(const int& x, const int& y);
	void Ring1(const int& x, const int& y,
		const short& mainFg, const short& mainBg,
		const short& subFg, const short& subBg);
	void Ring2(const int& x, const int& y,
		const short& mainFg, const short& mainBg,
		const short& subFg, const short& subBg);
	void Ring3(const int& x, const int& y,
		const short& mainFg, const short& mainBg,
		const short& subFg, const short& subBg);
	void Ring4(const int& x, const int& y,
		const short& mainFg, const short& mainBg,
		const short& subFg, const short& subBg);
	void Ring5(const int& x, const int& y,
		const short& mainFg, const short& mainBg,
		const short& subFg, const short& subBg);
	void Ring6(const int& x, const int& y,
		const short& mainFg, const short& mainBg,
		const short& subFg, const short& subBg);
	void Ring7(const int& x, const int& y,
		const short& mainFg, const short& mainBg,
		const short& subFg, const short& subBg);
	void Ring8(const int& x, const int& y,
		const short& mainFg, const short& mainBg,
		const short& subFg, const short& subBg);
	void ClearRing(const int& x, const int& y,
		const short& fg, const short& bg);

	void MainBorder();
	void MainBorderColor();

	void OuterBorderColor();
	void InnerBorderColor();

	void OuterBorder();
	void InnerBorder();

	void Draw_TL_Corner(const short& fg, const short& bg);
	void Draw_TR_Corner(const short& fg, const short& bg);
	void Draw_BL_Corner(const short& fg, const short& bg);
	void Draw_BR_Corner(const short& fg, const short& bg);

	void DrawTitle(const int& x, const int& y);
	void TitleBorder(const int& x, const int& y,
		const short& fg, const short& bg);
	void TitleBackground(const int& x, const int& y,
		const short& fg, const short& bg);

private:
	static const int M_S_SRC_X0;
	static const int M_S_SRC_X1;
	static const int M_S_SRC_Y0;
	static const int M_S_SRC_Y1;

	static const pair<short, short> MB_COLOR;

	static const COORD C_FRAME_1;
	static const COORD C_FRAME_2;	
	static const COORD C_RING_1;
	static const COORD C_RING_2;
	static COORD C_MOUSE_POINTER;
	static const COORD FROG_COORD;
	static const COORD DOG_COORD;

	static short curCharIdx;
	static short lastCharIdx;

/*
ref: https://stackoverflow.com/questions/70766824/how-i-can-run-two-threads-parallelly-one-by-one
*/
	void InState_FrameFlowAnimation(const COORD& _C,
		void(StateSetting::* pFunc)(const int&), const int& stateIdx);
	void InState_SelectedAnimation(const int& x, const int& y, const int& stateIdx);
	void InState_UnselectedAnimation(const int& x, const int& y, const int& stateIdx);

	void procThread1();
	void procThread2();
	static void ThreadDriver(StateSetting* thr);

};

#endif // !_STATE_SETTING_H_
