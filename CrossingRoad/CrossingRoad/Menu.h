#pragma once
#ifndef _MENU_H_
#define _MENU_H_
#include "StateMenu.h"
#include <vector>
#include <wchar.h>
using namespace std;
/*
		Splash3(game, y, FG_DARK_YELLOW, BG_DARK_YELLOW);
		Splash2(game, y, FG_YELLOW, BG_YELLOW);
		Splash1(game, y, FG_GREY, BG_GREY);
*/
class Menu : public StateMenu
{
public:
	void UpdateMenuUI(CrossingRoadGame* game, const int& opt,
		const int& innerOfset, const int& outerOfset) 
	{
		// clear screen
		game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);

		// Update UI
		UpdateMenuTitle(game, innerOfset, outerOfset);

		UpdateNewgameUI(game, opt);
		UpdateLoadgameUI(game, opt);
		UpdateLBUI(game, opt);
		UpdateSettingUI(game, opt);
		UpdateCreditUI(game, opt);
		UpdateExitUI(game, opt);
	}
	void PressButtonAnimation(CrossingRoadGame* game, const int& x, 
		const int& y, vector<wstring>& Strings);

	Menu(CrossingRoadGame* game);

	void SplashAnimation(CrossingRoadGame* game, const int& opt) {
		switch (opt) {
		case MENU_OPTION::NEWGAME_OPT:
			PressButtonAnimation(game, C_NEWGAME.X, C_NEWGAME.Y, m_Newgame);
			break;
		case MENU_OPTION::LOADGAME_OPT:
			PressButtonAnimation(game, C_LOADGAME.X, C_LOADGAME.Y, m_Loadgame);
			break;
		case MENU_OPTION::LB_OPT:
			PressButtonAnimation(game, C_LB.X, C_LB.Y, m_LB);
			break;
		case MENU_OPTION::SETTING_OPT:
			PressButtonAnimation(game, C_SETTING.X, C_SETTING.Y, m_Setting);
			break;
		case MENU_OPTION::CREDIT_OPT:
			PressButtonAnimation(game, C_CREDIT.X, C_CREDIT.Y, m_Credit);
			break;
		case MENU_OPTION::EXIT_OPT:
			PressButtonAnimation(game, C_EXIT.X, C_EXIT.Y, m_Exit);
			break;
		default: 
			break;
		}
	}

protected:
	void UpdateMenuTitle(CrossingRoadGame*& game, const int& innerOfset, const int& outerOfset);
	void UpdateNewgameUI(CrossingRoadGame*& game, const int& opt) {
		if (opt == MENU_OPTION::NEWGAME_OPT)
			DrawOptionalUI(game, C_NEWGAME.X, C_NEWGAME.Y, m_Newgame);
		else
			DrawNormalUI(game, C_NEWGAME.X, C_NEWGAME.Y, m_Newgame);
	}
	void UpdateLoadgameUI(CrossingRoadGame*& game, const int& opt) {
		if (opt == MENU_OPTION::LOADGAME_OPT)
			DrawOptionalUI(game, C_LOADGAME.X, C_LOADGAME.Y, m_Loadgame);
		else
			DrawNormalUI(game, C_LOADGAME.X, C_LOADGAME.Y, m_Loadgame);
	}
	void UpdateLBUI(CrossingRoadGame*& game, const int& opt) {
		if (opt == MENU_OPTION::LB_OPT)
			DrawOptionalUI(game, C_LB.X, C_LB.Y, m_LB);
		else
			DrawNormalUI(game, C_LB.X, C_LB.Y, m_LB);
	}
	void UpdateSettingUI(CrossingRoadGame*& game, const int& opt) {
		if (opt == MENU_OPTION::SETTING_OPT)
			DrawOptionalUI(game, C_SETTING.X, C_SETTING.Y, m_Setting);
		else
			DrawNormalUI(game, C_SETTING.X, C_SETTING.Y, m_Setting);
	}
	void UpdateCreditUI(CrossingRoadGame*& game, const int& opt) {
		if (opt == MENU_OPTION::CREDIT_OPT)
			DrawOptionalUI(game, C_CREDIT.X, C_CREDIT.Y, m_Credit);
		else
			DrawNormalUI(game, C_CREDIT.X, C_CREDIT.Y, m_Credit);
	}
	void UpdateExitUI(CrossingRoadGame*& game, const int& opt) {
		if (opt == MENU_OPTION::EXIT_OPT)
			DrawOptionalUI(game, C_EXIT.X, C_EXIT.Y, m_Exit);
		else
			DrawNormalUI(game, C_EXIT.X, C_EXIT.Y, m_Exit);
	}

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


