#include "StateWin.h"
#include "Data.h"

bool StateWin::OnStateEnter() {
	TrainSound.OpenTrainSound();
	WinProcess();
	TrainSound.CloseTrainSound();
	return true;
}


bool StateWin::Update(float fElapsedTime) {
	DrawSaveBox();
	HandleEnterName();
	return true;
}

void StateWin::WinProcess() {
	static const int _tm = 10;// 15

	OpenWinProcess();

	// SKY
	game->Fill(0, 0, 159, 62, L' ', COLOUR::BG_DARK_CYAN);
	ForestBG();

	for (int i = 0; i <= 360; ++i) {// 202
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		//COLOUR::BG_DARK_CYAN
		CompleteCGBanner(159 - i, 29);
		// sửa lỗi tràn buffer
		game->Fill(0, 0, 0, 62, L' ', COLOUR::BG_DARK_CYAN);

		game->ConsOutput();

		if (i == 202)
			this_thread::sleep_for(std::chrono::milliseconds(500));

		// xóa spr cũ
		game->Fill(1, 8, game->ScreenWidth(), 62, L' ', COLOUR::BG_DARK_CYAN);
	}
	this_thread::sleep_for(std::chrono::milliseconds(500));

	CompleteWinBanner();
	game->ConsOutput();

	
	this_thread::sleep_for(std::chrono::milliseconds(1000));
}


void StateWin::DrawSaveBox(const int& x, const int& y) {
	WinBorder();

	game->Fill(x + 36, y + 36, x + 59, y + 44, L' ', BG_BLACK);
	game->Fill(x + 18, y + 31, x + 29, y + 31, L' ', BG_BLACK);
	game->Fill(x + 42, y + 31, x + 53, y + 31, L' ', BG_BLACK);
	game->Fill(x + 66, y + 31, x + 77, y + 31, L' ', BG_BLACK);
	this->string2Pixel(L"Enter name", x + 24, y + 4, FG_BLACK, BG_CYAN);
	this->string2Pixel(L"OK", x + 43, y + 39, FG_WHITE, BG_BLACK);
	int offSet = 2;
	this->char2Pixel(saveName[0], x + 22, y + 26, FG_BLACK, BG_CYAN, offSet);
	this->char2Pixel(saveName[1], x + 46, y + 26, FG_BLACK, BG_CYAN, offSet);
	this->char2Pixel(saveName[2], x + 70, y + 26, FG_BLACK, BG_CYAN, offSet);

	switch (optionIndex)
	{
	case 0:
	case 1:
	case 2:
		game->Fill(x + 23 + 24 * optionIndex, y + 22, x + 24 + 24 * optionIndex, y + 23, L' ', BG_BLACK);
		break;
	case 3:
		game->Fill(x + 64, y + 40, x + 66, y + 41, L' ', BG_BLACK);
	default:
		break;
	}
}
void StateWin::HandleEnterName() {
	if (game->GetKey(VK_ESCAPE).bPressed) {
		switch (optionIndex)
		{
		case 1:
		case 2:
		case 3:
			optionIndex--;
			saveName[optionIndex] = L' ';
			break;
		default:
			break;
		}
	}

	if (optionIndex >= 0 && optionIndex < 3) {
		for (int i = 0x41; i < 0x5A; i++) {
			if (game->GetKey(i).bPressed) {
				wchar_t temp = (wchar_t)i;
				saveName[optionIndex] = temp;
				optionIndex++;
			}
		}
	}

	if (game->GetKey(VK_SPACE).bPressed && optionIndex == 3) {
		Data::AddLeaderboard(saveName, score);
		game->SetState(new StateMenu(game));
	}
}



void StateWin::OpenWinProcess() {
	static const int _tm = 1;// 25
	static const int changeState = 300;// 25
	static const int maxStateIdx = 4;

	static const int x0 = 0;
	static const int x1 = 160;
	static const int y0 = 0;
	static const int y1 = 96;
	static const int deltaX = x1 - x0 + 1;
	static const int deltaY = y1 - y0 + 1;

	for (int x = x0; x <= x1 / 2; ++x) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		game->Fill(x, y0,
			x, y1, L' ', COLOUR::BG_BLACK);
		game->Fill(x1 - x, y0,
			x1 - x, y1, L' ', COLOUR::BG_BLACK);

		game->ConsOutput();
	}
	TrainSound.PlayTrainSound();
	this_thread::sleep_for(std::chrono::milliseconds(changeState));

	for (int x = x1 / 2; x <= x1; ++x) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		game->Fill(x, y0,
			x, y1, L' ', COLOUR::BG_GREY);
		game->Fill(x1 - x, y0,
			x1 - x, y1, L' ', COLOUR::BG_GREY);

		game->ConsOutput();
	}
	this_thread::sleep_for(std::chrono::milliseconds(changeState));

}
void StateWin::ForestBG() {
	// river
	game->Fill(0, 86, 50, 95, L' ', BG_BLUE);
	game->Fill(51, 85, 96, 95, L' ', BG_BLUE);
	game->Fill(97, 84, 131, 95, L' ', BG_BLUE);
	game->Fill(132, 83, 159, 95, L' ', BG_BLUE);

	game->DrawLine(0, 85, 38, 85, L' ', BG_DARK_BLUE);
	game->DrawLine(37, 84, 83, 84, L' ', BG_DARK_BLUE);
	game->DrawLine(82, 83, 121, 83, L' ', BG_DARK_BLUE);
	game->DrawLine(120, 82, 159, 82, L' ', BG_DARK_BLUE);

	game->DrawLine(39, 85, 46, 85, L' ', BG_DARK_CYAN);
	game->DrawLine(84, 84, 92, 84, L' ', BG_DARK_CYAN);
	game->DrawLine(122, 83, 127, 83, L' ', BG_DARK_CYAN);

	game->DrawLine(47, 85, 50, 85, L' ', BG_CYAN);
	game->DrawLine(93, 84, 96, 84, L' ', BG_CYAN);
	game->DrawLine(128, 83, 131, 83, L' ', BG_CYAN);

	// LAND
	game->DrawLine(0, 84, 36, 84, L' ', BG_DARK_YELLOW);
	game->DrawLine(36, 83, 81, 83, L' ', BG_DARK_YELLOW);
	game->DrawLine(81, 82, 119, 82, L' ', BG_DARK_YELLOW);
	game->DrawLine(119, 81, 159, 81, L' ', BG_DARK_YELLOW);

	game->DrawLine(0, 65, 159, 65, L' ', BG_DARK_GREEN);
	game->DrawLine(0, 64, 159, 64, L' ', BG_DARK_GREY);
	game->DrawLine(0, 63, 159, 63, L' ', BG_BLACK);

	// GRASS
	game->Fill(0, 66, 35, 83, L' ', BG_GREEN);
	game->Fill(36, 66, 80, 82, L' ', BG_GREEN);
	game->Fill(81, 66, 118, 81, L' ', BG_GREEN);
	game->Fill(119, 66, 159, 80, L' ', BG_GREEN);

	MiniGrass(3, 69);
	MiniGrass(13, 79);
	MiniGrass(24, 68);
	MiniGrass(39, 71);
	MiniGrass(58, 76);
	MiniGrass(77, 74);
	MiniGrass(125, 76);
	MiniGrass(139, 67);
	MiniGrass(158, 70);
	MiniGrass(87, 68);
	MiniGrass(106, 77);

	MiniMushroom(16, 72);
	MiniMushroom(118, 69);
	MiniMushroom(148, 76);
	MiniMushroom(40, 77);
}
void StateWin::MiniGrass(const int& x, const int& y) {
	game->DrawLine(x, y + 1, x + 1, y, 9608, FG_DARK_GREEN + BG_DARK_GREEN);
	game->Draw(x + 2, y + 1, 9608, FG_DARK_GREEN + BG_DARK_GREEN);
}
void StateWin::MiniMushroom(const int& x, const int& y) {
	// FG_DARK_RED + BG_DARK_RED
	game->DrawLine(x + 1, y, x + 3, y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 2, x + 3, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x, y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 4, y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 1, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 3, y + 3, 9608, FG_BLACK + BG_BLACK);

	game->Draw(x + 1, y + 1, 9608, FG_RED + BG_RED);
	game->Draw(x + 3, y + 1, 9608, FG_RED + BG_RED);

	game->Draw(x + 2, y + 1, 9608, FG_WHITE + BG_WHITE);
	game->Draw(x + 2, y + 3, 9608, FG_WHITE + BG_WHITE);
}


