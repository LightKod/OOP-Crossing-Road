#include "StateLoad.h"
#define MAX_OPTION 4

const int	StateLoad::m_s_X0		= 20;
const int	StateLoad::m_s_X1		= 140;
const int	StateLoad::m_s_Y0		= 8;
const int	StateLoad::m_s_Y1		= 88;
const int	StateLoad::m_s_OFFSET_X	= 10;

const COORD StateLoad::m_s_LINE_1{ m_s_X0 + m_s_OFFSET_X + 12, m_s_Y1 * 2 / 6 };
const COORD StateLoad::m_s_LINE_2{ m_s_X0 + m_s_OFFSET_X + 12, m_s_Y1 * 3 / 6 };
const COORD StateLoad::m_s_LINE_3{ m_s_X0 + m_s_OFFSET_X + 12, m_s_Y1 * 4 / 6 };
const COORD StateLoad::m_s_LINE_4{ m_s_X0 + m_s_OFFSET_X + 12, m_s_Y1 * 5 / 6 };

bool StateLoad::Update(float fElapsedTime) {
	static int optionIndex = 0;
	/*static float deltaTime = 0;
	static bool down = 0;

	deltaTime += fElapsedTime;
	if (deltaTime > .5f) {
		deltaTime = 0.f;
	}*/

	if (game->GetKey(VK_W).bReleased) {
		optionIndex = (optionIndex - 1 + MAX_OPTION) % MAX_OPTION;
	}
	else if (game->GetKey(VK_S).bReleased) {
		optionIndex = (optionIndex + 1 + MAX_OPTION) % MAX_OPTION;
	}

	if (game->GetKey(VK_SPACE).bReleased) {
		LoadingThread(game, optionIndex);
		exit(1);
	}

	UpdateArrowCoord(optionIndex);
	this->DrawLoadingScreen(game);
	return true;
}
bool StateLoad::OnStateEnter() {
	this->game = game;
	SetArrowCoord(m_s_LINE_1);
	this->DrawLoadingScreen(game);
	return true;
}
bool StateLoad::OnStateExit() {
	return 1;
}


void StateLoad::LoadingThread(CrossingRoadGame*& game, const int& opt) {
	// Get data from path name

	// Animation
	MoveArrow(-4);
	LoadingAnimation(game);
}
void StateLoad::LoadingAnimation(CrossingRoadGame*& game) {
	int des_X = m_ArrowCoord.X;
	int speed = 10;

	while (des_X < m_s_X1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(int(24)));

		DrawLoadingScreen(game);
		game->DrawLine(m_ArrowCoord.X, m_ArrowCoord.Y, des_X,
			m_ArrowCoord.Y, 9608, FG_DARK_CYAN + BG_DARK_CYAN);
		game->ConsOutput();

		des_X += speed++;
	}
}

