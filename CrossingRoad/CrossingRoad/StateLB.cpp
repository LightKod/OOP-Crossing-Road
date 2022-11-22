#include "StateLB.h"
#include "StateMenu.h"

const int StateLB::M_S_SRC_X0 = 20;
const int StateLB::M_S_SRC_X1 = 140;
const int StateLB::M_S_SRC_Y0 = 4;
const int StateLB::M_S_SRC_Y1 = 92;

const COORD StateLB::M_S_COL_2{ M_S_SRC_X0 + 5, M_S_SRC_Y1 - 48 };
const COORD StateLB::M_S_COL_1{ M_S_SRC_X0 +41, M_S_SRC_Y1 - 58 };
const COORD StateLB::M_S_COL_3{ M_S_SRC_X0 +77, M_S_SRC_Y1 - 38 };

bool StateLB::Update(float fElapsedTime) {
	thread t1(&StateLB::AnimationThread, this);

	while (!m_bBack);

	//https://stackoverflow.com/questions/23129870/how-do-i-clean-input-buffer-before-using-getch
	char escChar = ' ';
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	while (1) {
		if (_kbhit) {
			if ((escChar = _getch()) == VK_ESCAPE) {
				break;
			}
		}
	}

	// Kết thúc thread Animation
	t1.join();

	// Xử lý quay về main menu
	game->SetState(new StateMenu(game));

	return true;
}

void StateLB::AnimationThread() {
	Intro();

	ShowRank3();
	ShowRank2();
	ShowRank1();

	PostEffect();

	m_bBack = true;
}


bool StateLB::OnStateEnter() {
	this->game = game;

	// clear screen
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);

	// Get saved data
	GetDataRecord();
	sort(m_Datas.begin(), m_Datas.end(),
		[&](const Data& a, const Data& b) -> bool {
			if (a.m_Score > b.m_Score)
				return 1;
			return 0;
		});

	return 1;
}
bool StateLB::OnStateExit() {
	return 0;
}

void StateLB::Intro() {
	static const int _tm = 20;// 25
	
	for (int i = 0; i < game->ScreenWidth(); i+=8) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		game->DrawLine(i, M_S_SRC_Y1 + 1,
					i + 7, M_S_SRC_Y1 + 1, 9608, FG_BLACK + BG_BLACK);
		game->Fill(i, M_S_SRC_Y1 + 2,
			i + 7, game->ScreenHeight(), 9608, FG_CYAN + BG_CYAN);
		
		game->ConsOutput();
	}

	int _x = game->ScreenWidth() - 7;
	DrawPodium(_x, M_S_COL_2.Y);
	game->ConsOutput();
	for (_x -= 8; _x >= M_S_COL_2.X; _x -= 8) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));
		
		// clear old spr
		game->Fill(_x + 8, M_S_COL_1.Y,
			game->ScreenWidth(), M_S_SRC_Y1, L' ', BG_BLUE);

		// draw new spr
		DrawPodium(_x, M_S_COL_2.Y);
		DrawPodium(_x + 36, M_S_COL_1.Y);
		DrawPodium(_x + 72, M_S_COL_3.Y);

		game->ConsOutput();
	}
}

