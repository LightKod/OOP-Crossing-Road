#include "StateLB.h"
#include "StateMenu.h"

const int StateLB::M_S_SRC_X0 = 20;
const int StateLB::M_S_SRC_X1 = 140;
const int StateLB::M_S_SRC_Y0 = 4;
const int StateLB::M_S_SRC_Y1 = 92;

const COORD StateLB::M_S_COL_2{ M_S_SRC_X0 + 5, M_S_SRC_Y1 - 55 };
const COORD StateLB::M_S_COL_1{ M_S_SRC_X0 +41, M_S_SRC_Y1 - 65 };
const COORD StateLB::M_S_COL_3{ M_S_SRC_X0 +77, M_S_SRC_Y1 - 45 };

bool StateLB::Update(float fElapsedTime) {
	thread t1(&StateLB::AnimationThread, this);

	while (!m_bBack) {}

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
	// clear screen
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);

	game->DrawLine(0, M_S_SRC_Y1 + 1, 
		game->ScreenWidth(), M_S_SRC_Y1 + 1,
		9608, FG_BLACK + BG_BLACK);

	DrawPodium(M_S_COL_2.X, M_S_COL_2.Y);
	DrawPodium(M_S_COL_1.X, M_S_COL_1.Y);
	DrawPodium(M_S_COL_3.X, M_S_COL_3.Y);
	game->ConsOutput();

	ShowRank3();
	ShowRank2();
	ShowRank1();

	m_bBack = true;
}


