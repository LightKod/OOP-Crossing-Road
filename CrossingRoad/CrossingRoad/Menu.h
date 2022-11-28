#pragma once
#ifndef _MENU_H_
#define _MENU_H_
#include "StateMenu.h"
#include <vector>
#include <wchar.h>
using namespace std;

class Menu : public StateMenu
{
public:
	virtual void UpdateMenuUI(CrossingRoadGame* game, const int& opt,
		const int& innerOfset, const int& outerOfset);
	virtual void PressButtonAnimation(CrossingRoadGame* game, const int& x,
		const int& y, vector<wstring>& Strings);

	Menu(CrossingRoadGame* game);

	virtual void SplashAnimation(CrossingRoadGame* game, const int& opt);

protected:
	void UpdateMenuTitle(CrossingRoadGame*& game, const int& innerOfset, const int& outerOfset);
	void UpdateNewgameUI(CrossingRoadGame*& game, const int& opt);
	void UpdateLoadgameUI(CrossingRoadGame*& game, const int& opt);
	void UpdateLBUI(CrossingRoadGame*& game, const int& opt);
	void UpdateSettingUI(CrossingRoadGame*& game, const int& opt);
	void UpdateCreditUI(CrossingRoadGame*& game, const int& opt);
	void UpdateExitUI(CrossingRoadGame*& game, const int& opt);

private:
	void DrawNormalUI(CrossingRoadGame* game, const int& x, 
		const int& y, vector<wstring>& Strings);
	void DrawOptionalUI(CrossingRoadGame* game, const int& x, 
		const int& y, vector<wstring>& Strings);

	void DrawFirework(CrossingRoadGame* game, const int& centerX,
		const int& centerY, const short& fg, const short& bg);	
	void Splash1(CrossingRoadGame* game, const int& y,
		const short& fg, const short& bg);
	void Splash2(CrossingRoadGame* game, const int& y,
		const short& fg, const short& bg);
	void Splash3(CrossingRoadGame* game, const int& y,
		const short& fg, const short& bg);

	enum MENU_OPTION : int {
		NEWGAME_OPT = 0,
		LOADGAME_OPT,
		LB_OPT,
		SETTING_OPT,
		CREDIT_OPT,
		EXIT_OPT,
	};

	static const COORD C_NEWGAME;
	static const COORD C_LOADGAME;
	static const COORD C_LB;
	static const COORD C_SETTING;
	static const COORD C_CREDIT;
	static const COORD C_EXIT;

	vector<wstring> m_Newgame;
	vector<wstring> m_Loadgame;
	vector<wstring> m_LB;
	vector<wstring> m_Setting;
	vector<wstring> m_Credit;
	vector<wstring> m_Exit;
};

#endif // !_MENU_H_
