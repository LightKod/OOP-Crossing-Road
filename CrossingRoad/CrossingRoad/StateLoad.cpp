#include "StateLoad.h"
#include "StateMenu.h"
#include "StatePlay.h"

#define MAX_OPTION 4

const vector<wstring> StateLoad::S_PATH_NAME = { L"A",L"B",L"C",L"D" };

const int StateLoad::S_MAX_DATA_LINE = 4;

const int	StateLoad::m_s_X0 = 20;
const int	StateLoad::m_s_X1 = 140;
const int	StateLoad::m_s_Y0 = 8;
const int	StateLoad::m_s_Y1 = 88;
const int	StateLoad::m_s_OFFSET_X = 10;

const COORD StateLoad::m_s_LINE_1{ m_s_X0 + m_s_OFFSET_X + 12, 34 };
const COORD StateLoad::m_s_LINE_2{ m_s_X0 + m_s_OFFSET_X + 12, 46 };
const COORD StateLoad::m_s_LINE_3{ m_s_X0 + m_s_OFFSET_X + 12, 58 };
const COORD StateLoad::m_s_LINE_4{ m_s_X0 + m_s_OFFSET_X + 12, 70 };

bool StateLoad::Update(float fElapsedTime) {
	// Xử lý load data
	if (game->GetKey(VK_SPACE).bPressed) {
		LoadingThread();

		// change state
		game->SetState(new StatePlay(game, S_PATH_NAME[m_OptionIdx]));

		return 1;
	}

	// Xử lý quay về main menu
	if (game->GetKey(VK_ESCAPE).bPressed) {
		game->SetState(new StateMenu(game));
		return true;
	}

	// Xử lý tương tác với người dùng
	if (game->GetKey(VK_W).bPressed) {
		m_OptionIdx = (m_OptionIdx - 1 + MAX_OPTION) % MAX_OPTION;

		// Xử lý đồ họa load screen
		UpdateArrowCoord();
		this->DrawLoadingScreen();

		return 1;
	}
	else if (game->GetKey(VK_S).bPressed) {
		m_OptionIdx = (m_OptionIdx + 1 + MAX_OPTION) % MAX_OPTION;

		// Xử lý đồ họa load screen
		UpdateArrowCoord();
		this->DrawLoadingScreen();

		return 1;
	}

	return true;
}
bool StateLoad::OnStateEnter() {
	this->game = game;

	// clear screen
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);

	// Get saved data
	GetDataRecord();
	ModifyDataRecord();

	SetArrowCoord(m_s_LINE_1);
	this->DrawLoadingScreen();

	return true;
}
bool StateLoad::OnStateExit() {
	return 0;
}


void StateLoad::DrawLoadingScreen() {
	// Tô màu nền
	LS_FillBackground();

	// Vẽ viền
	LS_DrawBorder();

	// Vẽ title
	DrawTitle();

	// Trang trí
	UpdateCheckbox();
	LS_DecorateScreen();

	// Hiển thị mũi tên (pointer)
	DrawArrow();

	// Hiển thị dữ liệu đã lưu
	ShowDataRecord();
}