void StateLoad::UpdateArrowCoord(const int& opt) {
	switch (opt) {
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
void StateLoad::LS_FillBackground(CrossingRoadGame*& game) {
	// Phía trên đến hết vòng tròn
	game->Fill(m_s_X0 + m_s_OFFSET_X + 21, m_s_Y0 - 3, m_s_X1 + m_s_OFFSET_X - 36, m_s_Y0 - 2, 9608, FG_WHITE + BG_WHITE);
	game->Fill(m_s_X0 + m_s_OFFSET_X + 1, m_s_Y0 - 1, m_s_X1 + m_s_OFFSET_X - 11, m_s_Y0, 9608, FG_WHITE + BG_WHITE);
	game->Fill(m_s_X0 + m_s_OFFSET_X + 1, m_s_Y0 + 1, m_s_X1 + m_s_OFFSET_X + 2, m_s_Y0 + 2, 9608, FG_WHITE + BG_WHITE);
	game->Fill(m_s_X0 + m_s_OFFSET_X + 1, m_s_Y0 + 3, m_s_X1 + m_s_OFFSET_X + 4, m_s_Y0 + 8, 9608, FG_WHITE + BG_WHITE);
	game->Fill(m_s_X0 + m_s_OFFSET_X + 1, m_s_Y0 + 9, m_s_X1 + m_s_OFFSET_X + 2, m_s_Y0 + 9, 9608, FG_WHITE + BG_WHITE);

	// Phần thân đến vết rách
	game->Fill(m_s_X0 + m_s_OFFSET_X + 1, m_s_Y0 + 10, m_s_X1 + m_s_OFFSET_X - 5, m_s_Y0 + 12, 9608, FG_WHITE + BG_WHITE);
	game->Fill(m_s_X0 + m_s_OFFSET_X - 1, m_s_Y0 + 13, m_s_X1 + m_s_OFFSET_X - 5, m_s_Y0 + 34, 9608, FG_WHITE + BG_WHITE);
	game->Fill(m_s_X0 + m_s_OFFSET_X - 3, m_s_Y0 + 35, m_s_X1 + m_s_OFFSET_X - 5, m_s_Y0 + 62, 9608, FG_WHITE + BG_WHITE);
	game->Fill(m_s_X0 + m_s_OFFSET_X - 5, m_s_Y0 + 63, m_s_X1 + m_s_OFFSET_X - 7, m_s_Y0 + 70, 9608, FG_WHITE + BG_WHITE);

	// Bên trái của vết rách
	game->Fill(m_s_X0 + m_s_OFFSET_X - 4, m_s_Y0 + 71, m_s_X1 + m_s_OFFSET_X - 26, m_s_Y0 + 73, 9608, FG_WHITE + BG_WHITE);
	game->Fill(m_s_X0 + m_s_OFFSET_X - 4, m_s_Y0 + 74, m_s_X1 + m_s_OFFSET_X - 28, m_s_Y0 + 77, 9608, FG_WHITE + BG_WHITE);
	game->Fill(m_s_X0 + m_s_OFFSET_X + 31, m_s_Y0 + 78, m_s_X1 + m_s_OFFSET_X - 30, m_s_Y0 + 79, 9608, FG_WHITE + BG_WHITE);

	// Bên phải của vết rách
	game->Fill(m_s_X1 + m_s_OFFSET_X - 22, m_s_Y0 + 71, m_s_X1 + m_s_OFFSET_X - 8, m_s_Y0 + 76, 9608, FG_WHITE + BG_WHITE);
	game->Fill(m_s_X1 + m_s_OFFSET_X - 24, m_s_Y0 + 77, m_s_X1 + m_s_OFFSET_X - 9, m_s_Y0 + 81, 9608, FG_WHITE + BG_WHITE);
}

// Vẽ viền cho screen loadgame
void StateLoad::LS_DrawBorder(CrossingRoadGame*& game) {
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
void StateLoad::DrawCheckbox(CrossingRoadGame*& game, const COORD& _coord) {
	game->Draw(_coord.X - 1, _coord.Y, 9608, FG_GREY + BG_GREY);
	game->Draw(_coord.X, _coord.Y - 1, 9608, FG_GREY + BG_GREY);
	game->Draw(_coord.X, _coord.Y + 1, 9608, FG_GREY + BG_GREY);
	game->Draw(_coord.X + 1, _coord.Y, 9608, FG_GREY + BG_GREY);

	game->DrawLine(_coord.X + 3, _coord.Y + 2, _coord.X + 72, 
		_coord.Y + 2, 9608, FG_GREY + BG_GREY);
}
void StateLoad::DrawArrow(CrossingRoadGame*& game) {
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
void StateLoad::LS_DecorateScreen(CrossingRoadGame*& game) {
	game->DrawLine(m_s_X0 + m_s_OFFSET_X + 10, m_s_Y0 + 10, m_s_X1 + m_s_OFFSET_X - 10,
		m_s_Y0 + 10, 9608, FG_RED + BG_RED);

	DrawCheckbox(game, m_s_LINE_1);
	DrawCheckbox(game, m_s_LINE_2);
	DrawCheckbox(game, m_s_LINE_3);
	DrawCheckbox(game, m_s_LINE_4);
}
void StateLoad::DrawLoadingScreen(CrossingRoadGame*& game)
{
	// clear screen
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);

	// Tô màu nền
	LS_FillBackground(game);

	// Vẽ viền
	LS_DrawBorder(game);

	// Trang trí
	LS_DecorateScreen(game);

	// Hiển thị mũi tên (pointer)
	DrawArrow(game);
}