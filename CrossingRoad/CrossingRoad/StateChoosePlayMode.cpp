#include "StateChoosePlayMode.h"
#include "StatePlay.h"
#include "StatePlay_Deadline.h"
#include "StatePlay_Versus.h"
#include "StatePlay_Endless.h"
#include "StateMenu.h"

const vector<COORD> StateChoosePlayMode::BORDER_COORD_LIST = {
	{30,21}, {30,41}, {30,61}, {30,81}
};
const vector<COORD> StateChoosePlayMode::TEXT_COORD_LIST = {
	{65,26}, {60,46}, {62,66}, {65,86}
};
const short StateChoosePlayMode::BG_COLOR = BG_DARK_CYAN;

bool StateChoosePlayMode::Update(float fElapsedTime) {
	static const int MAX_OPT = 4;
	
	if (game->GetKey(VK_ESCAPE).bPressed) {
		game->SetState(new StateMenu(game));
		return 1;
	}

	// Xử lý chuyển state
	if (game->GetKey(VK_SPACE).bPressed) {
		ChangeStateAnimation();

		// Tạo state mới
		switch (this->UserChoice) {
		case 0:
			game->SetState(new StatePlay(game));
			break;
		case 1:
			game->SetState(new StatePlay_Deadline(game));
			break;
		case 2:
			game->SetState(new StatePlay_Endless(game));
			break;
		case 3:
			game->SetState(new StatePlay_Versus(game));
			break;
		default:
			break;
		}

		return 1;
	}

	// Xử lý tương tác với người dùng
	if (game->GetKey(VK_W).bPressed) {
		UserChoice = (UserChoice - 1 + MAX_OPT) % MAX_OPT;
		UpdateUserChoice();
	}
	if (game->GetKey(VK_S).bPressed) {
		UserChoice = (UserChoice + 1) % MAX_OPT;
		UpdateUserChoice();
	}

	return 1;
}
bool StateChoosePlayMode::OnStateEnter() {
	this->game = game;
	game->Fill(0, 0, 159, 95, L' ', BG_COLOR);

	UpdatePointerCoord();
	DrawPointer();
	DrawTitle();
	DrawText_();

	return true;
}
bool StateChoosePlayMode::OnStateExit() {
	return 1;
}

