#include "StateExit.h"

const int StateExit::M_S_SRC_X0 = 4;
const int StateExit::M_S_SRC_Y0 = 4;
const int StateExit::M_S_SRC_X1 = 155;
const int StateExit::M_S_SRC_Y1 = 91;

bool StateExit::Update(float fElapsedTime) {
	OpenWindowEffect();

	DrawExitScreen();
	DecorateExitScreen();
	game->ConsOutput();

	DrawMessage();

	//// clear screen
	//game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLACK);
	//this_thread::sleep_for(std::chrono::milliseconds(1000));

	GameEngine::m_bAtomActive = 0;
	return 0;
}
bool StateExit::OnStateEnter() {
	this->game = game;
	ByeSound.OpenByeSound();
	ByeSound.PlayByeSound();
	// clear screen
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);

	return 1;
}
bool StateExit::OnStateExit() {
	ByeSound.CloseSound();
	return 1;
}


void StateExit::DrawMessage() {
	static const int _tm = 10;
	this_thread::sleep_for(std::chrono::milliseconds(400));

	Thanks(27, 29, FG_DARK_GREY, BG_DARK_GREY);
	game->ConsOutput();
	for (int i = 1; i < 15; ++i) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		Thanks(27, 30 - i, FG_CYAN, BG_CYAN);

		if (i < 8) {
			Thanks(27, 29 - i, FG_DARK_GREY, BG_DARK_GREY);
		}
		else {
			Thanks(27, 29 - i, FG_BLACK, BG_BLACK);
		}

		game->ConsOutput();
	}

	For(102, 29, FG_DARK_GREY, BG_DARK_GREY);
	game->ConsOutput();
	for (int i = 1; i < 15; ++i) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		For(102, 30 - i, FG_CYAN, BG_CYAN);

		if (i < 8) {
			For(102, 29 - i, FG_DARK_GREY, BG_DARK_GREY);
		}
		else {
			For(102, 29 - i, FG_BLACK, BG_BLACK);
		}

		game->ConsOutput();
	}

	Playing(46, 47, FG_DARK_GREY, BG_DARK_GREY);
	game->ConsOutput();
	for (int i = 1; i < 15; ++i) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		Playing(46, 48 - i, FG_CYAN, BG_CYAN);

		if (i < 8) {
			Playing(46, 47 - i, FG_DARK_GREY, BG_DARK_GREY);
		}
		else {
			Playing(46, 47 - i, FG_BLACK, BG_BLACK);
		}

		game->ConsOutput();
	}

	HeartsEffect();

	// BYE BYE
	ByeBye();
}

void StateExit::HeartsEffect() {
	Heart1(7, 38);
	Heart2(120, 40);
	Heart3(135, 60);
}