bool StateLB::OnStateEnter() {
	this->game = game;

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

void StateLB::ShowDataEffect(const COORD& _C) {
	this_thread::sleep_for(std::chrono::milliseconds(1000));

	string2Pixel(m_Datas[m_CurrIndex].m_Name,
		_C.X + 18 - 4 * m_Datas[m_CurrIndex].m_Name.size() / 2,
		_C.Y - 7, FG_WHITE, BG_BLUE);
	string2Pixel(m_Datas[m_CurrIndex].m_Score,
		_C.X + 14 - 4 * m_Datas[m_CurrIndex].m_Score.size() / 2,
		_C.Y + 28, FG_WHITE, BG_MAGENTA);
}
void StateLB::ShowRank3() {
	if (m_CurrIndex >= m_Datas.size()) {
		--m_CurrIndex;
		return;
	}

	ShowDataEffect(M_S_COL_3);
	DrawMedal(M_S_COL_3.X + 8, M_S_COL_3.Y - 1, 3);
	game->ConsOutput();

	--m_CurrIndex;
}
void StateLB::ShowRank2() {
	if (m_CurrIndex >= m_Datas.size()) {
		--m_CurrIndex;
		return;
	}

	ShowDataEffect(M_S_COL_2);
	DrawMedal(M_S_COL_2.X + 8, M_S_COL_2.Y - 1, 2);
	game->ConsOutput();

	--m_CurrIndex;
}
void StateLB::ShowRank1() {
	if (m_CurrIndex >= m_Datas.size()) {
		--m_CurrIndex;
		return;
	}

	ShowDataEffect(M_S_COL_1);
	DrawMedal(M_S_COL_1.X + 8, M_S_COL_1.Y - 1, 1);
	game->ConsOutput();

	this_thread::sleep_for(std::chrono::milliseconds(100));
	DrawCrown();
	game->ConsOutput();
}

void StateLB::DrawPodium(const int& x, const int& y) {
	static const int _y1 = M_S_SRC_Y1;

	game->Fill(x	 , y, x + 30, _y1, 9608, FG_MAGENTA + BG_MAGENTA);
	game->Fill(x + 31, y, x + 40, _y1, 9608, FG_DARK_MAGENTA + BG_DARK_MAGENTA);
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

void StateLB::DrawCrown() {
	static const int _x = M_S_COL_1.X + 9;
	static const int _y = M_S_SRC_Y0 - 2;
	
	// Viền đen
	game->DrawLine(_x	 , _y + 3, _x	 , _y +12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x +20, _y + 3, _x +20, _y +12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 1, _y +13, _x +19, _y +13, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 9, _y + 6, _x +11, _y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 9, _y +10, _x +11, _y +10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + 8, _y + 7, _x + 8, _y + 9, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x +12, _y + 7, _x +12, _y + 9, 9608, FG_BLACK + BG_BLACK);
	
	game->Draw(_x + 1, _y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 2, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 3, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 4, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 5, _y + 6, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 6, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 7, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 8, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 9, _y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x +10, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x +11, _y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x +12, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x +13, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x +14, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x +15, _y + 6, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x +16, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x +17, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x +18, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x +19, _y + 2, 9608, FG_BLACK + BG_BLACK);

	game->Draw(_x + 3, _y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 4, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 5, _y	 , 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 6, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 7, _y + 2, 9608, FG_BLACK + BG_BLACK);

	game->Draw(_x +13, _y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x +14, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x +15, _y	 , 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x +16, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x +17, _y + 2, 9608, FG_BLACK + BG_BLACK);

	// Viền vàng đậm
	game->DrawLine(_x + 1, _y + 3, _x + 1, _y +12, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(_x +19, _y + 3, _x +19, _y +12, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(_x + 2, _y +12, _x +18, _y +12, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	game->DrawLine(_x + 5, _y + 2, _x + 6, _y + 2, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(_x + 4, _y + 3, _x + 7, _y + 3, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(_x + 4, _y + 4, _x + 6, _y + 4, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Draw(_x + 5, _y + 5, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);


	game->DrawLine(_x +15, _y + 2, _x +16, _y + 2, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(_x +14, _y + 3, _x +17, _y + 3, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(_x +14, _y + 4, _x +16, _y + 4, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Draw(_x +15, _y + 5, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	// Tô nèn vàng nhạt
	game->Draw(_x + 5, _y + 1, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 4, _y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 3, _y + 3, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x +15, _y + 1, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x +14, _y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x +13, _y + 3, 9608, FG_YELLOW + BG_YELLOW);

	game->DrawLine(_x + 2, _y + 4, _x + 2, _y +11, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x +18, _y + 4, _x +18, _y +11, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 3, _y +11, _x +17, _y +11, 9608, FG_YELLOW + BG_YELLOW);

	game->DrawLine(_x + 3, _y + 5, _x + 3, _y + 7, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 4, _y + 6, _x + 4, _y + 8, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 5, _y + 7, _x + 5, _y + 9, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 6, _y + 6, _x + 6, _y +10, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 7, _y + 5, _x + 7, _y +10, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x + 8, _y + 4, _x + 8, _y + 6, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x +10, _y + 4, _x +10, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x +11, _y + 3, _x +11, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x +12, _y + 4, _x +12, _y + 6, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x +13, _y + 5, _x +13, _y +10, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x +14, _y + 6, _x +14, _y +10, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x +15, _y + 7, _x +15, _y +10, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x +16, _y + 6, _x +16, _y +10, 9608, FG_YELLOW + BG_YELLOW);
	game->DrawLine(_x +17, _y + 5, _x +17, _y +10, 9608, FG_YELLOW + BG_YELLOW);

	game->Draw(_x +10, _y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 9, _y + 3, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 9, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 8, _y +10, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x +12, _y +10, 9608, FG_YELLOW + BG_YELLOW);

	// Vẽ ruby đỏ
	game->DrawLine(_x + 9, _y + 7, _x + 9, _y + 9, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(_x +10, _y + 9, _x +11, _y + 9, 9608, FG_DARK_RED + BG_DARK_RED);

	game->DrawLine(_x +10, _y + 7, _x +10, _y + 8, 9608, FG_RED + BG_RED);
	game->Draw(_x +11, _y + 8, 9608, FG_RED + BG_RED);

	// Hiệu ứng ánh sáng
	game->Draw(_x +11, _y + 7, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x +10, _y + 3, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + 9, _y + 4, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + 5, _y +10, 9608, FG_WHITE + BG_WHITE);

	game->DrawLine(_x + 4, _y + 9, _x + 4, _y + 10, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + 3, _y + 8, _x + 3, _y + 10, 9608, FG_WHITE + BG_WHITE);
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