void StateChoosePlayMode::ChangeStateAnimation() {
	static const int _tm = 12;
	static const int step = 2;
	
	game->Fill(0, 0, 159, 95, L' ', BG_COLOR);

	int x = -40;
	int y = BORDER_COORD_LIST[UserChoice].Y - 24;
	int dummy = 0;
	for (int i = 0; i < 200; ) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));
		game->Fill(x + i, y, x + i + 21, y + 33, L' ', BG_COLOR);
		
		OpenLand();
		if (++dummy & 1) {
			i += step;
			DrawLoadingState1(x + i, y);
		}
		else {
			i += 4*step;
			DrawLoadingState2(x + i, y);
		}
		game->ConsOutput();
	}
}
// ================ CHỌN CHẾ ĐỘ CHƠI ================
void StateChoosePlayMode::DrawLoadingState(const int& x, const int& y) {
	static const vector<pair<short, short>> COLOR_LIST = {
		{FG_BLACK, BG_BLACK},// viền
		{FG_DARK_YELLOW, BG_DARK_YELLOW},// túi
		{FG_YELLOW, BG_YELLOW},// túi
		{FG_DARK_GREY, BG_DARK_GREY},// bụng
		{FG_WHITE, BG_WHITE},// bụng_mắt
		{FG_CYAN, BG_CYAN},// bụng
		{FG_DARK_BLUE, BG_DARK_BLUE},// lông
		{FG_BLUE, BG_BLUE},// lông
	};
	int dummy = 0;

// viền
border: {
	game->DrawLine(x + 1, y + 17, x + 1, y + 23, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 2, y + 15, x + 2, y + 16, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 3, y + 14, x + 4, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 5, y + 13, x + 6, y + 12, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 7, y + 12, x + 9, y + 12, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 8, y + 14, x + 9, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 8, y + 16, x + 8, y + 17, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 9, y + 16, x + 10, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 9, y + 16, x + 10, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 11, y + 15, x + 11, y + 18, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 10, y + 19, x + 9, y + 20, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 9, y + 21, x + 8, y + 22, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 8, y + 23, x + 8, y + 24, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 7, y + 24, x + 6, y + 25, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 5, y + 25, x + 4, y + 25, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 2, y + 24, x + 3, y + 25, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 10, y + 13, x + 11, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 11, y + 12, x + 12, y + 11, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 12, y + 10, x + 13, y + 9, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 12, y + 10, x + 13, y + 9, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 14, y + 8, x + 15, y + 8, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 14, y + 1, x + 15, y + 1, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 14, y + 2, x + 14, y + 7, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 16, y + 2, x + 16, y + 3, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 17, y + 4, x + 17, y + 5, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 18, y + 6, x + 18, y + 7, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 18, y + 8, x + 22, y + 8, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 20, y + 2, x + 20, y + 7, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 20, y + 1, x + 21, y + 2, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 22, y + 3, x + 22, y + 4, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 23, y + 5, x + 23, y + 6, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 24, y + 7, x + 25, y + 9, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 26, y + 10, x + 26, y + 11, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 27, y + 12, x + 27, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 28, y + 14, x + 28, y + 17, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 28, y + 14, x + 28, y + 17, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 17, y + 12, x + 18, y + 12, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 24, y + 12, x + 25, y + 12, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 19, y + 13, x + 19, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 26, y + 13, x + 26, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 22, y + 15, x + 23, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 18, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 25, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 29, y + 18, x + 29, y + 26, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 28, y + 27, x + 28, y + 28, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 26, y + 29, x + 27, y + 29, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 24, y + 30, x + 25, y + 30, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 21, y + 31, x + 23, y + 31, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 21, y + 31, x + 23, y + 31, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 20, y + 31, x + 20, y + 33, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 19, y + 32, x + 19, y + 33, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 16, y + 33, x + 17, y + 33, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 17, y + 32, x + 18, y + 33, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 14, y + 32, x + 15, y + 32, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 10, y + 28, x + 13, y + 31, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 8, y + 30, x + 9, y + 29, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 7, y + 31, x + 7, y + 32, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 8, y + 33, x + 10, y + 33, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 11, y + 32, x + 12, y + 32, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 9, y + 25, x + 9, y + 27, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 12, y + 14, x + 12, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 13, y + 15, x + 15, y + 17, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 12, y + 16, x + 14, y + 18, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 14, y + 19, x + 14, y + 20, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 13, y + 21, x + 13, y + 22, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 14, y + 22, x + 15, y + 23, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 15, y + 22, x + 16, y + 21, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 15, y + 18, x + 17, y + 20, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 14, y + 24, x + 14, y + 26, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 15, y + 27, x + 16, y + 27, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 17, y + 28, x + 18, y + 28, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 19, y + 29, x + 20, y + 30, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 18, y + 19, x + 21, y + 19, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 22, y + 18, x + 25, y + 18, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 26, y + 19, x + 27, y + 19, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 28, y + 20, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 20, y + 23, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 24, y + 23, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 28, y + 23, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 18, y + 23, x + 19, y + 22, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 22, y + 23, x + 23, y + 22, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 26, y + 23, x + 27, y + 22, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	}
// túi
bag: {
	dummy++;
	game->DrawLine(x + 2, y + 19, x + 2, y + 23, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 3, y + 21, x + 3, y + 22, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 7, y + 22, x + 7, y + 23, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 3, y + 23, x + 6, y + 24, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	
	dummy++;
	game->Fill(x + 3, y + 15, x + 7, y + 16, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 2, y + 17, x + 7, y + 18, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 3, y + 19, x + 8, y + 20, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 4, y + 21, x + 6, y + 22, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 9, y + 17, x + 10, y + 18, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 13, y + 16, x + 14, y + 17, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 10, y + 14, x + 11, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 6, y + 13, x + 9, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 4, y + 14, x + 7, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 8, y + 15, x + 9, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 7, y + 21, x + 8, y + 21, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 8, y + 18, x + 9, y + 19, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 10, y + 16, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	}
// bụng
belly_n_eye: {
	dummy++;
	game->DrawLine(x + 17, y + 27, x + 18, y + 27, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 19, y + 28, x + 20, y + 29, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 21, y + 29, x + 23, y + 30, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 24, y + 28, x + 25, y + 29, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 26, y + 27, x + 27, y + 28, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 28, y + 26, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	
	dummy++;
	game->Fill(x + 15, y + 24, x + 27, y + 26, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 20, y + 27, x + 23, y + 28, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 22, y + 19, x + 25, y + 20, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 16, y + 22, x + 17, y + 23, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 24, y + 27, x + 25, y + 27, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 17, y + 21, x + 18, y + 21, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 18, y + 20, x + 21, y + 20, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 20, y + 21, x + 22, y + 21, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 21, y + 22, x + 21, y + 23, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 24, y + 21, x + 26, y + 21, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 25, y + 22, x + 25, y + 23, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 26, y + 20, x + 27, y + 20, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 28, y + 24, x + 28, y + 25, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 19, y + 27, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 28, y + 21, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 19, y + 23, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 23, y + 23, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 27, y + 23, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	
	game->DrawLine(x + 17, y + 13, x + 18, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 17, y + 15, x + 18, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 24, y + 15, x + 25, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 24, y + 13, x + 25, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 17, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 24, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	
	dummy++;
	game->Draw(x + 20, y + 22, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 24, y + 22, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 28, y + 22, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 18, y + 22, x + 19, y + 21, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 22, y + 22, x + 23, y + 21, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 26, y + 22, x + 27, y + 21, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	}
// lông
fur: {
	dummy++;
	game->DrawLine(x + 8, y + 31, x + 10, y + 29, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 8, y + 32, x + 10, y + 30, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 15, y + 2, x + 15, y + 7, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 21, y + 3, x + 21, y + 6, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 21, y + 7, x + 22, y + 7, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 14, y + 9, x + 15, y + 9, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 12, y + 12, x + 13, y + 13, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 13, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 18, y + 32, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 11, y + 28, x + 14, y + 31, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 12, y + 28, x + 16, y + 32, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 13, y + 10, x + 14, y + 11, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 9, y + 22, x + 11, y + 22, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 11, y + 19, x + 12, y + 19, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 12, y + 17, x + 12, y + 18, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 10, y + 20, x + 11, y + 21, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 9, y + 23, x + 10, y + 24, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 10, y + 25, x + 11, y + 27, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 15, y + 19, x + 14, y + 21, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	
	dummy++;
	game->DrawLine(x + 12, y + 31, x + 10, y + 32, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 9, y + 32, x + 11, y + 30, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 15, y + 21, x + 17, y + 19, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 16, y + 6, x + 17, y + 8, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 15, y + 10, x + 25, y + 11, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 20, y + 12, x + 21, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 22, y + 12, x + 23, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 14, y + 12, x + 16, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 16, y + 16, x + 21, y + 18, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 22, y + 16, x + 25, y + 17, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 26, y + 16, x + 27, y + 18, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 11, y + 23, x + 13, y + 24, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 12, y + 25, x + 13, y + 27, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 14, y + 28, x + 16, y + 29, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 16, y + 30, x + 19, y + 31, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 16, y + 4, x + 16, y + 5, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 22, y + 5, x + 22, y + 6, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 23, y + 7, x + 23, y + 8, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 16, y + 9, x + 24, y + 9, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 27, y + 14, x + 27, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Fill(x + 28, y + 18, x + 28, y + 19, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 13, y + 18, x + 13, y + 20, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 12, y + 20, x + 12, y + 22, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 13, y + 28, x + 14, y + 27, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 17, y + 29, x + 18, y + 29, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 15, y + 30, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 15, y + 16, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 19, y + 12, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 26, y + 12, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 14, y + 23, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	}
}
void StateChoosePlayMode::DrawLoadingState1(const int& x, const int& y) {
	DrawLoadingState(x, y);

	// chân trái
	game->DrawLine(x + 21, y + 33, x + 23, y + 33, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 24, y + 32, x + 25, y + 32, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 26, y + 31, x + 27, y + 30, 9608, FG_BLACK + BG_BLACK);

	game->DrawLine(x + 21, y + 32, x + 23, y + 32, 9608, FG_BLUE + BG_BLUE);
	game->DrawLine(x + 24, y + 31, x + 25, y + 31, 9608, FG_BLUE + BG_BLUE);
	game->Draw(x + 26, y + 30, 9608, FG_BLUE + BG_BLUE);
}
void StateChoosePlayMode::DrawLoadingState2(const int& x, const int& y) {
	DrawLoadingState(x, y);

	// chân trái
	game->DrawLine(x + 23, y + 32, x + 24, y + 33, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 25, y + 32, x + 25, y + 33, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 28, y + 29, x + 28, y + 31, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x + 27, y + 32, x + 28, y + 33, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 26, y + 33, 9608, FG_BLACK + BG_BLACK);

	game->DrawLine(x + 24, y + 31, x + 24, y + 32, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->DrawLine(x + 25, y + 31, x + 26, y + 32, 9608, FG_DARK_BLUE + BG_DARK_BLUE);

	game->Fill(x + 26, y + 30, x + 27, y + 31, 9608, FG_BLUE + BG_BLUE);
}
void StateChoosePlayMode::OpenLand() {
	game->DrawLine(0, BORDER_COORD_LIST[UserChoice].Y + 1, 159, 
		BORDER_COORD_LIST[UserChoice].Y + 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(0, BORDER_COORD_LIST[UserChoice].Y + 11, 159,
		BORDER_COORD_LIST[UserChoice].Y + 11, 9608, FG_BLACK + BG_BLACK);

	game->DrawLine(0, BORDER_COORD_LIST[UserChoice].Y + 2, 159,
		BORDER_COORD_LIST[UserChoice].Y + 2, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->DrawLine(0, BORDER_COORD_LIST[UserChoice].Y + 10, 159,
		BORDER_COORD_LIST[UserChoice].Y + 10, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	game->Fill(0, BORDER_COORD_LIST[UserChoice].Y + 3, 159,
		BORDER_COORD_LIST[UserChoice].Y + 9, L' ', BG_YELLOW);
}

void StateChoosePlayMode::UpdatePointerCoord() {
	C_Pointer.X = 13;
	C_Pointer.Y = BORDER_COORD_LIST[UserChoice].Y;
}
void StateChoosePlayMode::DrawPointer() {
border: {
	game->DrawLine(C_Pointer.X + 1, C_Pointer.Y + 4, C_Pointer.X + 5, C_Pointer.Y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(C_Pointer.X + 1, C_Pointer.Y + 8, C_Pointer.X + 5, C_Pointer.Y + 8, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(C_Pointer.X + 1, C_Pointer.Y + 5, C_Pointer.X + 1, C_Pointer.Y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(C_Pointer.X + 6, C_Pointer.Y + 1, C_Pointer.X + 6, C_Pointer.Y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(C_Pointer.X + 6, C_Pointer.Y + 8, C_Pointer.X + 6, C_Pointer.Y + 11, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(C_Pointer.X + 7, C_Pointer.Y + 2, C_Pointer.X + 11, C_Pointer.Y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(C_Pointer.X + 7, C_Pointer.Y + 10, C_Pointer.X + 10, C_Pointer.Y + 7, 9608, FG_BLACK + BG_BLACK);
	}
color: {
	game->DrawLine(C_Pointer.X + 2, C_Pointer.Y + 5, C_Pointer.X + 6, C_Pointer.Y + 5, 9608, FG_RED + BG_RED);
	game->DrawLine(C_Pointer.X + 7, C_Pointer.Y + 3, C_Pointer.X + 10, C_Pointer.Y + 6, 9608, FG_RED + BG_RED);
	
	game->DrawLine(C_Pointer.X + 7, C_Pointer.Y + 4, C_Pointer.X + 7, C_Pointer.Y + 9, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(C_Pointer.X + 8, C_Pointer.Y + 5, C_Pointer.X + 8, C_Pointer.Y + 8, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(C_Pointer.X + 9, C_Pointer.Y + 6, C_Pointer.X + 9, C_Pointer.Y + 7, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(C_Pointer.X + 2, C_Pointer.Y + 6, C_Pointer.X + 6, C_Pointer.Y + 7, 9608, FG_DARK_RED + BG_DARK_RED);
	}
}
void StateChoosePlayMode::ClearPointer() {
	game->Fill(C_Pointer.X + 1, C_Pointer.Y + 1, C_Pointer.X + 11, C_Pointer.Y + 11, L' ', BG_COLOR);
}

void StateChoosePlayMode::DrawTextBorder(const int& x, const int& y, const short& bg) {
border: {
	game->Fill(x + 1, y + 1, x + 2, y + 11, L' ', BG_BLACK);
	game->Fill(x + 99, y + 1, x + 100, y + 11, L' ', BG_BLACK);
	game->DrawLine(x + 3, y + 1, x + 98, y + 1, L' ', BG_BLACK);
	game->DrawLine(x + 3, y + 11, x + 98, y + 11, L' ', BG_BLACK);
	}
color: {
	game->Fill(x + 3, y + 2, x + 98, y + 10, L' ', bg);
	}
}
void StateChoosePlayMode::DrawText_CASUAL() {
	static const int SelfIndex = 0;
	static const wstring SelfText = L"CASUAL";

	short fg = FG_GREY;
	short bg = BG_DARK_GREY;

	if (UserChoice == SelfIndex) {
		fg = FG_BLACK;
		bg = BG_YELLOW;
	}

	DrawTextBorder(BORDER_COORD_LIST[SelfIndex].X, BORDER_COORD_LIST[SelfIndex].Y, bg);
	string2Pixel(SelfText, TEXT_COORD_LIST[SelfIndex].X, TEXT_COORD_LIST[SelfIndex].Y,
		fg, bg);
}
void StateChoosePlayMode::DrawText_DEADLINE() {
	static const int SelfIndex = 1;
	static const wstring SelfText = L"DEADLINE";

	short fg = FG_GREY;
	short bg = BG_DARK_GREY;

	if (UserChoice == SelfIndex) {
		fg = FG_BLACK;
		bg = BG_YELLOW;
	}

	DrawTextBorder(BORDER_COORD_LIST[SelfIndex].X, BORDER_COORD_LIST[SelfIndex].Y, bg);
	string2Pixel(SelfText, TEXT_COORD_LIST[SelfIndex].X, TEXT_COORD_LIST[SelfIndex].Y,
		fg, bg);
}
void StateChoosePlayMode::DrawText_ENDLESS() {
	static const int SelfIndex = 2;
	static const wstring SelfText = L"ENDLESS";

	short fg = FG_GREY;
	short bg = BG_DARK_GREY;

	if (UserChoice == SelfIndex) {
		fg = FG_BLACK;
		bg = BG_YELLOW;
	}

	DrawTextBorder(BORDER_COORD_LIST[SelfIndex].X, BORDER_COORD_LIST[SelfIndex].Y, bg);
	string2Pixel(SelfText, TEXT_COORD_LIST[SelfIndex].X, TEXT_COORD_LIST[SelfIndex].Y,
		fg, bg);
}
void StateChoosePlayMode::DrawText_VERSUS() {
	static const int SelfIndex = 3;
	static const wstring SelfText = L"VERSUS";

	short fg = FG_GREY;
	short bg = BG_DARK_GREY;

	if (UserChoice == SelfIndex) {
		fg = FG_BLACK;
		bg = BG_YELLOW;
	}

	DrawTextBorder(BORDER_COORD_LIST[SelfIndex].X, BORDER_COORD_LIST[SelfIndex].Y, bg);
	string2Pixel(SelfText, TEXT_COORD_LIST[SelfIndex].X, TEXT_COORD_LIST[SelfIndex].Y,
		fg, bg);
}
void StateChoosePlayMode::DrawText_() {
	DrawText_CASUAL();
	DrawText_DEADLINE();
	DrawText_ENDLESS();
	DrawText_VERSUS();
}

void StateChoosePlayMode::DrawTitleBorder() {
	static const vector<pair<short, short>> COLOR_LIST = {
		{FG_BLACK, BG_BLACK},// viền
		{FG_DARK_MAGENTA, BG_DARK_MAGENTA},// layer 1
		{FG_MAGENTA, BG_MAGENTA},// layer2
		{FG_MAGENTA, BG_MAGENTA},// nền
	};
	static const int x = 23;
	static const int y = 0;

	int dummy = 0;
border: {
	game->DrawLine(x + 1, y + 3, x + 1, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 2, y + 15, x + 3, y + 16, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 3, y + 1, x + 112, y + 1, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 4, y + 17, x + 111, y + 17, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 114, y + 3, x + 114, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 112, y + 16, x + 113, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 2, y + 2, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 113, y + 2, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	}
layer1: {
	++dummy;
	game->DrawLine(x + 2, y + 3, x + 2, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 3, y + 2, x + 112, y + 2, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 4, y + 16, x + 111, y + 16, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 113, y + 3, x + 113, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 3, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->Draw(x + 112, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	}
layer2: {
	++dummy;
	game->DrawLine(x + 3, y + 3, x + 112, y + 3, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 4, y + 15, x + 111, y + 15, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 3, y + 4, x + 3, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	game->DrawLine(x + 112, y + 4, x + 112, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	}
color: {
	++dummy;
	game->Fill(x + 4, y + 4, x + 111, y + 14, 9608, COLOR_LIST[dummy].first + COLOR_LIST[dummy].second);
	}
}
void StateChoosePlayMode::DrawTitle() {
	static const wstring TITLE = L"SELECT MODE";
	static const int x = 52;
	static const int y = 0 + 8;

	DrawTitleBorder();
	string2Pixel(TITLE, x, y, FG_BLACK, BG_MAGENTA);
}

void StateChoosePlayMode::UpdateUserChoice() {
	ClearPointer();
	UpdatePointerCoord();
	DrawPointer();
	DrawText_();
}
