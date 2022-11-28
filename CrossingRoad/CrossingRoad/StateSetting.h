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

protected:
	void DrawTitle(const int& x, const int& y);
	void TitleBorder(const int& x, const int& y,
		const short& fg, const short& bg);
	void TitleBackground(const int& x, const int& y,
		const short& fg, const short& bg);

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

	void SelectedFrame(const int& x, const int& y);
	void UnselectedFrame(const int& x, const int& y);
	void UIFrame(const int& x, const int& y,
		const short& borderFg, const short& borderBg,
		const short& topLayerFg, const short& topLayerBg,
		const short& botLayerFg, const short& botLayerBg,
		const short& mainFg, const short& mainBg);

	void MousePointer(const int& x, const int& y);
	void Clicking(const int& x, const int& y);

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

private:

};

#endif // !_STATE_SETTING_H_