void StateLB::PostEffect() {
	static const int _x = M_S_COL_1.X + 8;
	static const int _y = M_S_SRC_Y0 - 18;
	static const int _tm = 25;// 25
	
	this_thread::sleep_for(std::chrono::milliseconds(100));
	DrawCrown(_x, _y);
	game->ConsOutput();
	for (int i = 1; i < 26; ++i) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		// clear old spr
		game->Fill(_x, _y + i - 1, _x + 20, _y + i + 2, L' ', BG_BLUE);
		// draw new spr
		DrawCrown(_x, _y + i);

		game->ConsOutput();
	}

	this_thread::sleep_for(std::chrono::milliseconds(120));
	Firework(_x, _y);
	game->ConsOutput();
}
void StateLB::Firework(const int& _x, const int& _y) {
	game->Fill(_x - 30, _y + 40, _x - 29, _y + 41, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x - 36, _y + 26, _x - 35, _y + 27, 9608, FG_GREEN + BG_GREEN);
	game->Fill(_x - 26, _y + 31, _x - 25, _y + 32, 9608, FG_RED + BG_RED);
	game->Fill(_x - 19, _y + 16, _x - 18, _y + 17, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x - 13, _y + 24, _x - 12, _y + 25, 9608, FG_CYAN + BG_CYAN);
	game->Fill(_x + 13, _y + 17, _x + 14, _y + 18, 9608, FG_RED + BG_RED);
	game->Fill(_x + 24, _y + 26, _x + 25, _y + 27, 9608, FG_RED + BG_RED);
	game->Fill(_x + 32, _y + 18, _x + 33, _y + 19, 9608, FG_RED + BG_RED);
	game->Fill(_x + 46, _y + 24, _x + 47, _y + 25, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 58, _y + 42, _x + 59, _y + 43, 9608, FG_RED + BG_RED);

	game->Fill(_x - 31, _y + 16, _x - 30, _y + 17, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x - 15, _y + 33, _x - 14, _y + 34, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x - 7, _y + 14, _x - 6, _y + 15, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x +28, _y + 16, _x +29, _y + 17, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x +38, _y + 30, _x + 39, _y + 31, 9608, FG_GREEN + BG_GREEN);
	game->Fill(_x +43, _y + 37, _x +44, _y + 38, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x +52, _y + 27, _x +53, _y + 28, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x +65, _y + 22, _x +66, _y + 23, 9608, FG_YELLOW + BG_YELLOW);
}
void StateLB::DrawCrown(const int& _x, const int& _y) {
	// Viền đen
	game->DrawLine(_x, _y + 3, _x, _y + 12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 20, _y + 3, _x + 20, _y + 12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 1, _y + 13, _x + 19, _y + 13, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 9, _y + 6, _x + 11, _y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 9, _y + 10, _x + 11, _y + 10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 8, _y + 7, _x + 8, _y + 9, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 12, _y + 7, _x + 12, _y + 9, 9608, FG_BLACK + BG_BLACK);

	game->Draw(_x + 1, _y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 2, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 3, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 4, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 5, _y + 6, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 6, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 7, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 8, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 9, _y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 10, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 11, _y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 12, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 13, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 14, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 15, _y + 6, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 16, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 17, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 18, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 19, _y + 2, 9608, FG_BLACK + BG_BLACK);

	game->Draw(_x + 3, _y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 4, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 5, _y, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 6, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 7, _y + 2, 9608, FG_BLACK + BG_BLACK);

	game->Draw(_x + 13, _y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 14, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 15, _y, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 16, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 17, _y + 2, 9608, FG_BLACK + BG_BLACK);

	// Viền vàng đậm
	game->DrawLine(_x + 1, _y + 3, _x + 1, _y + 12, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(_x + 19, _y + 3, _x + 19, _y + 12, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(_x + 2, _y + 12, _x + 18, _y + 12, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	game->DrawLine(_x + 5, _y + 2, _x + 6, _y + 2, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(_x + 4, _y + 3, _x + 7, _y + 3, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(_x + 4, _y + 4, _x + 6, _y + 4, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Draw(_x + 5, _y + 5, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);


	game->DrawLine(_x + 15, _y + 2, _x + 16, _y + 2, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(_x + 14, _y + 3, _x + 17, _y + 3, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(_x + 14, _y + 4, _x + 16, _y + 4, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Draw(_x + 15, _y + 5, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	// Tô nèn vàng nhạt
	game->Draw(_x + 5, _y + 1, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 4, _y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 3, _y + 3, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 15, _y + 1, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 14, _y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 13, _y + 3, 9608, FG_YELLOW + BG_YELLOW);

	game->DrawLine(_x + 2, _y + 4, _x + 2, _y + 11, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 18, _y + 4, _x + 18, _y + 11, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 3, _y + 11, _x + 17, _y + 11, 9608, FG_YELLOW + BG_YELLOW);

	game->DrawLine(_x + 3, _y + 5, _x + 3, _y + 7, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 4, _y + 6, _x + 4, _y + 8, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 5, _y + 7, _x + 5, _y + 9, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 6, _y + 6, _x + 6, _y + 10, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 7, _y + 5, _x + 7, _y + 10, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 8, _y + 4, _x + 8, _y + 6, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 10, _y + 4, _x + 10, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 11, _y + 3, _x + 11, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 12, _y + 4, _x + 12, _y + 6, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 13, _y + 5, _x + 13, _y + 10, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 14, _y + 6, _x + 14, _y + 10, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 15, _y + 7, _x + 15, _y + 10, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 16, _y + 6, _x + 16, _y + 10, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 17, _y + 5, _x + 17, _y + 10, 9608, FG_YELLOW + BG_YELLOW);

	game->Draw(_x + 10, _y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 9, _y + 3, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 9, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 8, _y + 10, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 12, _y + 10, 9608, FG_YELLOW + BG_YELLOW);

	// Vẽ ruby đỏ
	game->DrawLine(_x + 9, _y + 7, _x + 9, _y + 9, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(_x + 10, _y + 9, _x + 11, _y + 9, 9608, FG_DARK_RED + BG_DARK_RED);

	game->DrawLine(_x + 10, _y + 7, _x + 10, _y + 8, 9608, FG_RED + BG_RED);
	game->Draw(_x + 11, _y + 8, 9608, FG_RED + BG_RED);

	// Hiệu ứng ánh sáng
	game->Draw(_x + 11, _y + 7, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + 10, _y + 3, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + 9, _y + 4, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + 5, _y + 10, 9608, FG_WHITE + BG_WHITE);

	game->DrawLine(_x + 4, _y + 9, _x + 4, _y + 10, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 3, _y + 8, _x + 3, _y + 10, 9608, FG_WHITE + BG_WHITE);
}

void StateLB::ShowDataEffect(const COORD& _C) {
	static const int _tm = 50;// 25
	int dummy = -2;

	// 1st frame
	this_thread::sleep_for(std::chrono::milliseconds(900));
	string2Pixel(m_Datas[m_CurrIndex].m_Score,
		_C.X + 15 - 4 * m_Datas[m_CurrIndex].m_Score.size() / 2,
		_C.Y + 28, FG_WHITE, BG_MAGENTA);
	game->ConsOutput();

	/**********************************************************/
	// 2nd frame
	this_thread::sleep_for(std::chrono::milliseconds(600));
	string2Pixel(m_Datas[m_CurrIndex].m_Name,
		_C.X + 16 - 4 * m_Datas[m_CurrIndex].m_Name.size() / 2,
		_C.Y - 6 + dummy, FG_DARK_GREY, BG_BLUE);
	game->ConsOutput();

	/**********************************************************/
	// 3rd frame
	this_thread::sleep_for(std::chrono::milliseconds(_tm));
	// clear old name
	string2Pixel(m_Datas[m_CurrIndex].m_Name,
		_C.X + 16 - 4 * m_Datas[m_CurrIndex].m_Name.size() / 2,
		_C.Y - 6 + dummy++, FG_BLUE, BG_BLUE);
	// draw new name
	string2Pixel(m_Datas[m_CurrIndex].m_Name,
		_C.X + 16 - 4 * m_Datas[m_CurrIndex].m_Name.size() / 2,
		_C.Y - 6 + dummy, FG_GREY, BG_BLUE);
	game->ConsOutput();

	/**********************************************************/
	// 4th frame
	this_thread::sleep_for(std::chrono::milliseconds(_tm));
	// clear old name
	string2Pixel(m_Datas[m_CurrIndex].m_Name,
		_C.X + 16 - 4 * m_Datas[m_CurrIndex].m_Name.size() / 2,
		_C.Y - 6 + dummy++, FG_BLUE, BG_BLUE);
	// draw new name
	string2Pixel(m_Datas[m_CurrIndex].m_Name,
		_C.X + 16 - 4 * m_Datas[m_CurrIndex].m_Name.size() / 2,
		_C.Y - 6 + dummy, FG_WHITE, BG_BLUE);
	game->ConsOutput();
}
void StateLB::ShowRank3() {
	if (m_CurrIndex >= m_Datas.size()) {
		--m_CurrIndex;
		return;
	}

	DrawMedal(M_S_COL_3.X + 8, M_S_COL_3.Y - 1, 3);
	ShowDataEffect(M_S_COL_3);

	--m_CurrIndex;
}
void StateLB::ShowRank2() {
	if (m_CurrIndex >= m_Datas.size()) {
		--m_CurrIndex;
		return;
	}

	DrawMedal(M_S_COL_2.X + 8, M_S_COL_2.Y - 1, 2);
	ShowDataEffect(M_S_COL_2);

	--m_CurrIndex;
}
void StateLB::ShowRank1() {
	if (m_CurrIndex >= m_Datas.size()) {
		--m_CurrIndex;
		return;
	}

	DrawMedal(M_S_COL_1.X + 8, M_S_COL_1.Y - 1, 1);
	ShowDataEffect(M_S_COL_1);
}

void StateLB::DrawPodium(const int& x, const int& y) {
	static const int _y1 = M_S_SRC_Y1;

	game->Fill(x	 , y, x + 30, _y1, 9608, FG_MAGENTA + BG_MAGENTA);
	game->Fill(x + 31, y, x + 38, _y1, 9608, FG_DARK_MAGENTA + BG_DARK_MAGENTA);
}

void StateLB::DrawMedal(const int& x, const int& y, const int& rank) {
	// Vẽ viền đen
	game->DrawLine(x + 1, y    , x + 5, y	 , 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 6, y + 1, x +13, y + 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x	, y + 1, x	  , y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 3, x + 1, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 5, x + 2, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y + 7, x + 3, y + 9, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 4, y +10, x + 4, y +11, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +13, y + 2, x +13, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +12, y + 4, x +12, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +11, y + 6, x +11, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +10, y + 8, x +10, y + 9, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 9, y + 8, x + 9, y +11, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 7, y + 3, x + 7, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 8, y + 5, x + 8, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 6, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 5, y +11, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 8, y +11, 9608, FG_BLACK + BG_BLACK);

	game->DrawLine(x + 5, y +13, x + 8, y +13, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y +22, x + 8, y +22, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 4, y +24, x + 9, y +24, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x	, y +15, x	  , y +20, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +13, y +15, x +13, y +20, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y +16, x + 2, y +19, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +11, y +16, x +11, y +19, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 3, y +12, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 2, y +13, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 1, y +14, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 1, y +21, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 2, y +22, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 3, y +23, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x +10, y +23, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x +11, y +22, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x +12, y +21, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x +10, y +12, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x +11, y +13, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x +12, y +14, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 4, y +14, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 3, y +15, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 3, y +20, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 4, y +21, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 9, y +21, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x +10, y +20, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x +10, y +15, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 9, y +14, 9608, FG_BLACK + BG_BLACK);

	// Tô màu dây sau
	game->Draw(x + 7, y + 2, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->Draw(x +10, y + 7, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->DrawLine(x + 8, y + 3, x + 8, y + 4, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->DrawLine(x + 9, y + 5, x + 9, y + 7, 9608, FG_DARK_BLUE + BG_DARK_BLUE);

	game->Draw(x + 8, y + 2, 9608, FG_BLUE + BG_BLUE);
	game->DrawLine(x + 9, y + 3, x + 9, y + 4, 9608, FG_BLUE + BG_BLUE);
	game->DrawLine(x +10, y + 5, x +10, y + 6, 9608, FG_BLUE + BG_BLUE);
	
	game->DrawLine(x + 9, y + 2, x +12, y + 2, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
	game->DrawLine(x +10, y + 3, x +12, y + 3, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
	game->DrawLine(x +10, y + 4, x +11, y + 4, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
	game->Draw(x + 11, y + 5, 9608, FG_DARK_CYAN + BG_DARK_CYAN);

	// Tô màu dây trước
	game->Draw(x + 1, y + 2, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->Draw(x + 2, y + 4, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->Draw(x + 5, y +10, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->Draw(x + 6, y +11, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->DrawLine(x + 3, y + 5, x + 3, y + 6, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->DrawLine(x + 4, y + 7, x + 4, y + 9, 9608, FG_DARK_BLUE + BG_DARK_BLUE);

	game->DrawLine(x + 1, y + 1, x + 2, y + 1, 9608, FG_BLUE + BG_BLUE);
	game->DrawLine(x + 2, y + 2, x + 3, y + 2, 9608, FG_BLUE + BG_BLUE);
	game->DrawLine(x + 2, y + 3, x + 3, y + 3, 9608, FG_BLUE + BG_BLUE);
	game->DrawLine(x + 3, y + 4, x + 4, y + 4, 9608, FG_BLUE + BG_BLUE);
	game->DrawLine(x + 4, y + 5, x + 4, y + 6, 9608, FG_BLUE + BG_BLUE);
	game->DrawLine(x + 5, y + 7, x + 5, y + 9, 9608, FG_BLUE + BG_BLUE);
	game->DrawLine(x + 6, y + 9, x + 6, y +10, 9608, FG_BLUE + BG_BLUE);
	game->DrawLine(x + 7, y +10, x + 7, y +11, 9608, FG_BLUE + BG_BLUE);

	game->DrawLine(x + 3, y + 1, x + 4, y + 1, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
	game->DrawLine(x + 4, y + 2, x + 4, y + 3, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
	game->DrawLine(x + 5, y + 3, x + 5, y + 6, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
	game->DrawLine(x + 6, y + 5, x + 6, y + 8, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
	game->DrawLine(x + 7, y + 8, x + 7, y + 9, 9608, FG_DARK_CYAN + BG_DARK_CYAN);

	game->DrawLine(x + 5, y + 1, x + 5, y + 2, 9608, FG_CYAN + BG_CYAN);
	game->DrawLine(x + 6, y + 3, x + 6, y + 4, 9608, FG_CYAN + BG_CYAN);
	game->DrawLine(x + 7, y + 5, x + 7, y + 7, 9608, FG_CYAN + BG_CYAN);
	game->DrawLine(x + 8, y + 8, x + 8, y +10, 9608, FG_CYAN + BG_CYAN);

	// Tô viền huy chương
	switch (rank) {
	case 1: DrawGoldMedal(x, y);	break;
	case 2: DrawSilverMedal(x, y);	break;
	case 3: DrawCopperMedal(x, y);	break;
	}

	// Hiệu ứng chiếu sáng
	game->DrawLine(x + 1, y +18, x + 1, y +19, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 3, y +16, x + 3, y +17, 9608, FG_WHITE + BG_WHITE);
	game->Fill(x + 4, y +15, x + 5, y +16, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 5, y +14, x + 6, y +14, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 7, y +12, x + 8, y +12, 9608, FG_WHITE + BG_WHITE);
}
void StateLB::DrawGoldMedal(const int& x, const int& y) {
	// Màu ngoài
	game->DrawLine(x + 4, y +12, x + 6, y +12, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 3, y +13, x + 4, y +13, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 2, y +14, x + 3, y +14, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 1, y +15, x + 2, y +15, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 1, y +16, x + 1, y +17, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 1, y +20, x + 2, y +20, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 2, y +21, x + 3, y +21, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 3, y +22, x + 4, y +22, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 4, y +23, x + 9, y +23, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 9, y +22, x +10, y +22, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x +10, y +21, x +11, y +21, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x +11, y +20, x +12, y +20, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x +12, y +15, x +12, y +19, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 9, y +12, x + 9, y +13, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x +10, y +13, x +10, y +14, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x +11, y +14, x +11, y +15, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	// Màu trong
	game->DrawLine(x + 7, y +14, x + 8, y +14, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 6, y +15, x + 9, y +15, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 6, y +16, x +10, y +16, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 4, y +17, x +10, y +17, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(x + 3, y +18, x +10, y +19, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 4, y +20, x + 9, y +20, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(x + 5, y +21, x + 8, y +21, 9608, FG_YELLOW + BG_YELLOW);

	// Tô số
	game->DrawLine(x + 7, y +15, x + 7, y +18, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Draw(x + 6, y +16, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(x + 6, y + 19, x + 8, y + 19, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
}
void StateLB::DrawSilverMedal(const int& x, const int& y) {
	// Màu ngoài
	game->DrawLine(x + 4, y + 12, x + 6, y + 12, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 3, y + 13, x + 4, y + 13, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 2, y + 14, x + 3, y + 14, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 1, y + 15, x + 2, y + 15, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 1, y + 16, x + 1, y + 17, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 1, y + 20, x + 2, y + 20, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 2, y + 21, x + 3, y + 21, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 3, y + 22, x + 4, y + 22, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 4, y + 23, x + 9, y + 23, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 9, y + 22, x + 10, y + 22, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 10, y + 21, x + 11, y + 21, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 11, y + 20, x + 12, y + 20, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 12, y + 15, x + 12, y + 19, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 9, y + 12, x + 9, y + 13, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 10, y + 13, x + 10, y + 14, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 11, y + 14, x + 11, y + 15, 9608, FG_DARK_GREY + BG_DARK_GREY);

	// Màu trong
	game->DrawLine(x + 7, y + 14, x + 8, y + 14, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 6, y + 15, x + 9, y + 15, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 6, y + 16, x + 10, y + 16, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 4, y + 17, x + 10, y + 17, 9608, FG_GREY + BG_GREY);
	game->Fill(x + 3, y + 18, x + 10, y + 19, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 4, y + 20, x + 9, y + 20, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 5, y + 21, x + 8, y + 21, 9608, FG_GREY + BG_GREY);

	// Tô số
	game->DrawLine(x + 6, y + 15, x + 8, y + 15, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 8, y + 16, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 6, y + 17, x + 8, y + 17, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 6, y + 18, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 6, y + 19, x + 8, y + 19, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateLB::DrawCopperMedal(const int& x, const int& y) {
	// Màu ngoài
	game->DrawLine(x + 4, y + 12, x + 6, y + 12, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 3, y + 13, x + 4, y + 13, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 2, y + 14, x + 3, y + 14, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 1, y + 15, x + 2, y + 15, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 1, y + 16, x + 1, y + 17, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 1, y + 20, x + 2, y + 20, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 2, y + 21, x + 3, y + 21, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 3, y + 22, x + 4, y + 22, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 4, y + 23, x + 9, y + 23, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 9, y + 22, x + 10, y + 22, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 10, y + 21, x + 11, y + 21, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 11, y + 20, x + 12, y + 20, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 12, y + 15, x + 12, y + 19, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 9, y + 12, x + 9, y + 13, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 10, y + 13, x + 10, y + 14, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 11, y + 14, x + 11, y + 15, 9608, FG_DARK_RED + BG_DARK_RED);

	// Màu trong
	game->DrawLine(x + 7, y + 14, x + 8, y + 14, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 6, y + 15, x + 9, y + 15, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 6, y + 16, x + 10, y + 16, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 4, y + 17, x + 10, y + 17, 9608, FG_RED + BG_RED);
	game->Fill(x + 3, y + 18, x + 10, y + 19, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 4, y + 20, x + 9, y + 20, 9608, FG_RED + BG_RED);
	game->DrawLine(x + 5, y + 21, x + 8, y + 21, 9608, FG_RED + BG_RED);

	// Tô số
	game->DrawLine(x + 6, y + 15, x + 8, y + 15, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(x + 8, y + 16, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 6, y + 17, x + 8, y + 17, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(x + 8, y + 18, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(x + 6, y + 19, x + 8, y + 19, 9608, FG_DARK_RED + BG_DARK_RED);
}

void StateLB::GetDataRecord() {
	wifstream wIfs(L"data_path.txt");
	wstring tmpPath;
	if (wIfs.is_open()) {
		int n;
		wIfs >> n;
		wIfs.ignore();
		m_Datas.resize(n);

		for (int i = 0; i < n; i++) {
			getline(wIfs, tmpPath);
			m_Datas[i].LoadData(tmpPath);
		}

		wIfs.close();
	}
}