void StateWin::CompleteWinBanner() {
	WinBorder();
	YouWin(24, 38);
	WinningCup(70, 10);
}
void StateWin::WinBorder() {
	static const int x0 = 15;
	static const int x1 = 148;
	static const int y0 = 4;
	static const int y1 = 58;

	game->DrawLine(x0 - 2, y0 + 2, x0 - 2, y1 + 1, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x0 - 2, y1 + 2, x1 - 2, y1 + 2, 9608, FG_GREY + BG_GREY);

	game->DrawLine(x0 - 1, y0 + 1, x0 - 1, y1 + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x0, y1 + 1, x1 - 1, y1 + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);

	game->DrawLine(x0, y0, x1, y0, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x0, y1, x1, y1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x0, y0 + 1, x0, y1 - 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x1, y0 + 1, x1, y1 - 1, 9608, FG_BLACK + BG_BLACK);

	game->Fill(x0 + 1, y0 + 1, x1 - 1, y1 - 1, 9608, FG_CYAN + BG_CYAN);

}
void StateWin::YouWin(const int& x, const int& y) {
	static const vector<pair<short, short>> COLOR_LIST = {
		{FG_RED, BG_RED},//Y
		{FG_RED, BG_RED},//O
		{FG_RED, BG_RED},//U
		{FG_MAGENTA, BG_MAGENTA},//W
		{FG_MAGENTA, BG_MAGENTA},//I
		{FG_MAGENTA, BG_MAGENTA},//N
		{FG_DARK_MAGENTA, BG_DARK_MAGENTA} //!
	};

	int dummy = 0;
	// ===================== Y =====================
	// Vẽ chữ
	game->DrawLine(x + 5, y + 13, x + 8, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 4, y + 7, x + 9, y + 12, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	game->DrawLine(x, y + 1, x, y + 2, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 1, y, x + 2, y, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	game->DrawLine(x, y + 3, x + 3, y + 6, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 1, y + 3, x + 4, y + 6, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 2, y + 3, x + 5, y + 6, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 2, y + 2, x + 6, y + 6, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 3, y + 2, x + 7, y + 6, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 3, y + 1, x + 8, y + 6, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 3, y, x + 9, y + 6, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	game->DrawLine(x + 7, y + 3, x + 10, y, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 8, y + 3, x + 11, y, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 8, y + 4, x + 12, y, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 9, y + 4, x + 12, y + 1, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 9, y + 5, x + 13, y + 1, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 10, y + 5, x + 13, y + 2, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 10, y + 6, x + 13, y + 3, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	// ánh sáng
	game->DrawLine(x + 1, y + 1, x + 2, y + 1, 9608, FG_WHITE + BG_WHITE);
	game->Draw(x + 1, y + 2, 9608, FG_WHITE + BG_WHITE);

	++dummy;
	// ===================== O =====================
	// Vẽ chữ
	game->Fill(x + 18, y + 3, x + 22, y + 11, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 23, y + 10, x + 26, y + 11, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 27, y + 3, x + 30, y + 11, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	game->DrawLine(x + 17, y + 2, x + 17, y + 11, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 18, y + 12, x + 29, y + 12, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 19, y + 13, x + 28, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	game->DrawLine(x + 19, y, x + 28, y, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 20, y + 1, x + 29, y + 1, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 19, y + 2, x + 30, y + 2, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	// ánh sáng
	game->DrawLine(x + 18, y + 1, x + 19, y + 1, 9608, FG_WHITE + BG_WHITE);
	game->Draw(x + 18, y + 2, 9608, FG_WHITE + BG_WHITE);

	++dummy;
	// ===================== U =====================
	// Vẽ chữ
	game->Fill(x + 35, y + 3, x + 40, y + 9, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 34, y + 10, x + 47, y + 11, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 43, y + 1, x + 47, y + 9, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	game->DrawLine(x + 34, y + 1, x + 34, y + 9, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 35, y, x + 39, y, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 37, y + 1, x + 40, y + 1, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 36, y + 2, x + 40, y + 2, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 44, y, x + 46, y, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 35, y + 12, x + 46, y + 12, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 36, y + 13, x + 45, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	// ánh sáng
	game->DrawLine(x + 35, y + 1, x + 36, y + 1, 9608, FG_WHITE + BG_WHITE);
	game->Draw(x + 35, y + 2, 9608, FG_WHITE + BG_WHITE);

	++dummy;
	// ===================== W =====================
	// Vẽ chữ
	game->Fill(x + 65, y + 3, x + 69, y + 12, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 73, y + 1, x + 77, y + 12, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	game->DrawLine(x + 64, y + 1, x + 64, y + 11, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 65, y, x + 68, y, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 74, y, x + 76, y, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 66, y + 13, x + 68, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 74, y + 13, x + 76, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	game->DrawLine(x + 67, y + 1, x + 69, y + 1, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 66, y + 2, x + 69, y + 2, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	game->DrawLine(x + 70, y + 7, x + 70, y + 11, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 72, y + 7, x + 72, y + 11, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 71, y + 6, x + 71, y + 10, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	// ánh sáng
	game->DrawLine(x + 65, y + 1, x + 66, y + 1, 9608, FG_WHITE + BG_WHITE);
	game->Draw(x + 65, y + 2, 9608, FG_WHITE + BG_WHITE);

	++dummy;
	// ===================== I =====================
	// Vẽ chữ
	game->Fill(x + 81, y + 3, x + 87, y + 12, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	game->DrawLine(x + 82, y, x + 86, y, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 82, y + 13, x + 86, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 84, y + 1, x + 87, y + 1, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 83, y + 2, x + 87, y + 2, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 81, y + 1, x + 81, y + 2, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	// ánh sáng
	game->DrawLine(x + 82, y + 1, x + 83, y + 1, 9608, FG_WHITE + BG_WHITE);
	game->Draw(x + 82, y + 2, 9608, FG_WHITE + BG_WHITE);

	++dummy;
	// ===================== N =====================
	// Vẽ chữ
	game->Fill(x + 91, y + 3, x + 97, y + 12, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	game->DrawLine(x + 92, y, x + 96, y, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 92, y + 13, x + 96, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 94, y + 1, x + 97, y + 1, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 93, y + 2, x + 97, y + 2, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 91, y + 1, x + 91, y + 2, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	game->DrawLine(x + 98, y + 5, x + 98, y + 8, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 99, y + 6, x + 99, y + 9, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 101, y, x + 103, y, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 101, y + 13, x + 103, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 100, y + 1, x + 104, y + 12, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	// ánh sáng
	game->DrawLine(x + 92, y + 1, x + 93, y + 1, 9608, FG_WHITE + BG_WHITE);
	game->Draw(x + 92, y + 2, 9608, FG_WHITE + BG_WHITE);

	++dummy;
	// ===================== ! =====================
	// Vẽ chữ
	game->Fill(x + 108, y + 3, x + 113, y + 5, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 109, y + 6, x + 112, y + 7, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 109, y + 11, x + 112, y + 12, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	game->DrawLine(x + 110, y + 13, x + 111, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 110, y + 10, x + 111, y + 10, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 110, y + 8, x + 111, y + 8, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 110, y + 2, x + 113, y + 2, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 111, y + 1, x + 113, y + 1, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 109, y, x + 112, y, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	game->DrawLine(x + 108, y + 1, x + 108, y + 2, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);

	// ánh sáng
	game->DrawLine(x + 109, y + 1, x + 110, y + 1, 9608, FG_WHITE + BG_WHITE);
	game->Draw(x + 109, y + 2, 9608, FG_WHITE + BG_WHITE);

}
void StateWin::WinningCup(const int& x, const int& y) {
	// Vẽ viền
	game->DrawLine(x, y + 3, x, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 19, y + 3, x + 19, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 4, x + 2, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 17, y + 4, x + 17, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 4, y, x + 4, y + 8, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 15, y, x + 15, y + 8, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 8, y + 12, x + 8, y + 15, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 11, y + 12, x + 11, y + 15, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y + 18, x + 7, y + 16, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 12, y + 16, x + 14, y + 18, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y + 19, x + 14, y + 19, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 7, y + 17, x + 12, y + 17, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y, x + 14, y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y + 1, x + 1, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 16, y + 1, x + 17, y + 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 8, x + 2, y + 9, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 17, y + 9, x + 18, y + 8, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y + 10, x + 5, y + 10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 14, y + 10, x + 16, y + 10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 9, y + 11, x + 10, y + 11, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y + 9, x + 7, y + 11, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y + 8, x + 8, y + 11, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 11, y + 11, x + 14, y + 8, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 12, y + 11, x + 14, y + 9, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 3, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 3, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 16, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 16, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 18, y + 2, 9608, FG_BLACK + BG_BLACK);

	// vẽ bóng
	game->DrawLine(x + 3, y + 8, x + 4, y + 9, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 17, y + 2, x + 18, y + 3, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 10, y + 12, x + 10, y + 15, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 10, y + 16, x + 11, y + 16, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 11, y + 18, x + 13, y + 18, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 8, y + 10, x + 11, y + 10, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 9, y + 9, x + 12, y + 9, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 10, y + 8, x + 13, y + 8, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 11, y + 7, x + 14, y + 7, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(x + 12, y + 1, x + 14, y + 6, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	// vẽ màu cup
	game->DrawLine(x + 2, y + 3, x + 3, y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 1, y + 6, x + 2, y + 7, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 1, y + 7, x + 3, y + 9, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 17, y + 3, x + 18, y + 4, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 18, y + 5, x + 18, y + 6, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 15, y + 9, x + 17, y + 7, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 16, y + 9, x + 18, y + 7, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 9, y + 12, x + 9, y + 13, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 8, y + 18, x + 10, y + 18, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 8, y + 1, x + 11, y + 1, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 7, y + 7, x + 8, y + 7, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 8, y + 8, x + 9, y + 7, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 8, y + 9, x + 10, y + 7, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(x + 6, y + 2, x + 11, y + 6, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(x + 9, y + 15, 9608, FG_YELLOW + BG_YELLOW);

	// vẽ ánh sáng
	game->DrawLine(x + 1, y + 3, x + 2, y + 2, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 1, y + 4, x + 1, y + 5, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 6, y + 18, x + 7, y + 18, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 8, y + 16, x + 9, y + 16, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 5, y + 1, x + 7, y + 1, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 5, y + 2, x + 5, y + 6, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 5, y + 7, x + 7, y + 9, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 6, y + 7, x + 7, y + 8, 9608, FG_WHITE + BG_WHITE);
	game->Draw(x + 16, y + 2, 9608, FG_WHITE + BG_WHITE);
	game->Draw(x + 9, y + 14, 9608, FG_WHITE + BG_WHITE);


}


//Draw Congratulations Banner
void StateWin::CompleteCGBanner(const int& x, const int& y) {
	Smoke(x + 11, y - 21);
	TrainLocomotive(x, y);
	TrainWagon(x + 49, y + 20);
	DrawCGBanner(x + 56, y - 1);
}
void StateWin::Congratulations(const int& x, const int& y) {
	static const short borFg = FG_BLACK;
	static const short borBg = BG_BLACK;
	static const short mainFg = FG_WHITE;
	static const short mainBg = BG_WHITE;

	int offsetX = 0;

	// ============================= C =============================
	// viền
	game->DrawLine(x, y + 1, x, y + 7, 9608, borFg + borBg);
	game->DrawLine(x + 1, y, x + 1, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 1, y + 7, x + 1, y + 8, 9608, borFg + borBg);
	game->DrawLine(x + 2, y, x + 7, y, 9608, borFg + borBg);
	game->DrawLine(x + 7, y + 1, x + 8, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 7, y + 1, x + 8, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 7, y + 7, x + 8, y + 7, 9608, borFg + borBg);
	game->DrawLine(x + 8, y + 2, x + 8, y + 6, 9608, borFg + borBg);
	game->Fill(x + 2, y + 8, x + 8, y + 9, 9608, borFg + borBg);
	game->Fill(x + 3, y + 2, x + 5, y + 6, 9608, borFg + borBg);
	game->Fill(x + 6, y + 3, x + 7, y + 5, 9608, borFg + borBg);
	// nền
	game->Fill(x + 1, y + 2, x + 2, y + 6, 9608, mainFg + mainBg);
	game->DrawLine(x + 2, y + 1, x + 6, y + 1, 9608, mainFg + mainBg);
	game->DrawLine(x + 2, y + 7, x + 6, y + 7, 9608, mainFg + mainBg);
	game->DrawLine(x + 6, y + 2, x + 7, y + 2, 9608, mainFg + mainBg);
	game->DrawLine(x + 6, y + 6, x + 7, y + 6, 9608, mainFg + mainBg);

	// ============================= O =============================
	// viền
	game->DrawLine(x + 9 + offsetX, y + 1, x + 9 + offsetX, y + 6, 9608, borFg + borBg);
	game->DrawLine(x + 10 + offsetX, y, x + 10 + offsetX, y + 1, 9608, borFg + borBg);
	game->Fill(x + 9 + offsetX, y + 7, x + 10 + offsetX, y + 8, 9608, borFg + borBg);
	game->Fill(x + 11 + offsetX, y + 8, x + 17 + offsetX, y + 9, 9608, borFg + borBg);
	game->DrawLine(x + 11 + offsetX, y, x + 16 + offsetX, y, 9608, borFg + borBg);
	game->DrawLine(x + 16 + offsetX, y + 1, x + 17 + offsetX, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 16 + offsetX, y + 7, x + 17 + offsetX, y + 7, 9608, borFg + borBg);
	game->DrawLine(x + 17 + offsetX, y + 2, x + 17 + offsetX, y + 6, 9608, borFg + borBg);
	game->Fill(x + 12 + offsetX, y + 2, x + 14 + offsetX, y + 6, 9608, borFg + borBg);
	// nền
	game->Fill(x + 10 + offsetX, y + 2, x + 11 + offsetX, y + 6, 9608, mainFg + mainBg);
	game->Fill(x + 15 + offsetX, y + 2, x + 16 + offsetX, y + 6, 9608, mainFg + mainBg);
	game->DrawLine(x + 11 + offsetX, y + 1, x + 15 + offsetX, y + 1, 9608, mainFg + mainBg);
	game->DrawLine(x + 11 + offsetX, y + 7, x + 15 + offsetX, y + 7, 9608, mainFg + mainBg);

	// ============================= N =============================
	// viền
	game->DrawLine(x + 18 + offsetX, y, x + 18 + offsetX, y + 8, 9608, borFg + borBg);
	game->Fill(x + 19 + offsetX, y + 8, x + 22 + offsetX, y + 9, 9608, borFg + borBg);
	game->Fill(x + 24 + offsetX, y + 8, x + 26 + offsetX, y + 9, 9608, borFg + borBg);
	game->DrawLine(x + 21 + offsetX, y, x + 22 + offsetX, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 21 + offsetX, y + 1, x + 22 + offsetX, y + 2, 9608, borFg + borBg);
	game->DrawLine(x + 23 + offsetX, y, x + 23 + offsetX, y + 3, 9608, borFg + borBg);
	game->DrawLine(x + 24 + offsetX, y, x + 26 + offsetX, y, 9608, borFg + borBg);
	game->DrawLine(x + 26 + offsetX, y + 1, x + 26 + offsetX, y + 7, 9608, borFg + borBg);
	game->DrawLine(x + 19 + offsetX, y, x + 20 + offsetX, y, 9608, borFg + borBg);
	game->DrawLine(x + 21 + offsetX, y + 4, x + 21 + offsetX, y + 7, 9608, borFg + borBg);
	game->DrawLine(x + 22 + offsetX, y + 5, x + 22 + offsetX, y + 7, 9608, borFg + borBg);
	game->DrawLine(x + 23 + offsetX, y + 6, x + 23 + offsetX, y + 8, 9608, borFg + borBg);
	// nền
	game->Fill(x + 19 + offsetX, y + 1, x + 20 + offsetX, y + 7, 9608, mainFg + mainBg);
	game->Fill(x + 24 + offsetX, y + 1, x + 25 + offsetX, y + 7, 9608, mainFg + mainBg);
	game->DrawLine(x + 21 + offsetX, y + 2, x + 23 + offsetX, y + 4, 9608, mainFg + mainBg);
	game->DrawLine(x + 21 + offsetX, y + 3, x + 23 + offsetX, y + 5, 9608, mainFg + mainBg);

	// ============================= G =============================
		// viền
	game->DrawLine(x + 27, y + 1, x + 27, y + 9, 9608, borFg + borBg);
	game->DrawLine(x + 28, y, x + 28, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 28, y + 7, x + 28, y + 8, 9608, borFg + borBg);
	game->DrawLine(x + 29, y, x + 34, y, 9608, borFg + borBg);
	game->DrawLine(x + 34, y + 1, x + 35, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 35, y + 2, x + 35, y + 7, 9608, borFg + borBg);
	game->Fill(x + 29, y + 8, x + 35, y + 9, 9608, borFg + borBg);
	game->Fill(x + 30, y + 2, x + 31, y + 6, 9608, borFg + borBg);
	game->DrawLine(x + 32, y + 2, x + 32, y + 3, 9608, borFg + borBg);
	game->DrawLine(x + 32, y + 5, x + 32, y + 6, 9608, borFg + borBg);
	game->DrawLine(x + 33, y + 3, x + 34, y + 3, 9608, borFg + borBg);
	game->Draw(x + 33, y + 7, 9608, borFg + borBg);
	// nền
	game->Fill(x + 28, y + 2, x + 29, y + 6, 9608, mainFg + mainBg);
	game->DrawLine(x + 29, y + 1, x + 33, y + 1, 9608, mainFg + mainBg);
	game->DrawLine(x + 33, y + 2, x + 34, y + 2, 9608, mainFg + mainBg);
	game->DrawLine(x + 29, y + 7, x + 32, y + 7, 9608, mainFg + mainBg);
	game->Fill(x + 33, y + 4, x + 34, y + 6, 9608, mainFg + mainBg);
	game->Draw(x + 32, y + 4, 9608, mainFg + mainBg);
	game->Draw(x + 34, y + 7, 9608, mainFg + mainBg);

	// ============================= R =============================
	// viền
	game->DrawLine(x + 36, y, x + 36, y + 9, 9608, borFg + borBg);
	game->DrawLine(x + 37, y, x + 43, y, 9608, borFg + borBg);
	game->DrawLine(x + 43, y + 1, x + 44, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 44, y + 2, x + 44, y + 7, 9608, borFg + borBg);
	game->Draw(x + 43, y + 4, 9608, borFg + borBg);
	game->Draw(x + 41, y + 8, 9608, borFg + borBg);
	game->Fill(x + 39, y + 2, x + 41, y + 3, 9608, borFg + borBg);
	game->Fill(x + 37, y + 8, x + 40, y + 9, 9608, borFg + borBg);
	game->Fill(x + 39, y + 5, x + 41, y + 7, 9608, borFg + borBg);
	game->Fill(x + 42, y + 8, x + 44, y + 9, 9608, borFg + borBg);
	// nền
	game->Fill(x + 37, y + 1, x + 38, y + 7, 9608, mainFg + mainBg);
	game->Fill(x + 42, y + 2, x + 43, y + 3, 9608, mainFg + mainBg);
	game->Fill(x + 42, y + 5, x + 43, y + 7, 9608, mainFg + mainBg);
	game->DrawLine(x + 39, y + 1, x + 42, y + 1, 9608, mainFg + mainBg);
	game->DrawLine(x + 39, y + 4, x + 42, y + 4, 9608, mainFg + mainBg);

	// ============================= A =============================
	// viền
	game->DrawLine(x + 45 + offsetX, y + 1, x + 45 + offsetX, y + 7, 9608, borFg + borBg);
	game->DrawLine(x + 46 + offsetX, y, x + 46 + offsetX, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 52 + offsetX, y, x + 52 + offsetX, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 47 + offsetX, y, x + 51 + offsetX, y, 9608, borFg + borBg);
	game->Fill(x + 48 + offsetX, y + 2, x + 50 + offsetX, y + 4, 9608, borFg + borBg);
	game->Fill(x + 48 + offsetX, y + 6, x + 50 + offsetX, y + 7, 9608, borFg + borBg);
	game->Fill(x + 45 + offsetX, y + 8, x + 49 + offsetX, y + 9, 9608, borFg + borBg);
	game->Fill(x + 51 + offsetX, y + 8, x + 52 + offsetX, y + 9, 9608, borFg + borBg);
	game->Fill(x + 53 + offsetX, y + 1, x + 54 + offsetX, y + 9, 9608, borFg + borBg);
	// nền
	game->Fill(x + 46 + offsetX, y + 2, x + 47 + offsetX, y + 7, 9608, mainFg + mainBg);
	game->Fill(x + 51 + offsetX, y + 2, x + 52 + offsetX, y + 7, 9608, mainFg + mainBg);
	game->DrawLine(x + 47 + offsetX, y + 1, x + 51 + offsetX, y + 1, 9608, mainFg + mainBg);
	game->DrawLine(x + 48 + offsetX, y + 5, x + 50 + offsetX, y + 5, 9608, mainFg + mainBg);

	// ============================= T =============================
	// viền
	game->DrawLine(x + 54 + offsetX, y, x + 61 + offsetX, y, 9608, borFg + borBg);
	game->DrawLine(x + 55 + offsetX, y + 2, x + 56 + offsetX, y + 2, 9608, borFg + borBg);
	game->DrawLine(x + 56 + offsetX, y + 3, x + 56 + offsetX, y + 8, 9608, borFg + borBg);
	game->DrawLine(x + 61 + offsetX, y + 1, x + 61 + offsetX, y + 3, 9608, borFg + borBg);
	game->Fill(x + 57 + offsetX, y + 8, x + 58 + offsetX, y + 9, 9608, borFg + borBg);
	game->Fill(x + 59 + offsetX, y + 2, x + 60 + offsetX, y + 9, 9608, borFg + borBg);
	// nền
	game->Fill(x + 57 + offsetX, y + 2, x + 58 + offsetX, y + 7, 9608, mainFg + mainBg);
	game->DrawLine(x + 55 + offsetX, y + 1, x + 60 + offsetX, y + 1, 9608, mainFg + mainBg);

	// ============================= U =============================
	// viền
	game->DrawLine(x + 62, y, x + 62, y + 7, 9608, borFg + borBg);
	game->DrawLine(x + 63, y + 7, x + 63, y + 8, 9608, borFg + borBg);
	game->DrawLine(x + 70, y, x + 70, y + 6, 9608, borFg + borBg);
	game->DrawLine(x + 69, y + 7, x + 70, y + 7, 9608, borFg + borBg);
	game->DrawLine(x + 63, y, x + 65, y, 9608, borFg + borBg);
	game->DrawLine(x + 67, y, x + 69, y, 9608, borFg + borBg);
	game->Fill(x + 65, y + 1, x + 67, y + 6, 9608, borFg + borBg);
	game->Fill(x + 64, y + 8, x + 70, y + 9, 9608, borFg + borBg);
	// nền
	game->Fill(x + 63, y + 1, x + 64, y + 6, 9608, mainFg + mainBg);
	game->Fill(x + 68, y + 1, x + 69, y + 6, 9608, mainFg + mainBg);
	game->DrawLine(x + 64, y + 7, x + 68, y + 7, 9608, mainFg + mainBg);

	// ============================= L =============================
	// viền
	game->DrawLine(x + 71, y, x + 71, y + 8, 9608, borFg + borBg);
	game->DrawLine(x + 78, y + 6, x + 78, y + 7, 9608, borFg + borBg);
	game->DrawLine(x + 72, y, x + 74, y, 9608, borFg + borBg);
	game->DrawLine(x + 76, y + 6, x + 77, y + 6, 9608, borFg + borBg);
	game->Fill(x + 74, y + 1, x + 75, y + 6, 9608, borFg + borBg);
	game->Fill(x + 72, y + 8, x + 78, y + 9, 9608, borFg + borBg);
	// nền
	game->Fill(x + 72, y + 1, x + 73, y + 7, 9608, mainFg + mainBg);
	game->DrawLine(x + 74, y + 7, x + 77, y + 7, 9608, mainFg + mainBg);

	offsetX = 34;
	// ============================= A =============================
	// viền
	game->DrawLine(x + 45 + offsetX, y + 1, x + 45 + offsetX, y + 7, 9608, borFg + borBg);
	game->DrawLine(x + 46 + offsetX, y, x + 46 + offsetX, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 52 + offsetX, y, x + 52 + offsetX, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 47 + offsetX, y, x + 51 + offsetX, y, 9608, borFg + borBg);
	game->Fill(x + 48 + offsetX, y + 2, x + 50 + offsetX, y + 4, 9608, borFg + borBg);
	game->Fill(x + 48 + offsetX, y + 6, x + 50 + offsetX, y + 7, 9608, borFg + borBg);
	game->Fill(x + 45 + offsetX, y + 8, x + 49 + offsetX, y + 9, 9608, borFg + borBg);
	game->Fill(x + 51 + offsetX, y + 8, x + 52 + offsetX, y + 9, 9608, borFg + borBg);
	game->Fill(x + 53 + offsetX, y + 1, x + 54 + offsetX, y + 9, 9608, borFg + borBg);
	// nền
	game->Fill(x + 46 + offsetX, y + 2, x + 47 + offsetX, y + 7, 9608, mainFg + mainBg);
	game->Fill(x + 51 + offsetX, y + 2, x + 52 + offsetX, y + 7, 9608, mainFg + mainBg);
	game->DrawLine(x + 47 + offsetX, y + 1, x + 51 + offsetX, y + 1, 9608, mainFg + mainBg);
	game->DrawLine(x + 48 + offsetX, y + 5, x + 50 + offsetX, y + 5, 9608, mainFg + mainBg);

	// ============================= T =============================
	// viền
	game->DrawLine(x + 54 + offsetX, y, x + 61 + offsetX, y, 9608, borFg + borBg);
	game->DrawLine(x + 55 + offsetX, y + 2, x + 56 + offsetX, y + 2, 9608, borFg + borBg);
	game->DrawLine(x + 56 + offsetX, y + 3, x + 56 + offsetX, y + 8, 9608, borFg + borBg);
	game->DrawLine(x + 61 + offsetX, y + 1, x + 61 + offsetX, y + 3, 9608, borFg + borBg);
	game->Fill(x + 57 + offsetX, y + 8, x + 58 + offsetX, y + 9, 9608, borFg + borBg);
	game->Fill(x + 59 + offsetX, y + 2, x + 60 + offsetX, y + 9, 9608, borFg + borBg);
	// nền
	game->Fill(x + 57 + offsetX, y + 2, x + 58 + offsetX, y + 7, 9608, mainFg + mainBg);
	game->DrawLine(x + 55 + offsetX, y + 1, x + 60 + offsetX, y + 1, 9608, mainFg + mainBg);

	// ============================= L =============================
	// viền
	game->DrawLine(x + 96, y, x + 96, y + 8, 9608, borFg + borBg);
	game->DrawLine(x + 97, y, x + 99, y, 9608, borFg + borBg);
	game->Fill(x + 97, y + 8, x + 98, y + 9, 9608, borFg + borBg);
	game->Fill(x + 99, y + 1, x + 100, y + 9, 9608, borFg + borBg);
	// nền
	game->Fill(x + 97, y + 1, x + 98, y + 7, 9608, mainFg + mainBg);

	offsetX = 91;
	// ============================= O =============================
	// viền
	game->DrawLine(x + 9 + offsetX, y + 1, x + 9 + offsetX, y + 6, 9608, borFg + borBg);
	game->DrawLine(x + 10 + offsetX, y, x + 10 + offsetX, y + 1, 9608, borFg + borBg);
	game->Fill(x + 9 + offsetX, y + 7, x + 10 + offsetX, y + 8, 9608, borFg + borBg);
	game->Fill(x + 11 + offsetX, y + 8, x + 17 + offsetX, y + 9, 9608, borFg + borBg);
	game->DrawLine(x + 11 + offsetX, y, x + 16 + offsetX, y, 9608, borFg + borBg);
	game->DrawLine(x + 16 + offsetX, y + 1, x + 17 + offsetX, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 16 + offsetX, y + 7, x + 17 + offsetX, y + 7, 9608, borFg + borBg);
	game->DrawLine(x + 17 + offsetX, y + 2, x + 17 + offsetX, y + 6, 9608, borFg + borBg);
	game->Fill(x + 12 + offsetX, y + 2, x + 14 + offsetX, y + 6, 9608, borFg + borBg);
	// nền
	game->Fill(x + 10 + offsetX, y + 2, x + 11 + offsetX, y + 6, 9608, mainFg + mainBg);
	game->Fill(x + 15 + offsetX, y + 2, x + 16 + offsetX, y + 6, 9608, mainFg + mainBg);
	game->DrawLine(x + 11 + offsetX, y + 1, x + 15 + offsetX, y + 1, 9608, mainFg + mainBg);
	game->DrawLine(x + 11 + offsetX, y + 7, x + 15 + offsetX, y + 7, 9608, mainFg + mainBg);

	// ============================= N =============================
	// viền
	game->DrawLine(x + 18 + offsetX, y, x + 18 + offsetX, y + 8, 9608, borFg + borBg);
	game->Fill(x + 19 + offsetX, y + 8, x + 22 + offsetX, y + 9, 9608, borFg + borBg);
	game->Fill(x + 24 + offsetX, y + 8, x + 26 + offsetX, y + 9, 9608, borFg + borBg);
	game->DrawLine(x + 21 + offsetX, y, x + 22 + offsetX, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 21 + offsetX, y + 1, x + 22 + offsetX, y + 2, 9608, borFg + borBg);
	game->DrawLine(x + 23 + offsetX, y, x + 23 + offsetX, y + 3, 9608, borFg + borBg);
	game->DrawLine(x + 24 + offsetX, y, x + 26 + offsetX, y, 9608, borFg + borBg);
	game->DrawLine(x + 26 + offsetX, y + 1, x + 26 + offsetX, y + 7, 9608, borFg + borBg);
	game->DrawLine(x + 19 + offsetX, y, x + 20 + offsetX, y, 9608, borFg + borBg);
	game->DrawLine(x + 21 + offsetX, y + 4, x + 21 + offsetX, y + 7, 9608, borFg + borBg);
	game->DrawLine(x + 22 + offsetX, y + 5, x + 22 + offsetX, y + 7, 9608, borFg + borBg);
	game->DrawLine(x + 23 + offsetX, y + 6, x + 23 + offsetX, y + 8, 9608, borFg + borBg);
	// nền
	game->Fill(x + 19 + offsetX, y + 1, x + 20 + offsetX, y + 7, 9608, mainFg + mainBg);
	game->Fill(x + 24 + offsetX, y + 1, x + 25 + offsetX, y + 7, 9608, mainFg + mainBg);
	game->DrawLine(x + 21 + offsetX, y + 2, x + 23 + offsetX, y + 4, 9608, mainFg + mainBg);
	game->DrawLine(x + 21 + offsetX, y + 3, x + 23 + offsetX, y + 5, 9608, mainFg + mainBg);

	// ============================= S =============================
	// viền
	game->DrawLine(x + 118, y + 1, x + 118, y + 9, 9608, borFg + borBg);
	game->DrawLine(x + 119, y, x + 119, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 119, y + 4, x + 119, y + 5, 9608, borFg + borBg);
	game->DrawLine(x + 119, y + 7, x + 119, y + 8, 9608, borFg + borBg);
	game->DrawLine(x + 125, y, x + 125, y + 1, 9608, borFg + borBg);
	game->DrawLine(x + 125, y + 3, x + 125, y + 4, 9608, borFg + borBg);
	game->DrawLine(x + 125, y + 7, x + 125, y + 8, 9608, borFg + borBg);
	game->DrawLine(x + 120, y, x + 124, y, 9608, borFg + borBg);
	game->DrawLine(x + 125, y + 9, x + 126, y + 9, 9608, borFg + borBg);
	game->Fill(x + 121, y + 2, x + 123, y + 3, 9608, borFg + borBg);
	game->Fill(x + 121, y + 5, x + 123, y + 6, 9608, borFg + borBg);
	game->Fill(x + 120, y + 8, x + 124, y + 9, 9608, borFg + borBg);
	game->Fill(x + 126, y + 2, x + 127, y + 8, 9608, borFg + borBg);
	game->Draw(x + 120, y + 5, 9608, borFg + borBg);
	game->Draw(x + 124, y + 3, 9608, borFg + borBg);
	game->Draw(x + 126, y + 1, 9608, borFg + borBg);
	// nền
	game->Fill(x + 119, y + 2, x + 120, y + 3, 9608, mainFg + mainBg);
	game->Fill(x + 124, y + 5, x + 125, y + 6, 9608, mainFg + mainBg);
	game->DrawLine(x + 120, y + 1, x + 124, y + 1, 9608, mainFg + mainBg);
	game->DrawLine(x + 120, y + 4, x + 124, y + 4, 9608, mainFg + mainBg);
	game->DrawLine(x + 120, y + 7, x + 124, y + 7, 9608, mainFg + mainBg);
	game->DrawLine(x + 119, y + 6, x + 120, y + 6, 9608, mainFg + mainBg);
	game->DrawLine(x + 124, y + 2, x + 125, y + 2, 9608, mainFg + mainBg);

}
void StateWin::CG_BannerBorder(const int& x, const int& y) {
	// outer border
	game->DrawLine(x, y, x, y + 18, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 136, y, x + 136, y + 18, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 1, y, x + 135, y, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 1, y + 18, x + 135, y + 18, 9608, FG_GREY + BG_GREY);

	game->DrawLine(x + 21, y + 21, x + 23, y + 19, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 24, y + 20, x + 25, y + 21, 9608, FG_GREY + BG_GREY);

	game->DrawLine(x + 114, y + 21, x + 116, y + 19, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 117, y + 20, x + 118, y + 21, 9608, FG_GREY + BG_GREY);

	// inner border
	game->DrawLine(x + 1, y + 1, x + 1, y + 17, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 135, y + 1, x + 135, y + 17, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 1, x + 134, y + 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 17, x + 135, y + 17, 9608, FG_BLACK + BG_BLACK);

	game->DrawLine(x + 22, y + 21, x + 24, y + 19, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 25, y + 20, x + 26, y + 21, 9608, FG_BLACK + BG_BLACK);

	game->DrawLine(x + 115, y + 21, x + 117, y + 19, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 118, y + 20, x + 119, y + 21, 9608, FG_BLACK + BG_BLACK);

	// TO BANNER
	game->Fill(x + 2, y + 2, x + 134, y + 16, 9608, FG_CYAN + BG_CYAN);

}
void StateWin::DrawCGBanner(const int& x, const int& y) {
	CG_BannerBorder(x, y);
	Congratulations(x + 4, y + 4);
}

// Draw Train
void StateWin::MiniWheel(const int& x, const int& y) {
	// viền
	game->DrawLine(x + 1, y, x + 2, y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 3, x + 2, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x, y + 1, x, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y + 1, x + 3, y + 2, 9608, FG_BLACK + BG_BLACK);

	// màu
	game->DrawLine(x + 1, y + 2, x + 2, y + 2, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Draw(x + 2, y + 1, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Draw(x + 1, y + 1, 9608, FG_YELLOW + BG_YELLOW);

}
void StateWin::DrawTrainWheel(const int& x, const int& y) {
	// viền
	// outer
	game->DrawLine(x, y + 4, x, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 8, x + 2, y + 9, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y + 9, x + 17, y + 9, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 18, y + 8, x + 19, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 19, y + 4, x + 19, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 16, y + 1, x + 18, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 4, y, x + 15, y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 3, x + 3, y + 1, 9608, FG_BLACK + BG_BLACK);
	// inner
	game->DrawLine(x + 4, y + 2, x + 16, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 4, x + 3, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 5, x + 2, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 7, x + 3, y + 8, 9608, FG_BLACK + BG_BLACK);

	// bánh xe
	MiniWheel(x + 4, y + 4);
	MiniWheel(x + 9, y + 4);
	MiniWheel(x + 14, y + 4);

	// to nen ngoài
	game->DrawLine(x + 1, y + 5, x + 1, y + 6, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 1, y + 7, x + 2, y + 8, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 1, y + 4, x + 3, y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 4, y + 1, x + 15, y + 1, 9608, FG_YELLOW + BG_YELLOW);

	// nền trong bánh xe
	game->DrawLine(x + 3, y + 4, x + 3, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 18, y + 4, x + 18, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 4, y + 3, x + 17, y + 3, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 4, y + 8, x + 17, y + 8, 9608, FG_DARK_GREY + BG_DARK_GREY);

	game->DrawLine(x + 7, y + 4, x + 9, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 7, y + 7, x + 9, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 12, y + 4, x + 14, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 12, y + 7, x + 14, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);

	game->DrawLine(x + 8, y + 5, x + 8, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 13, y + 5, x + 13, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);

	game->Draw(x + 4, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 4, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 17, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 17, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);

}
void StateWin::TrainLocomotive(const int& x, const int& y) {
	// viền
	game->DrawLine(x, y + 25, x, y + 26, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 27, x + 2, y + 27, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y + 28, x + 5, y + 28, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 24, x + 5, y + 20, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y + 27, x + 9, y + 23, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 20, x + 8, y + 22, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 6, y + 29, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 27, y + 30, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 9, y + 22, x + 30, y + 22, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 30, y + 3, x + 30, y + 21, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 25, y + 3, x + 29, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 25, y + 1, x + 25, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 26, y + 4, x + 26, y + 11, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 27, y + 12, x + 28, y + 13, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 28, y + 14, x + 28, y + 18, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 26, y + 20, x + 27, y + 19, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 11, y + 20, x + 25, y + 20, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 10, y + 18, x + 10, y + 19, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 19, x + 9, y + 19, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 8, y + 17, x + 8, y + 18, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 16, x + 7, y + 17, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 14, x + 6, y + 15, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 7, y + 13, x + 8, y + 13, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 9, y + 14, x + 9, y + 16, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 8, y + 12, x + 9, y + 11, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 10, y + 11, x + 10, y + 12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 11, y + 13, x + 11, y + 17, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 11, y + 6, x + 11, y + 11, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 14, y + 6, x + 14, y + 11, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 10, y + 2, x + 10, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 15, y + 2, x + 15, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 11, y + 2, x + 14, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 12, y + 6, x + 13, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 12, y + 12, x + 13, y + 12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 15, y + 11, x + 25, y + 11, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 26, y, x + 45, y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 46, y + 1, x + 45, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 31, y + 2, x + 44, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 43, y + 5, x + 46, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 42, y + 6, x + 42, y + 14, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 41, y + 14, x + 41, y + 20, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 42, y + 20, x + 43, y + 21, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 33, y + 14, x + 40, y + 14, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 33, y + 15, x + 33, y + 21, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 33, y + 22, x + 42, y + 22, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 33, y + 6, x + 40, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 33, y + 11, x + 40, y + 11, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 33, y + 7, x + 33, y + 10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 40, y + 7, x + 40, y + 10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 48, y + 21, x + 48, y + 24, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x + 43, y + 22, x + 47, y + 23, 9608, FG_BLACK + BG_BLACK);

	// vẼ BÁNH XE
	DrawTrainWheel(x + 7, y + 24);
	DrawTrainWheel(x + 28, y + 24);

	// Tô màu cho xe lửa
	game->DrawLine(x + 1, y + 26, x + 6, y + 21, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 3, y + 26, x + 7, y + 22, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 3, y + 27, x + 4, y + 27, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 5, y + 26, x + 8, y + 23, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 6, y + 27, x + 6, y + 28, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 7, y + 27, x + 10, y + 24, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 7, y + 16, x + 8, y + 15, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 9, y + 17, x + 10, y + 16, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 9, y + 18, x + 10, y + 17, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(x + 8, y + 16, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 11, y + 12, x + 12, y + 13, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 13, y + 13, x + 14, y + 13, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 14, y + 12, x + 15, y + 12, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 11, y + 18, x + 11, y + 19, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 27, y + 13, x + 27, y + 18, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(x + 12, y + 17, x + 23, y + 19, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(x + 24, y + 16, x + 26, y + 19, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 23, y + 24, x + 31, y + 24, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 24, y + 25, x + 30, y + 25, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 25, y + 26, x + 29, y + 26, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 26, y + 27, x + 28, y + 27, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 27, y + 28, x + 27, y + 29, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 31, y + 3, x + 44, y + 3, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 41, y + 4, x + 43, y + 4, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 32, y + 5, x + 40, y + 5, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 32, y + 6, x + 32, y + 11, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 32, y + 13, x + 41, y + 13, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 32, y + 23, x + 42, y + 23, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 32, y + 14, x + 32, y + 22, 9608, FG_DARK_RED + BG_DARK_RED);

	game->DrawLine(x + 1, y + 25, x + 5, y + 21, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 2, y + 26, x + 6, y + 22, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 4, y + 26, x + 7, y + 23, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 7, y + 26, x + 10, y + 23, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 11, y + 23, x + 31, y + 23, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 7, y + 14, x + 7, y + 15, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 8, y + 14, x + 9, y + 13, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 9, y + 12, x + 10, y + 13, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 10, y + 14, x + 10, y + 15, 9608, FG_RED + BG_RED);
	game->Fill(x + 12, y + 14, x + 14, y + 16, 9608, FG_RED + BG_RED);
	game->Fill(x + 16, y + 12, x + 26, y + 15, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 15, y + 13, x + 15, y + 16, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 16, y + 16, x + 23, y + 16, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 31, y + 4, x + 31, y + 22, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 32, y + 4, x + 40, y + 4, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 32, y + 12, x + 41, y + 12, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 41, y + 6, x + 41, y + 11, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 41, y + 5, x + 42, y + 5, 9608, FG_RED + BG_RED);

	game->DrawLine(x + 11, y + 3, x + 14, y + 3, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 11, y + 4, x + 13, y + 4, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 12, y + 8, x + 12, y + 10, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 26, y + 1, x + 42, y + 1, 9608, FG_YELLOW + BG_YELLOW);

	game->DrawLine(x + 11, y + 5, x + 13, y + 5, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 14, y + 4, x + 14, y + 5, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 13, y + 8, x + 13, y + 10, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 12, y + 7, x + 13, y + 7, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 12, y + 11, x + 13, y + 11, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 26, y + 2, x + 30, y + 2, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 43, y + 1, x + 45, y + 1, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	game->Fill(x + 34, y + 15, x + 40, y + 21, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 41, y + 21, x + 42, y + 21, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 7, y + 20, x + 10, y + 20, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 8, y + 21, x + 29, y + 21, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 27, y + 20, x + 29, y + 20, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 28, y + 19, x + 29, y + 19, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 28, y + 12, x + 29, y + 12, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 29, y + 13, x + 29, y + 18, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Fill(x + 27, y + 4, x + 29, y + 11, 9608, FG_DARK_GREY + BG_DARK_GREY);

	game->DrawLine(x + 34, y + 10, x + 39, y + 10, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
	game->DrawLine(x + 36, y + 9, x + 39, y + 9, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
	game->DrawLine(x + 38, y + 8, x + 39, y + 8, 9608, FG_DARK_CYAN + BG_DARK_CYAN);

	game->DrawLine(x + 34, y + 9, x + 35, y + 9, 9608, FG_CYAN + BG_CYAN);
	game->DrawLine(x + 34, y + 8, x + 37, y + 8, 9608, FG_CYAN + BG_CYAN);
	game->DrawLine(x + 34, y + 7, x + 39, y + 7, 9608, FG_CYAN + BG_CYAN);

}
void StateWin::TrainWagon(const int& x, const int& y) {
	// viền
	game->DrawLine(x, y + 2, x, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x, y + 1, x + 149, y + 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x, y + 4, x + 149, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 152, y + 1, x + 152, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x + 150, y, x + 151, y + 5, 9608, FG_BLACK + BG_BLACK);

	// vẼ BÁNH XE
	DrawTrainWheel(x + 10, y + 4);
	DrawTrainWheel(x + 49, y + 4);
	DrawTrainWheel(x + 88, y + 4);
	DrawTrainWheel(x + 128, y + 4);

	// Tô màu 

	game->DrawLine(x + 1, y + 3, x + 149, y + 3, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 1, y + 2, x + 149, y + 2, 9608, FG_RED + BG_RED);

}
void StateWin::Smoke(const int& x, const int& y) {
	const vector<pair<short, short>> ColorList = {
		{FG_BLACK, BG_BLACK},
		{FG_DARK_GREY, BG_DARK_GREY},
		{FG_WHITE, BG_WHITE}
	};

	int dummy = 0;
	// layer 1
	game->Fill(x + 5, y + 21, x + 6, y + 22, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 7, y + 20, x + 8, y + 19, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 8, y + 17, x + 10, y + 18, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 11, y + 16, x + 14, y + 17, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Draw(x + 12, y + 15, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 15, y + 16, x + 16, y + 15, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 12, y + 10, x + 13, y + 9, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 13, y + 4, x + 15, y + 4, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 15, y + 7, x + 15, y + 9, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 16, y + 9, x + 16, y + 10, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 20, y + 10, x + 21, y + 9, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 17, y + 10, x + 19, y + 11, 9608, ColorList[dummy].first + ColorList[dummy].second);

	++dummy;
	// layer 2
	game->Fill(x + 1, y + 17, x + 2, y + 18, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 2, y + 21, x + 4, y + 22, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 3, y + 19, x + 6, y + 20, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 3, y + 12, x + 6, y + 14, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 3, y + 12, x + 6, y + 14, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 9, y + 9, x + 11, y + 11, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 12, y + 2, x + 13, y + 3, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 14, y + 3, x + 16, y + 3, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 16, y + 8, x + 17, y + 9, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 18, y + 9, x + 19, y + 9, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 20, y + 9, x + 21, y + 8, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 20, y + 8, x + 21, y + 7, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 16, y + 13, x + 16, y + 14, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 11, y + 15, x + 12, y + 14, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 12, y + 13, x + 13, y + 14, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 13, y + 15, x + 15, y + 15, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 2, y + 11, x + 2, y + 13, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 4, y + 15, x + 7, y + 15, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 7, y + 16, x + 10, y + 16, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 7, y + 12, x + 8, y + 11, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 7, y + 11, x + 8, y + 10, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 11, y + 12, x + 12, y + 11, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 12, y + 9, x + 13, y + 8, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 9, y + 8, x + 10, y + 8, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x, y + 18, x, y + 22, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Draw(x + 1, y + 22, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Draw(x + 3, y + 16, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Draw(x + 9, y + 7, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Draw(x + 7, y + 19, 9608, ColorList[dummy].first + ColorList[dummy].second);

	++dummy;
	// layer 3
	game->Fill(x + 1, y + 19, x + 2, y + 20, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 1, y + 14, x + 2, y + 16, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 3, y + 17, x + 7, y + 18, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 8, y + 12, x + 10, y + 15, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 17, y + 5, x + 19, y + 8, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 14, y + 1, x + 16, y + 2, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 3, y + 8, x + 7, y + 10, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 10, y + 6, x + 13, y + 7, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Fill(x + 13, y + 12, x + 15, y + 13, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x, y + 15, x, y + 17, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 3, y + 15, x + 4, y + 16, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 5, y + 16, x + 6, y + 16, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 12, y + 1, x + 13, y + 1, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 13, y, x + 15, y, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 16, y + 6, x + 16, y + 7, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 20, y + 6, x + 20, y + 7, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 14, y + 14, x + 15, y + 14, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 14, y + 11, x + 12, y + 12, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 11, y + 8, x + 12, y + 8, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 9, y + 6, x + 10, y + 5, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 11, y + 5, x + 12, y + 5, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 2, y + 9, x + 2, y + 10, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 3, y + 11, x + 6, y + 11, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 4, y + 7, x + 7, y + 7, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 8, y + 8, x + 8, y + 9, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 7, y + 13, x + 7, y + 14, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->DrawLine(x + 11, y + 13, x + 11, y + 14, 9608, ColorList[dummy].first + ColorList[dummy].second);
	game->Draw(x + 1, y + 21, 9608, ColorList[dummy].first + ColorList[dummy].second);

}