void StateExit::Heart3(const int& _x, const int& _y) {
	Heart3_LeftWing(_x, _y);
	Heart3_MainHeart(_x, _y);
	Heart3_RightWing(_x, _y);
	Heart3_SubHeart(_x, _y);
	Heart3_SubHeart(_x, _y);
}
void StateExit::Heart3_SubHeart(const int& _x, const int& _y) {
	Plus(_x - 4, _y + 4);
	MiniHeart(_x + 10, _y + 7);
}
void StateExit::Heart3_LeftWing(const int& _x, const int& _y) {
	// Vẽ viền
	game->DrawLine(_x, _y, _x + 1, _y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x, _y + 1, _x + 1, _y + 2, 9608, FG_BLACK + BG_BLACK);
	
	// Vẽ nền
	game->Draw(_x + 1, _y + 1, 9608, FG_GREY + BG_GREY);
}
void StateExit::Heart3_MainHeart(const int& _x, const int& _y) {
	// Vẽ viền
	game->DrawLine(_x + 3, _y , _x + 4, _y , 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 6, _y , _x + 7, _y , 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 2, _y + 1, _x + 2, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 8, _y + 1, _x + 8, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 3, _y + 4, _x + 5, _y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 6, _y + 5, _x + 7, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 5, _y + 1, 9608, FG_BLACK + BG_BLACK);

	//Vẽ bóng
	game->DrawLine(_x + 5, _y + 4, _x + 7, _y + 2, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(_x + 5, _y + 5, _x + 7, _y + 3, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + 4, _y + 4, 9608, FG_DARK_RED + BG_DARK_RED);

	// Vẽ nền
	game->DrawLine(_x + 3, _y + 1, _x + 4, _y + 1, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 6, _y + 1, _x + 7, _y + 1, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 3, _y + 2, _x + 6, _y + 2, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 3, _y + 3, _x + 5, _y + 3, 9608, FG_RED + BG_RED);

	// Vẽ ánh sáng
	game->Draw(_x + 3, _y + 1, 9608, FG_WHITE + BG_WHITE);
}
void StateExit::Heart3_RightWing(const int& _x, const int& _y) {
	game->DrawLine(_x + 9, _y, _x + 10, _y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 9, _y + 2, _x + 10, _y + 1, 9608, FG_BLACK + BG_BLACK);

	// Vẽ nền
	game->Draw(_x + 9, _y + 1, 9608, FG_GREY + BG_GREY);
}

void StateExit::Heart2(const int& _x, const int& _y) {
	Heart2_LeftWing(_x, _y);
	Heart2_MainHeart(_x, _y);
	Heart2_RightWing(_x, _y);
	Heart2_SubHeart(_x, _y);
	Heart2_SubHeart(_x, _y);
}
void StateExit::Heart2_SubHeart(const int& _x, const int& _y) {
	Plus(_x + 5, _y - 1);
	Plus(_x +16, _y + 13);
	MiniHeart(_x + 1, _y + 16);
	MiniHeart(_x + 22, _y - 4);
}
void StateExit::Heart2_LeftWing(const int& _x, const int& _y) {
	// Vẽ viền
	game->DrawLine(_x + 1, _y + 3, _x + 2, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x	 , _y + 6, _x	 , _y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 1, _y + 8, _x + 1, _y + 9, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 4, _y + 7, _x + 4, _y + 9, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 2, _y +10, _x + 3, _y +10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x	 , _y + 4, _x + 2, _y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 3, _y + 4, _x + 5, _y + 6, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 2, _y + 8, 9608, FG_BLACK + BG_BLACK);

	// Vẽ bóng
	game->Draw(_x + 3, _y + 9, 9608, FG_GREY + BG_GREY);

	// Vẽ nền
	game->DrawLine(_x + 1, _y + 4, _x + 2, _y + 4, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 2, _y + 5, _x + 3, _y + 5, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 3, _y + 6, _x + 4, _y + 6, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 1, _y + 6, _x + 1, _y + 7, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 2, _y + 7, _x + 3, _y + 7, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + 2, _y + 9, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + 3, _y + 8, 9608, FG_WHITE + BG_WHITE);
}
void StateExit::Heart2_MainHeart(const int& _x, const int& _y) {
	// Vẽ viền
	game->DrawLine(_x + 6, _y + 5, _x + 7, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 8, _y + 6, _x + 9, _y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x +10, _y + 6, _x +10, _y + 8, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x +12, _y + 4, _x +14, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x +16, _y + 6, _x +16, _y + 9, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 8, _y +13, _x + 9, _y +13, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x +10, _y +14, _x +11, _y +14, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 5, _y +10, _x + 7, _y +12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x +12, _y +13, _x +15, _y +10, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 11, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 15, _y + 5, 9608, FG_BLACK + BG_BLACK);

	//Vẽ bóng
	game->DrawLine(_x + 10, _y + 13, _x + 11, _y + 13, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(_x + 12, _y + 12, _x + 14, _y + 10, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(_x + 13, _y +  5, _x + 14, _y + 5, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(_x + 14, _y +  6, _x + 15, _y + 6, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(_x + 15, _y +  7, _x + 15, _y + 9, 9608, FG_DARK_RED + BG_DARK_RED);

	// Vẽ nền
	game->DrawLine(_x + 6, _y + 6, _x + 7, _y + 6, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 7, _y + 7, _x + 8, _y + 7, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 6, _y + 8, _x + 9, _y + 8, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 7, _y + 9, _x +14, _y + 9, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 8, _y +10, _x +13, _y +10, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 7, _y +11, _x +12, _y +11, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 8, _y +12, _x +11, _y +12, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 5, _y + 7, _x + 5, _y +9, 9608, FG_RED + BG_RED);
	game->DrawLine(_x +11, _y + 6, _x +13, _y +6, 9608, FG_RED + BG_RED);
	game->Draw(_x + 12, _y +  5, 9608, FG_RED + BG_RED);
	game->Draw(_x +  6, _y + 10, 9608, FG_RED + BG_RED);
	game->Fill(_x + 11, _y +  7, _x + 14, _y + 8, 9608, FG_RED + BG_RED);

	// Vẽ ánh sáng
	game->DrawLine(_x + 6, _y + 9, _x + 7, _y + 10, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + 6, _y + 7, 9608, FG_WHITE + BG_WHITE);
}
void StateExit::Heart2_RightWing(const int& _x, const int& _y) {
	// Vẽ viền
	game->DrawLine(_x + 15, _y + 2, _x + 15, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 17, _y    , _x + 18, _y	   , 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 19, _y + 3, _x + 19, _y	+ 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 19, _y + 6, _x + 19, _y	+ 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 17, _y + 7, _x + 18, _y	+ 8, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 17, _y + 3, _x + 19, _y	+ 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 16, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 18, _y + 5, 9608, FG_BLACK + BG_BLACK);

	// Vẽ bóng
	game->DrawLine(_x + 15, _y + 4, _x + 18, _y + 7, 9608, FG_GREY + BG_GREY);

	// Vẽ nền
	game->DrawLine(_x + 17, _y + 1, _x + 18, _y + 1, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 16, _y + 2, _x + 17, _y + 2, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 16, _y + 3, _x + 17, _y + 4, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 16, _y + 4, _x + 18, _y + 6, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 18, _y + 3, _x + 18, _y + 4, 9608, FG_WHITE + BG_WHITE);
}

void StateExit::Heart1(const int& _x, const int& _y) {
	Heart1_LeftWing(_x, _y);
	Heart1_MainHeart(_x, _y);
	Heart1_RightWing(_x, _y);
	Heart1_SubHeart(_x, _y);
	Heart1_SubHeart(_x, _y);
}
void StateExit::Heart1_SubHeart(const int& _x, const int& _y) {
	Plus(_x + 14, _y + 3);
	Plus(_x + 27, _y + 19);
	MiniHeart(_x + 4, _y + 8);
	MiniHeart(_x +20, _y - 2);
	MiniHeart(_x + 19, _y + 26);
}
void StateExit::Heart1_RightWing(const int& _x, const int& _y) {
	// Vẽ viền
	game->DrawLine(_x + 25, _y + 6, _x + 25, _y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 26, _y + 4, _x + 26, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 28, _y + 2, _x + 29, _y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 30, _y + 3, _x + 30, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 31, _y + 5, _x + 31, _y + 8, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 32, _y + 8, _x + 32, _y +10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 31, _y +11, _x + 31, _y +13, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 27, _y +15, _x + 29, _y +15, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 24, _y + 8, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 27, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 28, _y + 7, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 29, _y + 6, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 29, _y +10, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 30, _y + 9, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 30, _y +12, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 30, _y +14, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 26, _y +14, 9608, FG_BLACK + BG_BLACK);

	// Vẽ bóng
	game->DrawLine(_x + 29, _y + 3, _x + 29, _y + 5, 9608, FG_GREY + BG_GREY);
	game->DrawLine(_x + 30, _y + 6, _x + 30, _y + 8, 9608, FG_GREY + BG_GREY);
	game->DrawLine(_x + 31, _y + 9, _x + 31, _y +10, 9608, FG_GREY + BG_GREY);
	game->DrawLine(_x + 27, _y +14, _x + 29, _y +14, 9608, FG_GREY + BG_GREY);
	game->Draw(_x + 28, _y + 6, 9608, FG_GREY + BG_GREY);
	game->Draw(_x + 29, _y + 9, 9608, FG_GREY + BG_GREY);
	game->Draw(_x + 30, _y +11, 9608, FG_GREY + BG_GREY);
	game->Draw(_x + 30, _y +13, 9608, FG_GREY + BG_GREY);

	// Vẽ nền
	game->DrawLine(_x + 25, _y + 8, _x + 25, _y + 10, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 26, _y + 6, _x + 26, _y + 13, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 27, _y + 4, _x + 27, _y + 13, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 28, _y + 3, _x + 28, _y +  5, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 28, _y + 8, _x + 28, _y + 13, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 29, _y + 7, _x + 29, _y +  8, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 29, _y +11, _x + 29, _y + 13, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + 30, _y + 10, 9608, FG_WHITE + BG_WHITE);
}
void StateExit::Heart1_MainHeart(const int& _x, const int& _y) {
	// Vẽ viền
	game->DrawLine(_x + 10, _y + 15, _x + 10, _y + 17, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 12, _y + 13, _x + 15, _y + 13, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 16, _y + 14, _x + 17, _y + 14, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 17, _y + 11, _x + 17, _y + 13, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 18, _y + 9, _x + 18, _y + 10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 19, _y + 8, _x + 22, _y + 8, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 23, _y + 9, _x + 24, _y + 9, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 25, _y + 11, _x + 25, _y + 17, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 24, _y + 18, _x + 24, _y + 19, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 16, _y + 22, _x + 21, _y + 22, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 11, _y + 14, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 24, _y + 10, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 22, _y + 21, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 23, _y + 20, 9608, FG_BLACK + BG_BLACK);

	//Vẽ bóng
	game->DrawLine(_x + 21, _y + 9, _x + 22, _y + 9, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(_x + 22, _y + 10, _x + 23, _y + 10, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(_x + 22, _y + 17, _x + 24, _y + 17, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(_x + 22, _y + 18, _x + 23, _y + 18, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(_x + 21, _y + 19, _x + 23, _y + 19, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(_x + 20, _y + 20, _x + 22, _y + 20, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(_x + 19, _y + 21, _x + 21, _y + 21, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 23, _y + 11, _x + 24, _y + 16, 9608, FG_DARK_RED + BG_DARK_RED);

	// Vẽ nền
	game->DrawLine(_x + 19, _y + 9, _x + 20, _y + 9, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 19, _y + 10, _x + 21, _y + 10, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 12, _y + 14, _x + 15, _y + 14, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 11, _y + 15, _x + 22, _y + 15, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 13, _y + 16, _x + 22, _y + 16, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 13, _y + 17, _x + 21, _y + 17, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 14, _y + 18, _x + 21, _y + 18, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 16, _y + 19, _x + 20, _y + 19, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 13, _y + 20, _x + 19, _y + 20, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 15, _y + 21, _x + 18, _y + 21, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 11, _y + 16, _x + 11, _y + 18, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 12, _y + 18, _x + 12, _y + 19, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 13, _y + 19, _x + 14, _y + 19, 9608, FG_RED + BG_RED);
	game->Fill(_x + 18, _y + 11, _x + 22, _y + 14, 9608, FG_RED + BG_RED);

	// Vẽ ánh sáng
	game->DrawLine(_x + 12, _y + 16, _x + 12, _y + 17, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + 13, _y + 18, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + 15, _y + 19, 9608, FG_WHITE + BG_WHITE);
}
void StateExit::Heart1_LeftWing(const int& _x, const int& _y) {
	// Vẽ viền
	game->DrawLine(_x, _y + 20, _x, _y + 21, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 1, _y + 19, _x + 2, _y + 19, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 3, _y + 18, _x + 4, _y + 18, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 5, _y + 17, _x + 8, _y + 17, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 9, _y + 18, _x + 10, _y + 18, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 13, _y + 21, _x + 14, _y + 21, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 15, _y + 22, _x + 15, _y + 24, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 6, _y + 22, _x + 7, _y + 22, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 11, _y + 26, _x + 13, _y + 26, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 8, _y + 26, _x + 9, _y + 26, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 5, _y + 25, _x + 7, _y + 25, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 2, _y + 23, _x + 5, _y + 23, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 1, _y + 22, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 11, _y + 19, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 12, _y + 20, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 4, _y + 24, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 8, _y + 24, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 9, _y + 23, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 10, _y + 25, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 11, _y + 24, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 14, _y + 25, 9608, FG_BLACK + BG_BLACK);

	// Vẽ bóng
	game->DrawLine(_x + 2, _y + 22, _x + 5, _y + 22, 9608, FG_GREY + BG_GREY);
	game->DrawLine(_x + 5, _y + 24, _x + 7, _y + 24, 9608, FG_GREY + BG_GREY);
	game->DrawLine(_x + 8, _y + 25, _x + 9, _y + 25, 9608, FG_GREY + BG_GREY);
	game->DrawLine(_x + 12, _y + 25, _x + 13, _y + 25, 9608, FG_GREY + BG_GREY);
	game->DrawLine(_x + 13, _y + 24, _x + 14, _y + 24, 9608, FG_GREY + BG_GREY);
	game->DrawLine(_x + 14, _y + 22, _x + 14, _y + 23, 9608, FG_GREY + BG_GREY);
	game->Draw(_x + 1, _y + 21, 9608, FG_GREY + BG_GREY);
	game->Draw(_x + 8, _y + 23, 9608, FG_GREY + BG_GREY);

	// Vẽ nền
	game->DrawLine(_x + 5, _y + 18, _x + 8, _y + 18, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 3, _y + 19, _x + 10, _y + 19, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 1, _y + 20, _x + 11, _y + 20, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 2, _y + 21, _x + 12, _y + 21, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 8, _y + 22, _x + 13, _y + 22, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 10, _y + 23, _x + 13, _y + 23, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 6, _y + 23, _x + 7, _y + 23, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 9, _y + 24, _x + 10, _y + 24, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + 12, _y + 24, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + 11, _y + 25, 9608, FG_WHITE + BG_WHITE);
}

void StateExit::Plus(const int& _x, const int& _y) {
	// Vẽ nền
	game->Draw(_x + 1, _y, 9608, FG_MAGENTA + BG_MAGENTA);
	game->Draw(_x + 1, _y + 2, 9608, FG_MAGENTA + BG_MAGENTA);
	game->DrawLine(_x, _y + 1, _x + 2, _y + 1, 9608, FG_MAGENTA + BG_MAGENTA);

	// Vẽ bóng
	game->Draw(_x, _y + 2, 9608, FG_DARK_MAGENTA + BG_DARK_MAGENTA);
	game->Draw(_x + 2, _y + 2, 9608, FG_DARK_MAGENTA + BG_DARK_MAGENTA);
	game->Draw(_x + 1, _y + 3, 9608, FG_DARK_MAGENTA + BG_DARK_MAGENTA);
}
void StateExit::MiniHeart(const int& _x, const int& _y) {
	// Vẽ nền
	game->DrawLine(_x, _y, _x + 1, _y, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 3, _y, _x + 4, _y, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x, _y + 1, _x + 4, _y + 1, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 1, _y + 2, _x + 3, _y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 2, _y + 3, 9608, FG_YELLOW + BG_YELLOW);

	// Vẽ bóng
	game->Draw(_x	 , _y + 2, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Draw(_x + 1, _y + 3, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Draw(_x + 2, _y + 4, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Draw(_x + 3, _y + 3, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Draw(_x + 4, _y + 2, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
}

void StateExit::ByeBye() {
	static const int _x1 = M_S_SRC_X0 + 35;
	static const int _x2 = _x1 + 44;
	static const int _y = M_S_SRC_Y1 - 29;
	static const int  _delayTm = 50;

	this_thread::sleep_for(std::chrono::milliseconds(_delayTm));
	Bye(_x1 - 1, _y + 1, FG_DARK_GREY, BG_DARK_GREY);
	Bye(_x2 - 1, _y + 1, FG_DARK_GREY, BG_DARK_GREY);
	game->ConsOutput();

	this_thread::sleep_for(std::chrono::milliseconds(_delayTm));
	// Xóa cũ
	Bye(_x1 - 1, _y + 1, FG_CYAN, BG_CYAN);
	Bye(_x2 - 1, _y + 1, FG_CYAN, BG_CYAN);
	// Vẽ mới
	Bye(_x1, _y, FG_DARK_BLUE, BG_DARK_BLUE);
	Bye(_x2, _y, FG_DARK_BLUE, BG_DARK_BLUE);
	game->ConsOutput();

	this_thread::sleep_for(std::chrono::milliseconds(_delayTm));
	// Xóa cũ
	Bye(_x1, _y, FG_BLUE, BG_BLUE);
	Bye(_x2, _y, FG_BLUE, BG_BLUE);
	// Vẽ mới
	Bye(_x1 + 1, _y - 1, FG_DARK_MAGENTA, BG_DARK_MAGENTA);
	Bye(_x2 + 1, _y - 1, FG_DARK_MAGENTA, BG_DARK_MAGENTA);
	game->ConsOutput();


	this_thread::sleep_for(std::chrono::milliseconds(_delayTm));
	// Xóa cũ
	Bye(_x1 + 1, _y - 1, FG_MAGENTA, BG_MAGENTA);
	Bye(_x2 + 1, _y - 1, FG_MAGENTA, BG_MAGENTA);
	// Vẽ mới
	Bye(_x1 + 2, _y - 2, FG_RED, BG_RED);
	Bye(_x2 + 2, _y - 2, FG_RED, BG_RED);
	game->ConsOutput();
}
void StateExit::Thanks(const int& _x, const int& _y,
	const short& fg, const short& bg)
{
	// T
	game->DrawLine(_x, _y, _x + 4, _y, 9608, fg + bg);
	game->DrawLine(_x + 6, _y, _x + 9, _y, 9608, fg + bg);
	game->DrawLine(_x, _y + 1, _x + 9, _y + 1, 9608, fg + bg);
	game->Fill(_x + 4, _y + 2, _x + 5, _y + 13, 9608, fg + bg);

	// H
	game->Fill(_x + 11, _y, _x + 12, _y + 6, 9608, fg + bg);
	game->Fill(_x + 11, _y + 8, _x + 12, _y + 13, 9608, fg + bg);
	game->Fill(_x + 19, _y, _x + 20, _y + 5, 9608, fg + bg);
	game->Fill(_x + 19, _y + 7, _x + 20, _y + 13, 9608, fg + bg);
	game->DrawLine(_x + 13, _y + 6, _x + 19, _y + 6, 9608, fg + bg);
	game->DrawLine(_x + 12, _y + 7, _x + 18, _y + 7, 9608, fg + bg);

	// A
	game->Fill(_x + 22, _y + 1, _x + 23, _y + 13, 9608, fg + bg);
	game->Fill(_x + 30, _y + 1, _x + 31, _y + 13, 9608, fg + bg);
	game->Fill(_x + 24, _y + 8, _x + 29, _y + 9, 9608, fg + bg);
	game->DrawLine(_x + 23, _y, _x + 30, _y, 9608, fg + bg);
	game->DrawLine(_x + 24, _y + 1, _x + 29, _y + 1, 9608, fg + bg);

	// N
	game->Fill(_x + 33, _y + 1, _x + 34, _y + 13, 9608, fg + bg);
	game->Fill(_x + 41, _y + 1, _x + 42, _y + 13, 9608, fg + bg);
	game->DrawLine(_x + 34, _y, _x + 41, _y, 9608, fg + bg);
	game->DrawLine(_x + 35, _y + 1, _x + 40, _y + 1, 9608, fg + bg);

	// K
	game->Fill(_x + 44, _y, _x + 45, _y + 13, 9608, fg + bg);
	game->Fill(_x + 46, _y + 6, _x + 47, _y + 7, 9608, fg + bg);
	game->Fill(_x + 48, _y + 4, _x + 49, _y + 5, 9608, fg + bg);
	game->Fill(_x + 48, _y + 8, _x + 49, _y + 9, 9608, fg + bg);
	game->DrawLine(_x + 51, _y, _x + 53, _y, 9608, fg + bg);
	game->DrawLine(_x + 50, _y + 1, _x + 53, _y + 1, 9608, fg + bg);
	game->DrawLine(_x + 49, _y + 2, _x + 51, _y + 2, 9608, fg + bg);
	game->DrawLine(_x + 48, _y + 3, _x + 50, _y + 3, 9608, fg + bg);
	game->DrawLine(_x + 51, _y + 13, _x + 53, _y + 13, 9608, fg + bg);
	game->DrawLine(_x + 50, _y + 12, _x + 53, _y + 12, 9608, fg + bg);
	game->DrawLine(_x + 49, _y + 11, _x + 51, _y + 11, 9608, fg + bg);
	game->DrawLine(_x + 48, _y + 10, _x + 50, _y + 10, 9608, fg + bg);

	// S
	game->DrawLine(_x + 56, _y, _x + 64, _y, 9608, fg + bg);
	game->DrawLine(_x + 55, _y + 1, _x + 64, _y + 1, 9608, fg + bg);
	game->DrawLine(_x + 55, _y + 6, _x + 63, _y + 6, 9608, fg + bg);
	game->DrawLine(_x + 56, _y + 7, _x + 64, _y + 7, 9608, fg + bg);
	game->DrawLine(_x + 55, _y + 12,_x + 64, _y + 12, 9608, fg + bg);
	game->DrawLine(_x + 55, _y + 13,_x + 63, _y + 13, 9608, fg + bg);
	game->Fill(_x + 55, _y + 2, _x + 56, _y + 5, 9608, fg + bg);
	game->Fill(_x + 63, _y + 8, _x + 64, _y + 11, 9608, fg + bg);
}
void StateExit::For(const int& _x, const int& _y,
	const short& fg, const short& bg)
{
	// F
	game->DrawLine(_x + 1, _y, _x + 8, _y, 9608, fg + bg);
	game->DrawLine(_x, _y + 1, _x + 8, _y + 1, 9608, fg + bg);
	game->Fill(_x, _y + 2, _x + 1, _y + 13, 9608, fg + bg);
	game->Fill(_x + 2, _y + 6, _x + 5, _y + 7, 9608, fg + bg);

	// O
	game->DrawLine(_x + 11, _y, _x + 18, _y, 9608, fg + bg);
	game->DrawLine(_x + 10, _y + 1, _x + 19, _y + 1, 9608, fg + bg);
	game->DrawLine(_x + 11, _y + 13, _x + 18, _y + 13, 9608, fg + bg);
	game->DrawLine(_x + 10, _y + 12, _x + 19, _y + 12, 9608, fg + bg);
	game->Fill(_x + 10, _y + 2, _x + 11, _y + 11, 9608, fg + bg);
	game->Fill(_x + 18, _y + 2, _x + 19, _y + 11, 9608, fg + bg);

	// R
	game->Fill(_x + 21, _y, _x + 22, _y + 13, 9608, fg + bg);
	game->DrawLine(_x + 23, _y, _x + 29, _y, 9608, fg + bg);
	game->DrawLine(_x + 23, _y + 1, _x + 30, _y + 1, 9608, fg + bg);
	game->Fill(_x + 29, _y + 2, _x + 30, _y + 7, 9608, fg + bg);
	game->DrawLine(_x + 23, _y + 8, _x + 30, _y + 8, 9608, fg + bg);
	game->DrawLine(_x + 23, _y + 9, _x + 29, _y + 9, 9608, fg + bg);
	game->Fill(_x + 26, _y + 10, _x + 27, _y + 12, 9608, fg + bg);
	game->DrawLine(_x + 28, _y + 12, _x + 30, _y + 12, 9608, fg + bg);
	game->DrawLine(_x + 27, _y + 13, _x + 30, _y + 13, 9608, fg + bg);
}
void StateExit::Playing(const int& _x, const int& _y,
	const short& fg, const short& bg)
{
	// P
	game->DrawLine(_x, _y, _x + 8, _y, 9608, fg + bg);
	game->DrawLine(_x, _y + 1, _x + 9, _y + 1, 9608, fg + bg);
	game->Fill(_x, _y + 2, _x + 1, _y + 13, 9608, fg + bg);
	game->Fill(_x + 8, _y + 2, _x + 9, _y + 6, 9608, fg + bg);
	game->DrawLine(_x + 2, _y + 7, _x + 9, _y + 7, 9608, fg + bg);
	game->DrawLine(_x + 2, _y + 8, _x + 8, _y + 8, 9608, fg + bg);

	// L
	game->Fill(_x + 11, _y, _x + 12, _y + 11, 9608, fg + bg);
	game->DrawLine(_x + 11, _y + 12, _x + 19, _y + 12, 9608, fg + bg);
	game->DrawLine(_x + 12, _y + 13, _x + 19, _y + 13, 9608, fg + bg);

	// A
	game->Fill(_x + 21, _y + 1, _x + 22, _y + 13, 9608, fg + bg);
	game->Fill(_x + 29, _y + 1, _x + 30, _y + 13, 9608, fg + bg);
	game->Fill(_x + 23, _y + 8, _x + 28, _y + 9, 9608, fg + bg);
	game->DrawLine(_x + 22, _y, _x + 29, _y, 9608, fg + bg);
	game->DrawLine(_x + 23, _y + 1, _x + 28, _y + 1, 9608, fg + bg);

	// Y
	game->Fill(_x + 32, _y, _x + 33, _y + 6, 9608, fg + bg);
	game->Fill(_x + 40, _y, _x + 41, _y + 6, 9608, fg + bg);
	game->Fill(_x + 36, _y + 9, _x + 37, _y + 13, 9608, fg + bg);
	game->DrawLine(_x + 32, _y + 7, _x + 41, _y + 7, 9608, fg + bg);
	game->DrawLine(_x + 33, _y + 8, _x + 40, _y + 8, 9608, fg + bg);

	// I
	game->Fill(_x + 43, _y, _x + 44, _y + 13, 9608, fg + bg);

	// N
	game->Fill(_x + 46, _y + 1, _x + 47, _y + 13, 9608, fg + bg);
	game->Fill(_x + 54, _y + 1, _x + 55, _y + 13, 9608, fg + bg);
	game->DrawLine(_x + 47, _y, _x + 54, _y, 9608, fg + bg);
	game->DrawLine(_x + 48, _y + 1, _x + 53, _y + 1, 9608, fg + bg);

	// G
	game->DrawLine(_x + 58, _y, _x + 65, _y, 9608, fg + bg);
	game->DrawLine(_x + 59, _y + 1, _x + 66, _y + 1, 9608, fg + bg);
	game->DrawLine(_x + 65, _y + 2, _x + 66, _y + 2, 9608, fg + bg);
	game->DrawLine(_x + 62, _y + 6, _x + 65, _y + 6, 9608, fg + bg);
	game->DrawLine(_x + 62, _y + 7, _x + 66, _y + 7, 9608, fg + bg);
	game->DrawLine(_x + 59, _y + 12, _x + 66, _y + 12, 9608, fg + bg);
	game->DrawLine(_x + 58, _y + 13, _x + 65, _y + 13, 9608, fg + bg);
	game->Fill(_x + 57, _y + 1, _x + 58, _y + 12, 9608, fg + bg);
	game->Fill(_x + 65, _y + 8, _x + 66, _y + 11, 9608, fg + bg);

	// !
	game->Fill(_x + 69, _y, _x + 70, _y + 10, 9608, fg + bg);
	game->Fill(_x + 69, _y + 12, _x + 70, _y + 13, 9608, fg + bg);
}
void StateExit::Bye(const int& _x, const int& _y,
	const short& fg, const short& bg) 
{
	// B
	game->DrawLine(_x + 1, _y	  , _x + 7, _y	   , 9608, fg + bg);
	game->DrawLine(_x	 , _y + 1 , _x + 8, _y + 1 , 9608, fg + bg);
	game->DrawLine(_x	 , _y + 2 , _x + 9, _y + 2 , 9608, fg + bg);
	game->Fill(	   _x	 , _y + 3 , _x + 2, _y + 11, 9608, fg + bg);
	game->DrawLine(_x + 1, _y + 14, _x + 7, _y + 14, 9608, fg + bg);
	game->DrawLine(_x	 , _y + 13, _x + 8, _y + 13, 9608, fg + bg);
	game->DrawLine(_x	 , _y + 12, _x + 9, _y + 12, 9608, fg + bg);
	game->DrawLine(_x + 7, _y +  3, _x + 9, _y + 3 , 9608, fg + bg);
	game->DrawLine(_x + 6, _y +  4, _x + 9, _y + 4 , 9608, fg + bg);
	game->DrawLine(_x + 5, _y +  5, _x + 8, _y + 5 , 9608, fg + bg);
	game->DrawLine(_x + 3, _y +  6, _x + 7, _y + 6 , 9608, fg + bg);
	game->DrawLine(_x + 3, _y +  7, _x + 8, _y + 7 , 9608, fg + bg);
	game->DrawLine(_x + 3, _y +  8, _x + 9, _y + 8 , 9608, fg + bg);
	game->DrawLine(_x + 6, _y +  9, _x + 9, _y + 9 , 9608, fg + bg);
	game->DrawLine(_x + 7, _y + 10, _x + 9, _y +10 , 9608, fg + bg);
	game->DrawLine(_x + 6, _y + 11, _x + 9, _y +11 , 9608, fg + bg);

	// Y
	game->DrawLine(_x + 12, _y + 7, _x + 22, _y + 7,  9608, fg + bg);
	game->DrawLine(_x + 13, _y + 8, _x + 21, _y + 8,  9608, fg + bg);
	game->DrawLine(_x + 14, _y + 9, _x + 20, _y + 9,  9608, fg + bg);
	game->Fill(	   _x + 16, _y + 10,_x + 18, _y + 14, 9608, fg + bg);
	game->Fill(	   _x + 12, _y,		_x + 14, _y + 6,  9608, fg + bg);
	game->Fill(	   _x + 20, _y,		_x + 22, _y + 6,  9608, fg + bg);

	// E
	game->DrawLine(_x + 27, _y	   , _x + 34, _y     , 9608, fg + bg);
	game->DrawLine(_x + 26, _y + 1 , _x + 34, _y + 1 , 9608, fg + bg);
	game->DrawLine(_x + 25, _y + 2 , _x + 34, _y + 2 , 9608, fg + bg);
	game->DrawLine(_x + 27, _y + 14, _x + 34, _y + 14, 9608, fg + bg);
	game->DrawLine(_x + 26, _y + 13, _x + 34, _y + 13, 9608, fg + bg);
	game->DrawLine(_x + 25, _y + 12, _x + 34, _y + 12, 9608, fg + bg);
	game->Fill(	   _x + 25, _y + 3 , _x + 27, _y + 11, 9608, fg + bg);
	game->Fill(	   _x + 28, _y + 6 , _x + 32, _y + 8 , 9608, fg + bg);
}

void StateExit::DecorateExitScreen() {
	// Top
	DrawTopButton(M_S_SRC_X1 - 6, M_S_SRC_Y0 + 2, FG_GREEN, BG_GREEN);
	DrawTopButton(M_S_SRC_X1 - 12, M_S_SRC_Y0 + 2, FG_YELLOW, BG_YELLOW);
	DrawTopButton(M_S_SRC_X1 - 18, M_S_SRC_Y0 + 2, FG_RED, BG_RED);

	// Bot
	DrawHeartButton();
	DrawCommentButton();
	DrawSaveButton();
}
void StateExit::DrawSaveButton() {
	static const int _x = M_S_SRC_X1 - 10;
	static const int _y = M_S_SRC_Y1 - 7;

	// vẽ viền
	game->DrawLine(_x + 1, _y, _x + 5, _y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x, _y + 1, _x, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 6, _y + 1, _x + 6, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 1, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 2, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 3, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 4, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 5, _y + 5, 9608, FG_BLACK + BG_BLACK);

	// Đổ bóng
	game->DrawLine(_x + 5, _y + 1, _x + 5, _y + 4, 9608, FG_DARK_MAGENTA + BG_DARK_MAGENTA);
	game->Draw(_x + 4, _y + 3, 9608, FG_DARK_MAGENTA + BG_DARK_MAGENTA);
	game->Draw(_x + 3, _y + 2, 9608, FG_DARK_MAGENTA + BG_DARK_MAGENTA);
	game->Draw(_x + 2, _y + 3, 9608, FG_DARK_MAGENTA + BG_DARK_MAGENTA);
	game->Draw(_x + 1, _y + 4, 9608, FG_DARK_MAGENTA + BG_DARK_MAGENTA);

	//// Tô nền
	game->DrawLine(_x + 1, _y + 2, _x + 1, _y + 3, 9608, FG_MAGENTA + BG_MAGENTA);
	game->DrawLine(_x + 2, _y + 1, _x + 2, _y + 2, 9608, FG_MAGENTA + BG_MAGENTA);
	game->DrawLine(_x + 4, _y + 1, _x + 4, _y + 2, 9608, FG_MAGENTA + BG_MAGENTA);
	game->Draw(_x + 3, _y + 1, 9608, FG_MAGENTA + BG_MAGENTA);

	// Ánh sáng
	game->Draw(_x + 1, _y + 1, 9608, FG_WHITE + BG_WHITE);
}
void StateExit::DrawCommentButton() {
	static const int _x = M_S_SRC_X0 + 13;
	static const int _y = M_S_SRC_Y1 - 7;

	// vẽ viền
	game->DrawLine(_x + 1, _y, _x + 5, _y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x, _y + 1, _x, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 6, _y + 1, _x + 6, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 1, _y + 4, _x + 3, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 4, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 5, _y + 4, 9608, FG_BLACK + BG_BLACK);

	// Đổ bóng
	game->DrawLine(_x + 5, _y + 1, _x + 5, _y + 3, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Draw(_x + 4, _y + 4, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	// Tô nền
	game->DrawLine(_x + 3, _y + 1, _x + 4, _y + 1, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 2, _y + 2, _x + 4, _y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 1, _y + 3, _x + 4, _y + 3, 9608, FG_YELLOW + BG_YELLOW);

	// Ánh sáng
	game->DrawLine(_x + 1, _y + 1, _x + 2, _y + 1, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + 1, _y + 2, 9608, FG_WHITE + BG_WHITE);
}
void StateExit::DrawHeartButton() {
	static const int _x = M_S_SRC_X0 + 3;
	static const int _y = M_S_SRC_Y1 - 7;
	
	// vẽ viền
	game->DrawLine(_x + 1, _y, _x + 2, _y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 4, _y, _x + 5, _y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x, _y + 1, _x, _y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 6, _y + 1, _x + 6, _y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 3, _y+1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 1, _y+3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 2, _y+4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 3, _y+5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 4, _y+4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 5, _y+3, 9608, FG_BLACK + BG_BLACK);

	// Đổ bóng
	game->DrawLine(_x + 5, _y + 1, _x + 5, _y + 2, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + 4, _y + 3, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + 3, _y + 4, 9608, FG_DARK_RED + BG_DARK_RED);

	// Tô nền
	game->Draw(_x + 2, _y + 1, 9608, FG_RED + BG_RED);
	game->Draw(_x + 4, _y + 1, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 1, _y + 2, _x + 4, _y + 2, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + 2, _y + 3, _x + 3, _y + 3, 9608, FG_RED + BG_RED);

	// Ánh sáng
	game->Draw(_x + 1, _y + 1, 9608, FG_WHITE + BG_WHITE);
}
void StateExit::DrawTopButton(const int& x0, const int& y0,
	const short& fg, const short& bg) 
{
	// vẽ viền
	game->DrawLine(x0 + 1, y0, x0 + 2, y0, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x0 + 1, y0 + 3, x0 + 2, y0 + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x0, y0 + 1, x0, y0 + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x0 + 3, y0 + 1, x0 + 3, y0 + 2, 9608, FG_BLACK + BG_BLACK);

	// Vẽ nền
	game->Draw(x0 + 2, y0 + 1, 9608, fg + bg);
	game->Draw(x0 + 1, y0 + 2, 9608, fg + bg);
	game->Draw(x0 + 2, y0 + 2, 9608, fg + bg);

	// Vẽ hiệu ứng ánh sáng
	game->Draw(x0 + 1, y0 + 1, 9608, FG_WHITE + BG_WHITE);
}

void StateExit::DrawExitScreen() {
	// Vẽ viền dọc
	game->DrawLine(M_S_SRC_X0, M_S_SRC_Y0, M_S_SRC_X0, M_S_SRC_Y1,
		9608, FG_BLACK + BG_BLACK);
	game->DrawLine(M_S_SRC_X1, M_S_SRC_Y0, M_S_SRC_X1, M_S_SRC_Y1,
		9608, FG_BLACK + BG_BLACK);

	// Vẽ viền ngang
	game->DrawLine(M_S_SRC_X0 + 1, M_S_SRC_Y0, M_S_SRC_X1 - 1, M_S_SRC_Y0,
		9608, FG_BLACK + BG_BLACK);
	game->DrawLine(M_S_SRC_X0 + 1, M_S_SRC_Y0 + 7, M_S_SRC_X1 - 1, M_S_SRC_Y0 + 7,
		9608, FG_BLACK + BG_BLACK);
	game->DrawLine(M_S_SRC_X0 + 1, M_S_SRC_Y1 - 9, M_S_SRC_X1 - 1, M_S_SRC_Y1 - 9,
		9608, FG_BLACK + BG_BLACK);
	game->DrawLine(M_S_SRC_X0 + 1, M_S_SRC_Y1, M_S_SRC_X1 - 1, M_S_SRC_Y1,
		9608, FG_BLACK + BG_BLACK);

	// Tô màu nền
	game->Fill(M_S_SRC_X0 + 1, M_S_SRC_Y0 + 1, M_S_SRC_X1 - 1, M_S_SRC_Y0 + 6,
		L' ', FG_GREY + BG_GREY);
	game->Fill(M_S_SRC_X0 + 1, M_S_SRC_Y0 + 8, M_S_SRC_X1 - 1, M_S_SRC_Y1 - 10,
		L' ', FG_CYAN + BG_CYAN);
	game->Fill(M_S_SRC_X0 + 1, M_S_SRC_Y1 - 8, M_S_SRC_X1 - 1, M_S_SRC_Y1 - 1,
		L' ', FG_DARK_CYAN + BG_DARK_CYAN);
}

void StateExit::OpenWindowEffect() {
	static const int _tm = 40;
	
	DrawShadow1(FG_GREY, BG_GREY);
	game->ConsOutput();
	
	this_thread::sleep_for(std::chrono::milliseconds(_tm));
	DrawShadow1(FG_BLUE, BG_BLUE);
	DrawShadow2(FG_GREY, BG_GREY);
	game->ConsOutput();

	this_thread::sleep_for(std::chrono::milliseconds(_tm));
	DrawShadow2(FG_BLUE, BG_BLUE);
	DrawShadow3(FG_GREY, BG_GREY);
	game->ConsOutput();
	
	this_thread::sleep_for(std::chrono::milliseconds(_tm));
	DrawShadow3(FG_BLUE, BG_BLUE);
	DrawShadow4(FG_GREY, BG_GREY);
	game->ConsOutput();

	this_thread::sleep_for(std::chrono::milliseconds(_tm));
	DrawShadow4(FG_BLUE, BG_BLUE);
	game->ConsOutput();
}
void StateExit::DrawShadow1(const short& fg, const short& bg) {
	game->Fill(M_S_SRC_X1 - 20, M_S_SRC_Y1 - 10, M_S_SRC_X1 + 4, M_S_SRC_Y1 + 4,
		L' ', fg + bg);
}
void StateExit::DrawShadow2(const short& fg, const short& bg) {
	game->Fill(M_S_SRC_X1 - 50, M_S_SRC_Y1 - 30, M_S_SRC_X1 + 3, M_S_SRC_Y1 + 3,
		L' ', fg + bg);
}
void StateExit::DrawShadow3(const short& fg, const short& bg) {
	game->Fill(M_S_SRC_X1 - 80, M_S_SRC_Y1 - 50, M_S_SRC_X1 + 2, M_S_SRC_Y1 + 2,
		L' ', fg + bg);
}
void StateExit::DrawShadow4(const short& fg, const short& bg) {
	game->Fill(M_S_SRC_X1 -110, M_S_SRC_Y1 - 70, M_S_SRC_X1 + 1, M_S_SRC_Y1 + 1,
		L' ', fg + bg);
}