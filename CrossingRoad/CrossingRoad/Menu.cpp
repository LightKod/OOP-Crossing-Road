#include "Menu.h"

const COORD Menu::C_EXIT	= { 70, 85 };
const COORD Menu::C_CREDIT	= { 67, 72 };
const COORD Menu::C_SETTING = { 62, 59 };
const COORD Menu::C_LB		= { 53, 46 };
const COORD Menu::C_LOADGAME= { 58, 33 };
const COORD Menu::C_NEWGAME = { 60, 20 };

static const int x0 = 50;
static const int x1 = 110;
static const int DUMMY_ROW = 7;

void Menu::UpdateMenuUI(CrossingRoadGame* game, const int& opt,
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

void Menu::SplashAnimation(CrossingRoadGame* game, const int& opt) {
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

void DrawShadowEffect(CrossingRoadGame* game, int y0)
{
	const int y = y0 - 1;

	// nền xám
	game->DrawLine(x0 - 1, y, x1 + 1, y, PIXEL_SOLID, FG_DARK_GREY + BG_DARK_GREY);
	game->Fill(x0 - 2, y + 1, x1 + 2, y + 8, PIXEL_SOLID, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x0 - 1, y + 9, x1 + 1, y + 9, PIXEL_SOLID, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x0, y + 10, x1, y + 10, PIXEL_SOLID, FG_DARK_GREY + BG_DARK_GREY);

	// viền đen
	for (int i = 1; i <= 8; i++)
	{
		game->Draw(x0 - 1, y + i, PIXEL_SOLID, FG_BLACK + BG_BLACK);
		game->Draw(x1 + 1, y + i, PIXEL_SOLID, FG_BLACK + BG_BLACK);
	}
	game->Draw(x0, y + 8, PIXEL_SOLID, FG_BLACK + BG_BLACK);
	game->Draw(x1, y + 8, PIXEL_SOLID, FG_BLACK + BG_BLACK);
	game->DrawLine(x0, y + 9, x1, y + 9, PIXEL_SOLID, FG_BLACK + BG_BLACK);
}
void DrawPanel(CrossingRoadGame* game, const int& _x, const int& _y,
	vector<wstring>& wStrings, const short& fg, const short& bg)
{
	const int y = _y - 3;

	// Tô nền
	game->Fill(x0 + 1, y + 1, x1 - 1, y + DUMMY_ROW, PIXEL_SOLID, fg + bg);

	// Vẽ viền trên
	game->DrawLine(x0 + 1, y, x1 - 1, y, PIXEL_SOLID, FG_BLACK + BG_BLACK);

	// Vẽ viền 2 bên
	int row = 1;
	for (; row < 8; row++)
	{
		game->Draw(x0, y + row, PIXEL_SOLID, FG_BLACK + BG_BLACK);
		game->Draw(x1, y + row, PIXEL_SOLID, FG_BLACK + BG_BLACK);
	}

	//// Vẽ viền dưới
	game->DrawLine(x0 + 1, y + row, x1 - 1, y + row, PIXEL_SOLID, FG_BLACK + BG_BLACK);

	// Xuất chữ
	for (int i = 0; i < 3; i++)
	{
		game->DrawString(_x, _y + i, wStrings[i], FG_BLACK + bg);
	}
}

void Menu::DrawFirework(CrossingRoadGame* game, const int& centerX,
	const int& centerY, const short& fg, const short& bg)
{
	game->Draw(centerX, centerY - 1, PIXEL_SOLID, fg + bg);
	game->DrawLine(centerX - 1, centerY, centerX + 1, centerY, PIXEL_SOLID, fg + bg);
	game->Draw(centerX, centerY + 1, PIXEL_SOLID, fg + bg);
}
void Menu::Splash1(CrossingRoadGame* game, const int& y, 
	const short& fg, const short& bg)
{
	// Top-Left
	DrawFirework(game, x0 - 4, y - 2, fg, bg);
	DrawFirework(game, x0 - 5, y - 3, fg, bg);
	DrawFirework(game, x0 - 6, y - 4, fg, bg);

	// Top-Right
	DrawFirework(game, x1 + 4, y - 2, fg, bg);
	DrawFirework(game, x1 + 5, y - 3, fg, bg);
	game->Draw(x1 + 6, y - 4, 9608, fg + bg);

	// Bot-Left
	DrawFirework(game, x0 - 4, y + 7, fg, bg);
	game->Draw(		   x0 - 3, y + 6, PIXEL_SOLID, fg + bg);
	game->Draw(		   x0 - 4, y + 5, PIXEL_SOLID, fg + bg);
	DrawFirework(game, x0 - 5, y + 6, fg, bg);

	// Bot-Right
	DrawFirework(game, x1 + 5, y + 5, fg, bg);
	DrawFirework(game, x1 + 7, y + 4, fg, bg);
	game->Draw(         x1 + 8, y + 3, PIXEL_SOLID, fg + bg);
}
void Menu::Splash2(CrossingRoadGame* game, const int& y,
	const short& fg, const short& bg)
{
	//// Top-Left
	DrawFirework(game, x0 - 8, y - 6, fg, bg);
	game->Draw(         x0 - 9, y - 7, PIXEL_SOLID, fg + bg);

	//// Top-Right
	DrawFirework(game, x1 + 8, y - 5, fg, bg);
	DrawFirework(game, x1 + 9, y - 5, fg, bg);
	DrawFirework(game, x1 + 10, y - 6, fg, bg);
	DrawFirework(game, x1 + 11, y - 6, fg, bg);

	// Bot-Left
	DrawFirework(game, x0 - 7, y + 4, fg, bg);

	// Bot-Right
	DrawFirework(game, x1 + 10, y + 4, fg, bg);
	game->Draw(         x1 + 11,y + 5, PIXEL_SOLID, fg + bg);
}
void Menu::Splash3(CrossingRoadGame* game, const int& y,
	const short& fg, const short& bg)
{
	// Top-Left
	game->Draw(x0 - 11, y - 6, PIXEL_SOLID, fg + bg);
	game->Draw(x0 - 11, y - 8, PIXEL_SOLID, fg + bg);
	game->Draw(x0 - 12, y - 7, PIXEL_SOLID, fg + bg);
	game->Draw(x0 - 13, y - 6, PIXEL_SOLID, fg + bg);
	game->Draw(x0 - 13, y - 8, PIXEL_SOLID, fg + bg);
	
	// Top-Right
	game->Draw(x1 + 16, y - 6, PIXEL_SOLID, fg + bg);

	game->Draw(x1 + 15, y - 8, PIXEL_SOLID, fg + bg);
	game->Draw(x1 + 15, y - 7, PIXEL_SOLID, fg + bg);
	game->Draw(x1 + 14, y - 7, PIXEL_SOLID, fg + bg);

	game->Draw(x1 + 15, y - 4, PIXEL_SOLID, fg + bg);
	game->Draw(x1 + 15, y - 5, PIXEL_SOLID, fg + bg);
	game->Draw(x1 + 14, y - 5, PIXEL_SOLID, fg + bg);

	game->Draw(x1 + 17, y - 4, PIXEL_SOLID, fg + bg);
	game->Draw(x1 + 17, y - 5, PIXEL_SOLID, fg + bg);
	game->Draw(x1 + 18, y - 5, PIXEL_SOLID, fg + bg);

	game->Draw(x1 + 17, y - 8, PIXEL_SOLID, fg + bg);
	game->Draw(x1 + 17, y - 7, PIXEL_SOLID, fg + bg);
	game->Draw(x1 + 18, y - 7, PIXEL_SOLID, fg + bg);

	// Bot-Left
	game->Draw(x0 - 9, y + 5, PIXEL_SOLID, fg + bg);
	game->Draw(x0 - 10, y + 5, PIXEL_SOLID, fg + bg);
	game->Draw(x0 - 9, y + 6, PIXEL_SOLID, fg + bg);
	
	// Bot-Right
	game->Draw(x1 + 11, y + 7, PIXEL_SOLID, fg + bg);
	game->Draw(x1 + 12, y + 6, PIXEL_SOLID, fg + bg);
	game->Draw(x1 + 12, y + 8, PIXEL_SOLID, fg + bg);
	game->Draw(x1 + 13, y + 7, PIXEL_SOLID, fg + bg);
}

void Menu::PressButtonAnimation(CrossingRoadGame* game, const int& x, 
	const int& y, vector<wstring>& Strings)
{
	// clear old button 
	game->Fill(x0 - 2, y - 4, x1 + 2, y + 8, L' ', COLOUR::BG_BLUE);
	game->ConsOutput();

	// Vẽ hiệu ứng nhấn nút
	DrawShadowEffect(game,  y - 1);
	DrawPanel(game, x,		y + 1, Strings, FG_DARK_YELLOW, BG_DARK_YELLOW);
	// +1 là hiệu ứng hạ xuống

	// Vẽ hiệu ứng pháo hoa
	for (int i = 0; i < 3; ++i) {
		if (i == 0) {
			Splash1(game, y, FG_DARK_YELLOW, BG_DARK_YELLOW);
		}
		else if (i == 1) {
			Splash1(game, y, FG_BLUE, BG_BLUE);
			Splash2(game, y, FG_DARK_YELLOW, BG_DARK_YELLOW);
		}
		else if (i == 2) {
			Splash2(game, y, FG_BLUE, BG_BLUE);
			Splash3(game, y, FG_DARK_YELLOW, BG_DARK_YELLOW);
		}

		game->ConsOutput();
		std::this_thread::sleep_for(std::chrono::milliseconds(int(33)));
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(int(310)));
}
void Menu::DrawOptionalUI(CrossingRoadGame* game, const int& x, 
	const int& y, vector<wstring>& Strings)
{
	// -1 là hiệu ứng nâng lên
	DrawShadowEffect(game, y - 1);
	DrawPanel(game, x,     y - 1, Strings, FG_YELLOW, BG_YELLOW);
}
void Menu::DrawNormalUI(CrossingRoadGame* game, const int& x, 
	const int& y, vector<wstring>& Strings) 
{
	const int _y = y - 2;

	game->DrawLine(x0 + 1, _y, x1 - 1, _y,  PIXEL_SOLID, FG_GREY + BG_GREY);
	game->DrawLine(x0 + 1, _y+6, x1 - 1, _y+6, PIXEL_SOLID, FG_GREY + BG_GREY);


	for (int dy = 1; dy <= 5; dy += 1)
	{
		game->Draw(x0, _y + dy, PIXEL_SOLID, FG_GREY + BG_GREY);
		game->Draw(x1, _y + dy, PIXEL_SOLID, FG_GREY + BG_GREY);
	}

	game->Draw(x0, _y + 6, PIXEL_SOLID, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x1, _y + 6, PIXEL_SOLID, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x0, _y + 7, x1, _y + 7, PIXEL_SOLID, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x0 + 1, _y + 8, x1 - 1, _y + 8, PIXEL_SOLID, FG_DARK_GREY + BG_DARK_GREY);

	// Xuất chữ
	for (int i = 0; i < 3; i++) {
		game->DrawString(x, y + i, Strings[i], FG_GREY + BG_BLUE);
	}
}

void Menu::UpdateNewgameUI(CrossingRoadGame*& game, const int& opt) {
	if (opt == MENU_OPTION::NEWGAME_OPT)
		DrawOptionalUI(game, C_NEWGAME.X, C_NEWGAME.Y, m_Newgame);
	else
		DrawNormalUI(game, C_NEWGAME.X, C_NEWGAME.Y, m_Newgame);
}
void Menu::UpdateLoadgameUI(CrossingRoadGame*& game, const int& opt) {
	if (opt == MENU_OPTION::LOADGAME_OPT)
		DrawOptionalUI(game, C_LOADGAME.X, C_LOADGAME.Y, m_Loadgame);
	else
		DrawNormalUI(game, C_LOADGAME.X, C_LOADGAME.Y, m_Loadgame);
}
void Menu::UpdateLBUI(CrossingRoadGame*& game, const int& opt) {
	if (opt == MENU_OPTION::LB_OPT)
		DrawOptionalUI(game, C_LB.X, C_LB.Y, m_LB);
	else
		DrawNormalUI(game, C_LB.X, C_LB.Y, m_LB);
}
void Menu::UpdateSettingUI(CrossingRoadGame*& game, const int& opt) {
	if (opt == MENU_OPTION::SETTING_OPT)
		DrawOptionalUI(game, C_SETTING.X, C_SETTING.Y, m_Setting);
	else
		DrawNormalUI(game, C_SETTING.X, C_SETTING.Y, m_Setting);
}
void Menu::UpdateCreditUI(CrossingRoadGame*& game, const int& opt) {
	if (opt == MENU_OPTION::CREDIT_OPT)
		DrawOptionalUI(game, C_CREDIT.X, C_CREDIT.Y, m_Credit);
	else
		DrawNormalUI(game, C_CREDIT.X, C_CREDIT.Y, m_Credit);
}
void Menu::UpdateExitUI(CrossingRoadGame*& game, const int& opt) {
	if (opt == MENU_OPTION::EXIT_OPT)
		DrawOptionalUI(game, C_EXIT.X, C_EXIT.Y, m_Exit);
	else
		DrawNormalUI(game, C_EXIT.X, C_EXIT.Y, m_Exit);
}

void Menu::UpdateMenuTitle(CrossingRoadGame*& game, 
	const int& innerOfset, const int& outerOfset) 
{
	static const int _deltaY = -10;
	//Inner
	//C
	int xOfset = 16;
	game->Fill(5 + xOfset, 12 + innerOfset + _deltaY, 7 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(4 + xOfset, 13 + innerOfset + _deltaY, 4 + xOfset, 16 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(8 + xOfset, 12 + innerOfset + _deltaY, 11 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(9 + xOfset, 13 + innerOfset + _deltaY, 12 + xOfset, 13 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(8 + xOfset, 17 + innerOfset + _deltaY, 11 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(9 + xOfset, 16 + innerOfset + _deltaY, 12 + xOfset, 16 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	//R
	game->Fill(14 + xOfset, 12 + innerOfset + _deltaY, 17 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(19 + xOfset, 12 + innerOfset + _deltaY, 21 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(22 + xOfset, 14 + innerOfset + _deltaY, 22 + xOfset, 16 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Draw(22 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Draw(18 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Draw(18 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	//O
	game->Fill(24 + xOfset, 13 + innerOfset + _deltaY, 27 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(29 + xOfset, 13 + innerOfset + _deltaY, 32 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(25 + xOfset, 12 + innerOfset + _deltaY, 31 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(25 + xOfset, 18 + innerOfset + _deltaY, 31 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	//S
	game->Fill(35 + xOfset, 12 + innerOfset + _deltaY, 42 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(34 + xOfset, 13 + innerOfset + _deltaY, 37 + xOfset, 14 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(35 + xOfset, 16 + innerOfset + _deltaY, 36 + xOfset, 16 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(35 + xOfset, 15 + innerOfset + _deltaY, 41 + xOfset, 15 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(39 + xOfset, 16 + innerOfset + _deltaY, 42 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(39 + xOfset, 16 + innerOfset + _deltaY, 42 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(34 + xOfset, 18 + innerOfset + _deltaY, 41 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	//S
	game->Fill(35 + 10 + xOfset, 12 + innerOfset + _deltaY, 42 + 10 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(34 + 10 + xOfset, 13 + innerOfset + _deltaY, 37 + 10 + xOfset, 14 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(35 + 10 + xOfset, 16 + innerOfset + _deltaY, 36 + 10 + xOfset, 16 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(35 + 10 + xOfset, 15 + innerOfset + _deltaY, 41 + 10 + xOfset, 15 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(39 + 10 + xOfset, 16 + innerOfset + _deltaY, 42 + 10 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(39 + 10 + xOfset, 16 + innerOfset + _deltaY, 42 + 10 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(34 + 10 + xOfset, 18 + innerOfset + _deltaY, 41 + 10 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	//I
	game->Fill(54 + xOfset, 12 + innerOfset + _deltaY, 57 + xOfset, 18 + _deltaY, L' ', COLOUR::BG_WHITE);

	//N
	game->Fill(59 + xOfset, 12 + innerOfset + _deltaY, 61 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(62 + xOfset, 13 + innerOfset + _deltaY, 62 + xOfset, 15 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(63 + xOfset, 15 + innerOfset + _deltaY, 63 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(64 + xOfset, 12 + innerOfset + _deltaY, 66 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);


	//G
	game->Fill(70 + xOfset, 12 + innerOfset + _deltaY, 76 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(69 + xOfset, 13 + innerOfset + _deltaY, 72 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(70 + xOfset, 18 + innerOfset + _deltaY, 76 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(75 + xOfset, 15 + innerOfset + _deltaY, 77 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Draw(74 + xOfset, 15 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	//R
	game->Fill(14 + 71 + xOfset, 12 + innerOfset + _deltaY, 17 + 71 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(19 + 71 + xOfset, 12 + innerOfset + _deltaY, 21 + 71 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(22 + 71 + xOfset, 14 + innerOfset + _deltaY, 22 + 71 + xOfset, 16 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Draw(22 + 71 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Draw(18 + 71 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Draw(18 + 71 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	//O
	game->Fill(24 + 71 + xOfset, 13 + innerOfset + _deltaY, 27 + 71 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(29 + 71 + xOfset, 13 + innerOfset + _deltaY, 32 + 71 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(25 + 71 + xOfset, 12 + innerOfset + _deltaY, 31 + 71 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(25 + 71 + xOfset, 18 + innerOfset + _deltaY, 31 + 71 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	//A
	game->Fill(105 + xOfset, 13 + innerOfset + _deltaY, 108 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(110 + xOfset, 13 + innerOfset + _deltaY, 113 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(106 + xOfset, 12 + innerOfset + _deltaY, 112 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Draw(109 + xOfset, 16 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	//D
	game->Fill(115 + xOfset, 12 + innerOfset + _deltaY, 118 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(119 + xOfset, 12 + innerOfset + _deltaY, 122 + xOfset, 12 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(119 + xOfset, 18 + innerOfset + _deltaY, 122 + xOfset, 18 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);
	game->Fill(120 + xOfset, 13 + innerOfset + _deltaY, 123 + xOfset, 17 + innerOfset + _deltaY, L' ', COLOUR::BG_WHITE);

	//Outline
	//C
	game->Fill(4 + xOfset, 18 + outerOfset + _deltaY, 4 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(5 + xOfset, 20 + outerOfset + _deltaY, 12 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(12 + xOfset, 19 + outerOfset + _deltaY, 13 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(13 + xOfset, 14 + outerOfset + _deltaY, 13 + xOfset, 18 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(8 + xOfset, 14 + outerOfset + _deltaY, 8 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	//R
	game->Fill(14 + xOfset, 20 + outerOfset + _deltaY, 23 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(23 + xOfset, 14 + outerOfset + _deltaY, 23 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(18 + xOfset, 14 + outerOfset + _deltaY, 18 + xOfset, 16 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(18 + xOfset, 14 + outerOfset + _deltaY, 18 + xOfset, 16 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Draw(22 + xOfset, 13 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Draw(22 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Draw(24 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	//0
	game->Fill(25 + xOfset, 20 + outerOfset + _deltaY, 32 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(32 + xOfset, 19 + outerOfset + _deltaY, 33 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(33 + xOfset, 14 + outerOfset + _deltaY, 33 + xOfset, 18 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(28 + xOfset, 14 + outerOfset + _deltaY, 28 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	//S
	game->Draw(34 + xOfset, 16 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Draw(43 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Draw(42 + xOfset, 15 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(35 + xOfset, 17 + outerOfset + _deltaY, 35 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(34 + xOfset, 20 + outerOfset + _deltaY, 42 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(42 + xOfset, 18 + outerOfset + _deltaY, 43 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(43 + xOfset, 13 + outerOfset + _deltaY, 43 + xOfset, 15 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	//S
	game->Draw(34 + 10 + xOfset, 16 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Draw(43 + 10 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Draw(42 + 10 + xOfset, 15 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(35 + 10 + xOfset, 17 + outerOfset + _deltaY, 35 + 10 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(34 + 10 + xOfset, 20 + outerOfset + _deltaY, 42 + 10 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(42 + 10 + xOfset, 18 + outerOfset + _deltaY, 43 + 10 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(43 + 10 + xOfset, 13 + outerOfset + _deltaY, 43 + 10 + xOfset, 15 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	//ING
	game->Fill(54 + xOfset, 20 + outerOfset + _deltaY, 62 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(58 + xOfset, 13 + outerOfset + _deltaY, 58 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(62 + xOfset, 17 + outerOfset + _deltaY, 62 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(63 + xOfset, 19 + outerOfset + _deltaY, 64 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(65 + xOfset, 20 + outerOfset + _deltaY, 68 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(68 + xOfset, 13 + outerOfset + _deltaY, 68 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(70 + xOfset, 20 + outerOfset + _deltaY, 77 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(77 + xOfset, 19 + outerOfset + _deltaY, 78 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(78 + xOfset, 15 + outerOfset + _deltaY, 78 + xOfset, 18 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(77 + xOfset, 13 + outerOfset + _deltaY, 77 + xOfset, 14 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(73 + xOfset, 15 + outerOfset + _deltaY, 73 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(69 + xOfset, 19 + outerOfset + _deltaY, 69 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	//R
	game->Fill(14 + xOfset + 71, 20 + outerOfset + _deltaY, 23 + 71 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(23 + xOfset + 71, 14 + outerOfset + _deltaY, 23 + 71 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(18 + xOfset + 71, 14 + outerOfset + _deltaY, 18 + 71 + xOfset, 16 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(18 + xOfset + 71, 14 + outerOfset + _deltaY, 18 + 71 + xOfset, 16 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Draw(22 + xOfset + 71, 13 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Draw(22 + xOfset + 71, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Draw(24 + xOfset + 71, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	//0 
	game->Fill(25 + xOfset + 71, 20 + outerOfset + _deltaY, 32 + 71 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(32 + xOfset + 71, 19 + outerOfset + _deltaY, 33 + 71 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(33 + xOfset + 71, 14 + outerOfset + _deltaY, 33 + 71 + xOfset, 18 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(28 + xOfset + 71, 14 + outerOfset + _deltaY, 28 + 71 + xOfset, 17 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);

	//AD
	game->Fill(105 + xOfset, 20 + outerOfset + _deltaY, 122 + xOfset, 20 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(109 + xOfset, 18 + outerOfset + _deltaY, 109 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(109 + xOfset, 14 + outerOfset + _deltaY, 109 + xOfset, 15 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(114 + xOfset, 14 + outerOfset + _deltaY, 114 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(122 + xOfset, 19 + outerOfset + _deltaY, 123 + xOfset, 19 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
	game->Fill(123 + xOfset, 18 + outerOfset + _deltaY, 123 + xOfset, 18 + outerOfset + _deltaY, L' ', COLOUR::BG_BLACK);
}


Menu::Menu(CrossingRoadGame* game) {
	m_Newgame.reserve(3);
	m_Newgame.push_back(L"█▄  █ █▀▀▀ █   █    █▀▀█ █▀▀█ █▀▄▀█ █▀▀▀");
	m_Newgame.push_back(L"█ █ █ █▀▀▀ █ █ █    █ ▄▄ █▄▄█ █ █ █ █▀▀▀");
	m_Newgame.push_back(L"█  ▀█ █▄▄▄ █▄▀▄█    █▄▄█ █  █ █   █ █▄▄▄");


	m_Loadgame.reserve(3);
	m_Loadgame.push_back(L"█    █▀▀▀█ █▀▀█ █▀▀▄    █▀▀█ █▀▀█ █▀▄▀█ █▀▀▀");
	m_Loadgame.push_back(L"█    █   █ █▄▄█ █  █    █ ▄▄ █▄▄█ █ █ █ █▀▀▀");
	m_Loadgame.push_back(L"█▄▄█ █▄▄▄█ █  █ █▄▄▀    █▄▄█ █  █ █   █ █▄▄▄");


	m_LB.reserve(3);
	m_LB.push_back(L"█    █▀▀▀ █▀▀█ █▀▀▄ █▀▀▀ █▀▀█ █▀▀█ █▀▀▀█ █▀▀█ █▀▀█ █▀▀▄");
	m_LB.push_back(L"█    █▀▀▀ █▄▄█ █  █ █▀▀▀ █▄▄▀ █▀▀▄ █   █ █▄▄█ █▄▄▀ █  █");
	m_LB.push_back(L"█▄▄█ █▄▄▄ █  █ █▄▄▀ █▄▄▄ █  █ █▄▄█ █▄▄▄█ █  █ █  █ █▄▄▀");

	m_Setting.reserve(3);
	m_Setting.push_back(L"█▀▀▀█ █▀▀▀ ▀▀█▀▀ ▀▀█▀▀ ▀█▀  █▄  █ █▀▀█");
	m_Setting.push_back(L"▀▀▀▄▄ █▀▀▀   █     █    █   █ █ █ █ ▄▄");
	m_Setting.push_back(L"█▄▄▄█ █▄▄▄   █     █   ▄█▄  █  ▀█ █▄▄█");


	m_Credit.reserve(3);
	m_Credit.push_back(L"█▀▀█ █▀▀█ █▀▀▀ █▀▀▄ ▀█▀ ▀▀█▀▀");
	m_Credit.push_back(L"█    █▄▄▀ █▀▀▀ █  █  █    █  ");
	m_Credit.push_back(L"█▄▄█ █  █ █▄▄▄ █▄▄▀ ▄█▄   █  ");


	m_Exit.reserve(3);
	m_Exit.push_back(L"█▀▀▀ ▀▄ ▄▀ ▀█▀ ▀▀█▀▀");
	m_Exit.push_back(L"█▀▀▀   █    █    █  ");
	m_Exit.push_back(L"█▄▄▄ ▄▀ ▀▄ ▄█▄   █  ");
}