void StateLoad::LoadingThread() {
	// Animation
	MoveArrow(-4);
	LoadingAnimation();
}
void StateLoad::LoadingAnimation() {
	int des_X = m_ArrowCoord.X;
	int speed = 10;

	DrawLoadingScreen();
	game->ConsOutput();
	std::this_thread::sleep_for(std::chrono::milliseconds(int(24)));

	while (des_X < m_s_X1) {
		game->DrawLine(m_ArrowCoord.X, m_ArrowCoord.Y, des_X,
			m_ArrowCoord.Y, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
		game->ConsOutput();

		des_X += speed++;

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}


void StateLoad::UpdateArrowCoord() {
	switch (m_OptionIdx) {
	case 0: SetArrowCoord(m_s_LINE_1);
		break;
	case 1: SetArrowCoord(m_s_LINE_2);
		break;
	case 2: SetArrowCoord(m_s_LINE_3);
		break;
	case 3: SetArrowCoord(m_s_LINE_4);
		break;
	default:SetArrowCoord(m_s_LINE_1);
		break;
	}
}
void StateLoad::SetArrowCoord(const COORD& _c) {
	m_ArrowCoord.X = _c.X - 2;
	m_ArrowCoord.Y = _c.Y - 2;
}
void StateLoad::MoveArrow(const int& n) {
	m_ArrowCoord.X -= n;
	m_ArrowCoord.Y -= n;
}

// Tô màu nền cho screen loadgame
void StateLoad::LS_FillBackground() {
	// Phía trên đến hết vòng tròn
	game->Fill(m_s_X0 + m_s_OFFSET_X + 21, m_s_Y0 - 3, m_s_X1 + m_s_OFFSET_X - 36, m_s_Y0 - 2, 9608, FG_GREY + BG_GREY);
	game->Fill(m_s_X0 + m_s_OFFSET_X + 1, m_s_Y0 - 1, m_s_X1 + m_s_OFFSET_X - 11, m_s_Y0, 9608, FG_GREY + BG_GREY);
	game->Fill(m_s_X0 + m_s_OFFSET_X + 1, m_s_Y0 + 1, m_s_X1 + m_s_OFFSET_X - 2, m_s_Y0 + 2, 9608, FG_GREY + BG_GREY);
	game->Fill(m_s_X0 + m_s_OFFSET_X + 1, m_s_Y0 + 3, m_s_X1 + m_s_OFFSET_X - 4, m_s_Y0 + 8, 9608, FG_GREY + BG_GREY);
	game->Fill(m_s_X0 + m_s_OFFSET_X + 1, m_s_Y0 + 9, m_s_X1 + m_s_OFFSET_X - 2, m_s_Y0 + 9, 9608, FG_GREY + BG_GREY);

	game->Fill(m_s_X1 + m_s_OFFSET_X - 2, m_s_Y0 + 2, m_s_X1 + m_s_OFFSET_X + 3, m_s_Y0 + 3, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Fill(m_s_X1 + m_s_OFFSET_X - 3, m_s_Y0 + 4, m_s_X1 + m_s_OFFSET_X + 4, m_s_Y0 + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Fill(m_s_X1 + m_s_OFFSET_X - 1, m_s_Y0 + 8, m_s_X1 + m_s_OFFSET_X + 3, m_s_Y0 + 9, 9608, FG_DARK_GREY + BG_DARK_GREY);


	// Phần thân đến vết rách
	game->Fill(m_s_X0 + m_s_OFFSET_X + 1, m_s_Y0 + 10, m_s_X1 + m_s_OFFSET_X - 5, m_s_Y0 + 12, 9608, FG_GREY + BG_GREY);
	game->Fill(m_s_X0 + m_s_OFFSET_X - 1, m_s_Y0 + 13, m_s_X1 + m_s_OFFSET_X - 5, m_s_Y0 + 34, 9608, FG_GREY + BG_GREY);
	game->Fill(m_s_X0 + m_s_OFFSET_X - 3, m_s_Y0 + 35, m_s_X1 + m_s_OFFSET_X - 5, m_s_Y0 + 62, 9608, FG_GREY + BG_GREY);
	game->Fill(m_s_X0 + m_s_OFFSET_X - 5, m_s_Y0 + 63, m_s_X1 + m_s_OFFSET_X - 7, m_s_Y0 + 70, 9608, FG_GREY + BG_GREY);

	// Bên trái của vết rách
	game->Fill(m_s_X0 + m_s_OFFSET_X - 4, m_s_Y0 + 71, m_s_X1 + m_s_OFFSET_X - 26, m_s_Y0 + 73, 9608, FG_GREY + BG_GREY);
	game->Fill(m_s_X0 + m_s_OFFSET_X - 4, m_s_Y0 + 74, m_s_X1 + m_s_OFFSET_X - 28, m_s_Y0 + 77, 9608, FG_GREY + BG_GREY);
	game->Fill(m_s_X0 + m_s_OFFSET_X + 31, m_s_Y0 + 78, m_s_X1 + m_s_OFFSET_X - 30, m_s_Y0 + 79, 9608, FG_GREY + BG_GREY);

	// Bên phải của vết rách
	game->Fill(m_s_X1 + m_s_OFFSET_X - 22, m_s_Y0 + 71, m_s_X1 + m_s_OFFSET_X - 8, m_s_Y0 + 76, 9608, FG_GREY + BG_GREY);
	game->Fill(m_s_X1 + m_s_OFFSET_X - 24, m_s_Y0 + 77, m_s_X1 + m_s_OFFSET_X - 9, m_s_Y0 + 81, 9608, FG_GREY + BG_GREY);
}
// Vẽ viền cho screen loadgame
void StateLoad::LS_DrawBorder() {
	// Vẽ viền trên 
	game->DrawLine(m_s_X0 + m_s_OFFSET_X, m_s_Y0 - 1, m_s_X0 + m_s_OFFSET_X + 8, m_s_Y0 - 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(m_s_X0 + m_s_OFFSET_X + 8, m_s_Y0 - 2, m_s_X0 + m_s_OFFSET_X + 20, m_s_Y0 - 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(m_s_X0 + m_s_OFFSET_X + 20, m_s_Y0 - 3, m_s_X0 + m_s_OFFSET_X + 30, m_s_Y0 - 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(m_s_X0 + m_s_OFFSET_X + 30, m_s_Y0 - 4, m_s_X0 + m_s_OFFSET_X + 65, m_s_Y0 - 4, 9608, FG_BLACK + BG_BLACK);// Giữa
	game->DrawLine(m_s_X0 + m_s_OFFSET_X + 65, m_s_Y0 - 3, m_s_X0 + m_s_OFFSET_X + 85, m_s_Y0 - 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(m_s_X0 + m_s_OFFSET_X + 85, m_s_Y0 - 2, m_s_X0 + m_s_OFFSET_X + 100, m_s_Y0 - 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(m_s_X0 + m_s_OFFSET_X + 100, m_s_Y0 - 1, m_s_X0 + m_s_OFFSET_X + 110, m_s_Y0 - 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(m_s_X0 + m_s_OFFSET_X + 110, m_s_Y0, m_s_X0 + m_s_OFFSET_X + 120, m_s_Y0, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(m_s_X0 + m_s_OFFSET_X + 119, m_s_Y0 + 1, m_s_X0 + m_s_OFFSET_X + 122, m_s_Y0 + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(m_s_X0 + m_s_OFFSET_X + 123, m_s_Y0 + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(m_s_X0 + m_s_OFFSET_X + 124, m_s_Y0 + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(m_s_X0 + m_s_OFFSET_X + 125, m_s_Y0 + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(m_s_X0 + m_s_OFFSET_X + 125, m_s_Y0 + 5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(m_s_X0 + m_s_OFFSET_X + 125, m_s_Y0 + 6, 9608, FG_BLACK + BG_BLACK);
	game->Draw(m_s_X0 + m_s_OFFSET_X + 125, m_s_Y0 + 7, 9608, FG_BLACK + BG_BLACK);
	game->Draw(m_s_X0 + m_s_OFFSET_X + 124, m_s_Y0 + 8, 9608, FG_BLACK + BG_BLACK);
	game->Draw(m_s_X0 + m_s_OFFSET_X + 123, m_s_Y0 + 9, 9608, FG_BLACK + BG_BLACK);

	game->Draw(m_s_X0 + m_s_OFFSET_X + 119, m_s_Y0 + 9, 9608, FG_BLACK + BG_BLACK);
	game->Draw(m_s_X0 + m_s_OFFSET_X + 118, m_s_Y0 + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(m_s_X0 + m_s_OFFSET_X + 117, m_s_Y0 + 8, m_s_X0 + m_s_OFFSET_X + 118, m_s_Y0 + 8, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(m_s_X0 + m_s_OFFSET_X + 117, m_s_Y0 + 10, m_s_X0 + m_s_OFFSET_X + 122, m_s_Y0 + 10, 9608, FG_BLACK + BG_BLACK);

	game->Draw(m_s_X0 + m_s_OFFSET_X + 118, m_s_Y0 + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(m_s_X0 + m_s_OFFSET_X + 117, m_s_Y0 + 3, 9608, FG_BLACK + BG_BLACK);

	// Vẽ viền phải
	int i = 0;
	for (; i < 45; i++) game->Draw(m_s_X0 + m_s_OFFSET_X + 116, m_s_Y0 + 4 + i, 9608, FG_BLACK + BG_BLACK);
	for (i--; i < 60; i++) game->Draw(m_s_X0 + m_s_OFFSET_X + 115, m_s_Y0 + 4 + i, 9608, FG_BLACK + BG_BLACK);
	for (i--; i < 65; i++) game->Draw(m_s_X0 + m_s_OFFSET_X + 114, m_s_Y0 + 4 + i, 9608, FG_BLACK + BG_BLACK);
	for (i--; i < 70; i++) game->Draw(m_s_X0 + m_s_OFFSET_X + 113, m_s_Y0 + 4 + i, 9608, FG_BLACK + BG_BLACK);
	for (i--; i < 77; i++) game->Draw(m_s_X0 + m_s_OFFSET_X + 112, m_s_Y0 + 4 + i, 9608, FG_BLACK + BG_BLACK);


	// Vẽ viền dưới 
	game->DrawLine(m_s_X1 + m_s_OFFSET_X - 15, m_s_Y1 + 1, m_s_X1 + m_s_OFFSET_X - 8, m_s_Y1 + 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(m_s_X1 + m_s_OFFSET_X - 25, m_s_Y1 + 2, m_s_X1 + m_s_OFFSET_X - 15, m_s_Y1 + 2, 9608, FG_BLACK + BG_BLACK);

	i = 0;
	for (; i < 3; i++) game->Draw(m_s_X1 + m_s_OFFSET_X - 25, m_s_Y1 + 1 - i, 9608, FG_BLACK + BG_BLACK);
	for (--i; i < 6; i++) game->Draw(m_s_X1 + m_s_OFFSET_X - 24, m_s_Y1 + 1 - i, 9608, FG_BLACK + BG_BLACK);
	for (--i; i < 9; i++) game->Draw(m_s_X1 + m_s_OFFSET_X - 23, m_s_Y1 + 1 - i, 9608, FG_BLACK + BG_BLACK);
	for (--i; i < 11; i++) game->Draw(m_s_X1 + m_s_OFFSET_X - 22, m_s_Y1 + 1 - i, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(m_s_X1 + m_s_OFFSET_X - 24, m_s_Y1 - 10, m_s_X1 + m_s_OFFSET_X - 22, m_s_Y1 - 10, 9608, FG_BLACK + BG_BLACK);

	i = 0;
	for (i--; i < 1; i++) game->Draw(m_s_X1 + m_s_OFFSET_X - 24, m_s_Y1 - 9 + i, 9608, FG_BLACK + BG_BLACK);
	for (i--; i < 2; i++) game->Draw(m_s_X1 + m_s_OFFSET_X - 25, m_s_Y1 - 9 + i, 9608, FG_BLACK + BG_BLACK);
	for (i--; i < 3; i++) game->Draw(m_s_X1 + m_s_OFFSET_X - 26, m_s_Y1 - 9 + i, 9608, FG_BLACK + BG_BLACK);
	for (i--; i < 5; i++) game->Draw(m_s_X1 + m_s_OFFSET_X - 27, m_s_Y1 - 9 + i, 9608, FG_BLACK + BG_BLACK);
	for (i--; i < 7; i++) game->Draw(m_s_X1 + m_s_OFFSET_X - 28, m_s_Y1 - 9 + i, 9608, FG_BLACK + BG_BLACK);
	for (i--; i < 9; i++) game->Draw(m_s_X1 + m_s_OFFSET_X - 29, m_s_Y1 - 9 + i, 9608, FG_BLACK + BG_BLACK);
	game->Draw(m_s_X1 + m_s_OFFSET_X - 30, m_s_Y1 - 1, 9608, FG_BLACK + BG_BLACK);

	game->DrawLine(m_s_X1 + m_s_OFFSET_X - 70, m_s_Y1, m_s_X1 + m_s_OFFSET_X - 30, m_s_Y1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(m_s_X1 + m_s_OFFSET_X - 90, m_s_Y1 - 1, m_s_X1 + m_s_OFFSET_X - 70, m_s_Y1 - 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(m_s_X1 + m_s_OFFSET_X - 105, m_s_Y1 - 2, m_s_X1 + m_s_OFFSET_X - 90, m_s_Y1 - 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(m_s_X1 + m_s_OFFSET_X - 125, m_s_Y1 - 3, m_s_X1 + m_s_OFFSET_X - 105, m_s_Y1 - 3, 9608, FG_BLACK + BG_BLACK);

	// Vẽ viền trái
	i = 0;
	for (; i < 16; i++) game->Draw(m_s_X0 + m_s_OFFSET_X - 5, m_s_Y1 - 3 - i, 9608, FG_BLACK + BG_BLACK);
	for (--i; i < 31; i++) game->Draw(m_s_X0 + m_s_OFFSET_X - 4, m_s_Y1 - 3 - i, 9608, FG_BLACK + BG_BLACK);
	for (--i; i < 44; i++) game->Draw(m_s_X0 + m_s_OFFSET_X - 3, m_s_Y1 - 3 - i, 9608, FG_BLACK + BG_BLACK);
	for (--i; i < 56; i++) game->Draw(m_s_X0 + m_s_OFFSET_X - 2, m_s_Y1 - 3 - i, 9608, FG_BLACK + BG_BLACK);
	for (--i; i < 66; i++) game->Draw(m_s_X0 + m_s_OFFSET_X - 1, m_s_Y1 - 3 - i, 9608, FG_BLACK + BG_BLACK);
	for (--i; i < 78; i++) game->Draw(m_s_X0 + m_s_OFFSET_X, m_s_Y1 - 3 - i, 9608, FG_BLACK + BG_BLACK);
}
// Trang trí screen loadgame
void StateLoad::DrawCheckbox(const COORD& _coord,
	const short& fg = FG_DARK_GREY, const short& bg = BG_DARK_GREY)
{
	game->Draw(_coord.X - 1, _coord.Y, 9608, fg + bg);
	game->Draw(_coord.X, _coord.Y - 1, 9608, fg + bg);
	game->Draw(_coord.X, _coord.Y + 1, 9608, fg + bg);
	game->Draw(_coord.X + 1, _coord.Y, 9608, fg + bg);

	game->DrawLine(_coord.X + 3, _coord.Y + 2, _coord.X + 90,
		_coord.Y + 2, 9608, fg + bg);
}
void StateLoad::UpdateCheckbox() {
	UpdateCheckbox1();
	UpdateCheckbox2();
	UpdateCheckbox3();
	UpdateCheckbox4();
}
void StateLoad::UpdateCheckbox1() {
	if (m_OptionIdx == 0)
		DrawCheckbox(m_s_LINE_1, FG_WHITE, BG_WHITE);
	else
		DrawCheckbox(m_s_LINE_1);
}
void StateLoad::UpdateCheckbox2() {
	if (m_OptionIdx == 1)
		DrawCheckbox(m_s_LINE_2, FG_WHITE, BG_WHITE);
	else
		DrawCheckbox(m_s_LINE_2);
}
void StateLoad::UpdateCheckbox3() {
	if (m_OptionIdx == 2)
		DrawCheckbox(m_s_LINE_3, FG_WHITE, BG_WHITE);
	else
		DrawCheckbox(m_s_LINE_3);
}
void StateLoad::UpdateCheckbox4() {
	if (m_OptionIdx == 3)
		DrawCheckbox(m_s_LINE_4, FG_WHITE, BG_WHITE);
	else
		DrawCheckbox(m_s_LINE_4);
}

void StateLoad::DrawArrow() {
	// Vẽ mũi tên
	game->Draw(m_ArrowCoord.X - 1, m_ArrowCoord.Y, 9608, FG_CYAN + BG_CYAN);
	game->Draw(m_ArrowCoord.X, m_ArrowCoord.Y, 9608, FG_DARK_CYAN + BG_DARK_CYAN);// 
	game->Draw(m_ArrowCoord.X, m_ArrowCoord.Y - 1, 9608, FG_CYAN + BG_CYAN);

	game->Draw(m_ArrowCoord.X - 3, m_ArrowCoord.Y - 1, 9608, FG_CYAN + BG_CYAN);
	game->Draw(m_ArrowCoord.X - 2, m_ArrowCoord.Y - 1, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
	game->Draw(m_ArrowCoord.X - 1, m_ArrowCoord.Y - 1, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
	game->Draw(m_ArrowCoord.X - 1, m_ArrowCoord.Y - 2, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
	game->Draw(m_ArrowCoord.X - 1, m_ArrowCoord.Y - 3, 9608, FG_CYAN + BG_CYAN);

	game->Draw(m_ArrowCoord.X - 2, m_ArrowCoord.Y - 2, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(m_ArrowCoord.X - 3, m_ArrowCoord.Y - 3, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(m_ArrowCoord.X - 4, m_ArrowCoord.Y - 4, 9608, FG_DARK_GREY + BG_DARK_GREY);

	game->Draw(m_ArrowCoord.X - 6, m_ArrowCoord.Y - 5, 9608, FG_CYAN + BG_CYAN);
	game->Draw(m_ArrowCoord.X - 5, m_ArrowCoord.Y - 5, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
	game->Draw(m_ArrowCoord.X - 5, m_ArrowCoord.Y - 6, 9608, FG_CYAN + BG_CYAN);

	game->Draw(m_ArrowCoord.X - 7, m_ArrowCoord.Y - 6, 9608, FG_CYAN + BG_CYAN);
	game->Draw(m_ArrowCoord.X - 6, m_ArrowCoord.Y - 6, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
	game->Draw(m_ArrowCoord.X - 6, m_ArrowCoord.Y - 7, 9608, FG_CYAN + BG_CYAN);

	// Hiệu ứng đổ bóng
	game->Draw(m_ArrowCoord.X, m_ArrowCoord.Y + 1, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->Draw(m_ArrowCoord.X - 1, m_ArrowCoord.Y + 1, 9608, FG_DARK_BLUE + BG_DARK_BLUE);

	game->Draw(m_ArrowCoord.X - 2, m_ArrowCoord.Y, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->Draw(m_ArrowCoord.X - 3, m_ArrowCoord.Y, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->Draw(m_ArrowCoord.X - 4, m_ArrowCoord.Y - 1, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->Draw(m_ArrowCoord.X - 2, m_ArrowCoord.Y - 3, 9608, FG_DARK_BLUE + BG_DARK_BLUE);

	game->Draw(m_ArrowCoord.X - 3, m_ArrowCoord.Y - 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(m_ArrowCoord.X - 4, m_ArrowCoord.Y - 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(m_ArrowCoord.X - 5, m_ArrowCoord.Y - 4, 9608, FG_BLACK + BG_BLACK);

	game->Draw(m_ArrowCoord.X - 6, m_ArrowCoord.Y - 4, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->Draw(m_ArrowCoord.X - 7, m_ArrowCoord.Y - 5, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->Draw(m_ArrowCoord.X - 8, m_ArrowCoord.Y - 6, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
	game->Draw(m_ArrowCoord.X - 7, m_ArrowCoord.Y - 7, 9608, FG_DARK_BLUE + BG_DARK_BLUE);
}

void StateLoad::LS_DecorateScreen() {
	// kính lúp góc phải trên
	DrawMagnifyingGlass();

	// Mark X góc phải dưới
	DrawMarkXTreasure();
}
void StateLoad::DrawMagnifyingGlass() {
	const static int _x = m_s_X1 - 23 + m_s_OFFSET_X;
	const static int _y = m_s_Y0 + 4;
	const static int offsetX = 10;
	const static int offsetY = 2;

	/****** Tô nền ******/
	game->Fill(_x + offsetX - 2, _y + offsetY + 2,
		_x + offsetX + 4, _y + offsetY + 8, 9608, FG_CYAN + BG_CYAN);

	/****** Vẽ Viền trong ******/
	// Viền trên
	game->DrawLine(_x + offsetX, _y + offsetY + 1, _x + offsetX + 2, _y + offsetY + 1, 9608, FG_BLUE + BG_BLUE);
	// Viền dưới
	game->DrawLine(_x + offsetX, _y + offsetY + 9, _x + offsetX + 2, _y + offsetY + 9, 9608, FG_BLUE + BG_BLUE);
	// Viền 4 góc chéo
	for (int i = 0; i < 2; i++) {
		game->Draw(_x + offsetX - 1 - i, _y + offsetY + 2 + i, 9608, FG_BLUE + BG_BLUE);
		game->Draw(_x + offsetX + 3 + i, _y + offsetY + 2 + i, 9608, FG_BLUE + BG_BLUE);

		game->Draw(_x + offsetX - 1 - i, _y + offsetY + 8 - i, 9608, FG_BLUE + BG_BLUE);
		game->Draw(_x + offsetX + 3 + i, _y + offsetY + 8 - i, 9608, FG_BLUE + BG_BLUE);
	}
	// 2 viền ngang
	for (int i = 0; i < 3; i++) {
		game->Draw(_x + offsetX - 3, _y + offsetY + 4 + i, 9608, FG_BLUE + BG_BLUE);
		game->Draw(_x + offsetX + 5, _y + offsetY + 4 + i, 9608, FG_BLUE + BG_BLUE);
	}

	/****** Vẽ Viền ngoài ******/
	// Viền trên
	game->DrawLine(_x + offsetX, _y + offsetY, _x + offsetX + 2, _y + offsetY, 9608, FG_RED + BG_RED);

	for (int i = 0; i < 3; i++) {
		game->Draw(_x + offsetX - 1 - i, _y + offsetY + 1 + i, 9608, FG_RED + BG_RED);
		game->Draw(_x + offsetX + 3 + i, _y + offsetY + 1 + i, 9608, FG_DARK_RED + BG_DARK_RED);
	}
	// Viền trái phải
	for (int i = 0; i < 3; i++) {
		game->Draw(_x + offsetX - 4, _y + offsetY + 4 + i, 9608, FG_RED + BG_RED);
		game->Draw(_x + offsetX + 6, _y + offsetY + 4 + i, 9608, FG_DARK_RED + BG_DARK_RED);
	}
	game->Draw(_x + offsetX - 3, _y + offsetY + 7, 9608, FG_RED + BG_RED);
	// Viền dưới
	for (int i = 0; i < 3; i++) {
		game->DrawLine(_x + offsetX - 4 - i, _y + offsetY + 8 + i,
			_x + offsetX - 2 - i, _y + offsetY + 8 + i, 9608, FG_RED + BG_RED);
	}
	game->Draw(_x + offsetX - 5, _y + offsetY + 11, 9608, FG_RED + BG_RED);
	game->Draw(_x + offsetX - 6, _y + offsetY + 11, 9608, FG_RED + BG_RED);

	for (int i = 0; i < 4; i++) {
		game->DrawLine(_x + offsetX - 5 + i, _y + offsetY + 12 - i,
			_x + offsetX - 4 + i, _y + offsetY + 12 - i, 9608, FG_DARK_RED + BG_DARK_RED);
	}
	game->DrawLine(_x + offsetX, _y + offsetY + 10,
		_x + offsetX + 2, _y + offsetY + 10, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + offsetX + 3, _y + offsetY + 9, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + offsetX + 4, _y + offsetY + 8, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + offsetX + 5, _y + offsetY + 7, 9608, FG_DARK_RED + BG_DARK_RED);

	/****** Tạo hiệu ứng ánh sáng ******/
	game->DrawLine(_x + offsetX + 1, _y + offsetY + 3,
		_x + offsetX + 2, _y + offsetY + 3, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + offsetX, _y + offsetY + 4,
		_x + offsetX + 3, _y + offsetY + 4, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + offsetX - 1, _y + offsetY + 5,
		_x + offsetX + 1, _y + offsetY + 5, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(_x + offsetX - 1, _y + offsetY + 6,
		_x + offsetX, _y + offsetY + 6, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + offsetX, _y + offsetY + 7, 9608, FG_WHITE + BG_WHITE);
}
void StateLoad::DrawMarkXTreasure()
{
	const static int _x = m_s_X1 - 29 + m_s_OFFSET_X;
	const static int _y = m_s_Y1 - 10;
	const static int offsetX = 10;
	const static int offsetY = 2;

	// Vẽ viền
	game->DrawLine(_x + offsetX, _y + offsetY, _x + offsetX + 2, _y + offsetY, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + offsetX + 5, _y + offsetY, _x + offsetX + 7, _y + offsetY, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + offsetX + 3, _y + offsetY + 1, _x + offsetX + 4, _y + offsetY + 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + offsetX + 3, _y + offsetY + 5, _x + offsetX + 4, _y + offsetY + 5, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + offsetX, _y + offsetY + 5, _x + offsetX, _y + offsetY + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x + offsetX + 7, _y + offsetY + 5, _x + offsetX + 7, _y + offsetY + 7, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + offsetX, _y + offsetY + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + offsetX + 7, _y + offsetY + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + offsetX + 1, _y + offsetY + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + offsetX + 6, _y + offsetY + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + offsetX + 2, _y + offsetY + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + offsetX + 5, _y + offsetY + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + offsetX + 1, _y + offsetY + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + offsetX + 6, _y + offsetY + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + offsetX + 2, _y + offsetY + 6, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + offsetX + 5, _y + offsetY + 6, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + offsetX + 1, _y + offsetY + 7, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + offsetX + 6, _y + offsetY + 7, 9608, FG_BLACK + BG_BLACK);

	// Tô nền
	game->Draw(_x + offsetX + 1, _y + offsetY + 1, 9608, FG_RED + BG_RED);
	game->Draw(_x + offsetX + 6, _y + offsetY + 1, 9608, FG_RED + BG_RED);
	game->Draw(_x + offsetX + 2, _y + offsetY + 1, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + offsetX + 5, _y + offsetY + 1, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + offsetX + 2, _y + offsetY + 2, 9608, FG_RED + BG_RED);
	game->Draw(_x + offsetX + 5, _y + offsetY + 2, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + offsetX + 3, _y + offsetY + 2, _x + offsetX + 4, _y + offsetY + 2, 9608, FG_DARK_RED + BG_DARK_RED);
	game->DrawLine(_x + offsetX + 3, _y + offsetY + 4, _x + offsetX + 4, _y + offsetY + 4, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + offsetX + 3, _y + offsetY + 3, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + offsetX + 4, _y + offsetY + 3, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + offsetX + 2, _y + offsetY + 4, _x + offsetX + 2, _y + offsetY + 5, 9608, FG_RED + BG_RED);
	game->DrawLine(_x + offsetX + 5, _y + offsetY + 4, _x + offsetX + 5, _y + offsetY + 5, 9608, FG_RED + BG_RED);
	game->Draw(_x + offsetX + 1, _y + offsetY + 5, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + offsetX + 6, _y + offsetY + 5, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + offsetX + 1, _y + offsetY + 6, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + offsetX + 6, _y + offsetY + 6, 9608, FG_DARK_RED + BG_DARK_RED);
}

void StateLoad::DrawTitle() {
	static const int _x = m_s_X0 + m_s_OFFSET_X + 6;
	static const int _y = m_s_Y0 + 2;
	int offsetX = 0;

	// L 
	game->Fill(_x, _y, _x + 9, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 5, _y, _x + 9, _y + 6, 9608, FG_GREY + BG_GREY);
	game->Fill(_x + 1, _y + 1, _x + 3, _y + 1, 9608, FG_WHITE + BG_WHITE);
	game->Fill(_x + 1, _y + 2, _x + 3, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 1, _y + 6, _x + 3, _y + 7, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 1, _y + 8, _x + 8, _y + 9, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 1, _y + 10, _x + 8, _y + 10, 9608, FG_DARK_RED + BG_DARK_RED);

	// O
	game->Fill(_x + 11, _y, _x + 20, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 11, _y, 9608, FG_GREY + BG_GREY);
	game->Draw(_x + 20, _y, 9608, FG_GREY + BG_GREY);
	game->Draw(_x + 20, _y + 11, 9608, FG_GREY + BG_GREY);
	game->Draw(_x + 11, _y + 11, 9608, FG_GREY + BG_GREY);

	game->Fill(_x + 13, _y + 1, _x + 18, _y + 1, 9608, FG_WHITE + BG_WHITE);
	game->Fill(_x + 15, _y + 5, _x + 16, _y + 6, 9608, FG_WHITE + BG_WHITE);

	game->Fill(_x + 12, _y + 2, _x + 19, _y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 12, _y + 2, _x + 13, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 18, _y + 3, _x + 19, _y + 5, 9608, FG_YELLOW + BG_YELLOW);

	game->Fill(_x + 14, _y + 3, _x + 17, _y + 3, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 13, _y + 10, _x + 18, _y + 10, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + 12, _y + 9, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + 19, _y + 9, 9608, FG_DARK_RED + BG_DARK_RED);

	game->Fill(_x + 12, _y + 6, _x + 13, _y + 7, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 18, _y + 6, _x + 19, _y + 7, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 12, _y + 8, _x + 19, _y + 8, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 13, _y + 9, _x + 18, _y + 9, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	// A
	game->Fill(_x + 23 + offsetX, _y, _x + 30 + offsetX, _y, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 23 + offsetX, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 30 + offsetX, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 22 + offsetX, _y + 1, _x + 22 + offsetX, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 31 + offsetX, _y + 1, _x + 31 + offsetX, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 23 + offsetX, _y + 11, _x + 24 + offsetX, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 29 + offsetX, _y + 11, _x + 30 + offsetX, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 25 + offsetX, _y + 9, _x + 25 + offsetX, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 28 + offsetX, _y + 9, _x + 28 + offsetX, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 25 + offsetX, _y + 8, _x + 28 + offsetX, _y + 8, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 25 + offsetX, _y + 4, _x + 28 + offsetX, _y + 4, 9608, FG_BLACK + BG_BLACK);

	game->Fill(_x + 25 + offsetX, _y + 3, _x + 28 + offsetX, _y + 3, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 25 + offsetX, _y + 7, _x + 28 + offsetX, _y + 7, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 23 + offsetX, _y + 10, _x + 24 + offsetX, _y + 10, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 29 + offsetX, _y + 10, _x + 30 + offsetX, _y + 10, 9608, FG_DARK_RED + BG_DARK_RED);

	game->Fill(_x + 23 + offsetX, _y + 2, _x + 30 + offsetX, _y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 23 + offsetX, _y + 5, _x + 30 + offsetX, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 23 + offsetX, _y + 3, _x + 24 + offsetX, _y + 4, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 29 + offsetX, _y + 3, _x + 30 + offsetX, _y + 4, 9608, FG_YELLOW + BG_YELLOW);

	game->Fill(_x + 23 + offsetX, _y + 6, _x + 30 + offsetX, _y + 6, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 23 + offsetX, _y + 7, _x + 24 + offsetX, _y + 9, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 29 + offsetX, _y + 7, _x + 30 + offsetX, _y + 9, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	game->Fill(_x + 24 + offsetX, _y + 1, _x + 29 + offsetX, _y + 1, 9608, FG_WHITE + BG_WHITE);

	// D
	game->Fill(_x + 33, _y, _x + 40, _y, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 33, _y + 11, _x + 40, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 33, _y + 1, _x + 33, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 40, _y + 1, _x + 41, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 40, _y + 10, _x + 41, _y + 10, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 41, _y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 41, _y + 9, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 42, _y + 2, _x + 42, _y + 9, 9608, FG_BLACK + BG_BLACK);

	game->Fill(_x + 36, _y + 4, _x + 38, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 36, _y + 8, _x + 38, _y + 8, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 36, _y + 5, _x + 36, _y + 7, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 38, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 38, _y + 7, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 39, _y + 5, _x + 39, _y + 7, 9608, FG_BLACK + BG_BLACK);

	game->Fill(_x + 34, _y + 10, _x + 39, _y + 10, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + 40, _y + 9, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + 41, _y + 8, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 36, _y + 3, _x + 38, _y + 3, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + 39, _y + 4, 9608, FG_DARK_RED + BG_DARK_RED);

	game->Fill(_x + 34, _y + 2, _x + 40, _y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 34, _y + 3, _x + 35, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 40, _y + 3, _x + 41, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 39, _y + 3, 9608, FG_YELLOW + BG_YELLOW);

	game->Fill(_x + 34, _y + 6, _x + 35, _y + 9, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 36, _y + 9, _x + 39, _y + 9, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 39, _y + 8, _x + 40, _y + 8, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 40, _y + 6, _x + 41, _y + 7, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	game->Fill(_x + 34, _y + 1, _x + 39, _y + 1, 9608, FG_WHITE + BG_WHITE);
	game->Fill(_x + 37, _y + 5, _x + 37, _y + 7, 9608, FG_WHITE + BG_WHITE);
	game->Draw(_x + 38, _y + 6, 9608, FG_WHITE + BG_WHITE);

	// G
	game->Fill(_x + 48, _y, _x + 56, _y, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 48, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 48, _y + 10, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 55, _y + 10, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 55, _y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 55, _y + 6, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 47, _y + 1, _x + 47, _y + 10, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 48, _y + 11, _x + 55, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 56, _y + 6, _x + 56, _y + 10, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 56, _y + 1, _x + 56, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 50, _y + 4, _x + 55, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 50, _y + 5, _x + 50, _y + 8, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 51, _y + 8, _x + 52, _y + 8, 9608, FG_BLACK + BG_BLACK);

	game->Fill(_x + 51, _y + 7, _x + 52, _y + 7, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 50, _y + 3, _x + 55, _y + 3, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 49, _y + 10, _x + 54, _y + 10, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + 48, _y + 9, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + 55, _y + 9, 9608, FG_DARK_RED + BG_DARK_RED);

	game->Fill(_x + 48, _y + 2, _x + 55, _y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 48, _y + 3, _x + 49, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 51, _y + 5, _x + 54, _y + 5, 9608, FG_YELLOW + BG_YELLOW);

	game->Fill(_x + 48, _y + 6, _x + 49, _y + 8, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 49, _y + 9, _x + 54, _y + 9, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 53, _y + 7, _x + 55, _y + 8, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 51, _y + 6, _x + 54, _y + 7, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	game->Fill(_x + 49, _y + 1, _x + 55, _y + 1, 9608, FG_WHITE + BG_WHITE);

	// A
	offsetX += 36;

	game->Fill(_x + 23 + offsetX, _y, _x + 30 + offsetX, _y, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 23 + offsetX, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 30 + offsetX, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 22 + offsetX, _y + 1, _x + 22 + offsetX, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 31 + offsetX, _y + 1, _x + 31 + offsetX, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 23 + offsetX, _y + 11, _x + 24 + offsetX, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 29 + offsetX, _y + 11, _x + 30 + offsetX, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 25 + offsetX, _y + 9, _x + 25 + offsetX, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 28 + offsetX, _y + 9, _x + 28 + offsetX, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 25 + offsetX, _y + 8, _x + 28 + offsetX, _y + 8, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 25 + offsetX, _y + 4, _x + 28 + offsetX, _y + 4, 9608, FG_BLACK + BG_BLACK);

	game->Fill(_x + 25 + offsetX, _y + 3, _x + 28 + offsetX, _y + 3, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 25 + offsetX, _y + 7, _x + 28 + offsetX, _y + 7, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 23 + offsetX, _y + 10, _x + 24 + offsetX, _y + 10, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 29 + offsetX, _y + 10, _x + 30 + offsetX, _y + 10, 9608, FG_DARK_RED + BG_DARK_RED);

	game->Fill(_x + 23 + offsetX, _y + 2, _x + 30 + offsetX, _y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 23 + offsetX, _y + 5, _x + 30 + offsetX, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 23 + offsetX, _y + 3, _x + 24 + offsetX, _y + 4, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 29 + offsetX, _y + 3, _x + 30 + offsetX, _y + 4, 9608, FG_YELLOW + BG_YELLOW);

	game->Fill(_x + 23 + offsetX, _y + 6, _x + 30 + offsetX, _y + 6, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 23 + offsetX, _y + 7, _x + 24 + offsetX, _y + 9, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 29 + offsetX, _y + 7, _x + 30 + offsetX, _y + 9, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	game->Fill(_x + 24 + offsetX, _y + 1, _x + 29 + offsetX, _y + 1, 9608, FG_WHITE + BG_WHITE);

	// M
	game->Fill(_x + 69, _y, _x + 73, _y, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 77, _y, _x + 81, _y, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 73, _y + 1, _x + 74, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 76, _y + 1, _x + 77, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 74, _y + 2, _x + 76, _y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 75, _y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 69, _y + 1, _x + 69, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 81, _y + 1, _x + 81, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 70, _y + 11, _x + 71, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 79, _y + 11, _x + 80, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 72, _y + 9, _x + 72, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 78, _y + 9, _x + 78, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 72, _y + 7, _x + 73, _y + 7, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 72, _y + 8, _x + 74, _y + 8, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 74, _y + 9, _x + 76, _y + 9, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 76, _y + 8, _x + 78, _y + 8, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 77, _y + 7, _x + 78, _y + 7, 9608, FG_BLACK + BG_BLACK);

	game->Fill(_x + 72, _y + 6, _x + 73, _y + 6, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 77, _y + 6, _x + 78, _y + 6, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 70, _y + 10, _x + 71, _y + 10, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 79, _y + 10, _x + 80, _y + 10, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + 74, _y + 7, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + 76, _y + 7, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + 75, _y + 8, 9608, FG_DARK_RED + BG_DARK_RED);

	game->Fill(_x + 70, _y + 2, _x + 73, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 77, _y + 2, _x + 80, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 74, _y + 4, _x + 76, _y + 5, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 74, _y + 3, 9608, FG_YELLOW + BG_YELLOW);
	game->Draw(_x + 76, _y + 3, 9608, FG_YELLOW + BG_YELLOW);

	game->Fill(_x + 70, _y + 6, _x + 71, _y + 9, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 79, _y + 6, _x + 80, _y + 9, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 74, _y + 6, _x + 76, _y + 6, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Draw(_x + 75, _y + 7, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	game->Fill(_x + 70, _y + 1, _x + 72, _y + 1, 9608, FG_WHITE + BG_WHITE);
	game->Fill(_x + 78, _y + 1, _x + 80, _y + 1, 9608, FG_WHITE + BG_WHITE);

	// E
	game->Fill(_x + 84, _y, _x + 92, _y, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 83, _y + 1, _x + 83, _y + 10, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 84, _y + 11, _x + 92, _y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 92, _y + 1, _x + 92, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 92, _y + 7, _x + 92, _y + 10, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 87, _y + 4, _x + 91, _y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 87, _y + 7, _x + 91, _y + 7, 9608, FG_BLACK + BG_BLACK);
	game->Fill(_x + 90, _y + 5, _x + 90, _y + 6, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 84, _y + 1, 9608, FG_BLACK + BG_BLACK);
	game->Draw(_x + 84, _y + 10, 9608, FG_BLACK + BG_BLACK);

	game->Fill(_x + 85, _y + 10, _x + 91, _y + 10, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 87, _y + 6, _x + 89, _y + 6, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Fill(_x + 87, _y + 3, _x + 91, _y + 3, 9608, FG_DARK_RED + BG_DARK_RED);
	game->Draw(_x + 84, _y + 9, 9608, FG_DARK_RED + BG_DARK_RED);

	game->Fill(_x + 84, _y + 2, _x + 91, _y + 2, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 84, _y + 3, _x + 86, _y + 4, 9608, FG_YELLOW + BG_YELLOW);
	game->Fill(_x + 84, _y + 5, _x + 89, _y + 5, 9608, FG_YELLOW + BG_YELLOW);

	game->Fill(_x + 84, _y + 6, _x + 86, _y + 7, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 84, _y + 8, _x + 91, _y + 8, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);
	game->Fill(_x + 85, _y + 9, _x + 91, _y + 9, 9608, FG_DARK_YELLOW + BG_DARK_YELLOW);

	game->Fill(_x + 85, _y + 1, _x + 91, _y + 1, 9608, FG_WHITE + BG_WHITE);

}

void StateLoad::ModifyDataRecord() {
	if (m_Datas.size() <= StateLoad::S_MAX_DATA_LINE)
		return;


	while (m_Datas.size() > StateLoad::S_MAX_DATA_LINE) {
		m_Datas.erase(m_Datas.begin());
	}

	wofstream wOfs(L"data/SAVE_LOAD.txt");
	if (wOfs.is_open()) {
		// write introduction line
		wOfs << L"TEN,LEVEL,SCORE,CHAR_IDX" << endl;
		
		// write real data
		for (int i = 0; i < m_Datas.size(); ++i) {
			wOfs << m_Datas[i].m_Name << L",";
			wOfs << m_Datas[i].m_Level << L",";
			wOfs << m_Datas[i].m_Score << L",";
			wOfs << m_Datas[i].m_CharIdx << endl;;
		}

		wOfs.close();
	}
}
void StateLoad::GetDataRecord() {
	m_Datas.reserve(4);
	wstring tmpName = L"";

	wifstream wIfs(L"data/A.txt");
	getline(wIfs, tmpName);
	m_Datas.emplace_back(Data(tmpName));
	wIfs.close();

	wIfs.open(L"data/B.txt");
	getline(wIfs, tmpName);
	m_Datas.emplace_back(Data(tmpName));
	wIfs.close();

	wIfs.open(L"data/C.txt");
	getline(wIfs, tmpName);
	m_Datas.emplace_back(Data(tmpName));
	wIfs.close();

	wIfs.open(L"data/D.txt");
	getline(wIfs, tmpName);
	m_Datas.emplace_back(Data(tmpName));
	wIfs.close();

}
void StateLoad::ShowDataRecord() {
	switch (m_Datas.size()) {
	case 4:
		UpdateDataLine4();
	case 3:
		UpdateDataLine3();
	case 2:
		UpdateDataLine2();
	case 1:
		UpdateDataLine1();
	}
}


void StateLoad::UpdateDataLine1()
{
	if (m_OptionIdx == 0)
		string2Pixel(m_Datas[0].m_Name,
			m_s_LINE_1.X + 3, m_s_LINE_1.Y - 2, FG_BLACK, BG_GREY);
	else
		string2Pixel(m_Datas[0].m_Name,
			m_s_LINE_1.X + 3, m_s_LINE_1.Y - 2, FG_DARK_GREY, BG_GREY);
}
void StateLoad::UpdateDataLine2()
{
	if (m_OptionIdx == 1)
		string2Pixel(m_Datas[1].m_Name,
			m_s_LINE_2.X + 3, m_s_LINE_2.Y - 2, FG_BLACK, BG_GREY);
	else
		string2Pixel(m_Datas[1].m_Name,
			m_s_LINE_2.X + 3, m_s_LINE_2.Y - 2, FG_DARK_GREY, BG_GREY);
}
void StateLoad::UpdateDataLine3()
{
	if (m_OptionIdx == 2)
		string2Pixel(m_Datas[2].m_Name,
			m_s_LINE_3.X + 3, m_s_LINE_3.Y - 2, FG_BLACK, BG_GREY);
	else
		string2Pixel(m_Datas[2].m_Name,
			m_s_LINE_3.X + 3, m_s_LINE_3.Y - 2, FG_DARK_GREY, BG_GREY);
}
void StateLoad::UpdateDataLine4()
{
	if (m_OptionIdx == 3)
		string2Pixel(m_Datas[3].m_Name,
			m_s_LINE_4.X + 3, m_s_LINE_4.Y - 2, FG_BLACK, BG_GREY);
	else
		string2Pixel(m_Datas[3].m_Name,
			m_s_LINE_4.X + 3, m_s_LINE_4.Y - 2, FG_DARK_GREY, BG_GREY);
}
