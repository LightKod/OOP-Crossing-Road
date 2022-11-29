#include "StateSetting.h"
#include "StateMenu.h"
#define MAX_CHAR_IDX 2
#define MAX_CORNER_IDX 4
#define LINE_WAITING 1.f
#define CORNER_WAITING 20.0f
#define TIME_FACTOR 30

// Biến để chạy thread
bool iStop = true;
mutex mtx;
condition_variable cv;
bool ready = false;

// ==============================================================
const int StateSetting::M_S_SRC_X0 = 9;
const int StateSetting::M_S_SRC_X1 = 151;
const int StateSetting::M_S_SRC_Y0 = 24;
const int StateSetting::M_S_SRC_Y1 = 90;

const pair<short, short> StateSetting::MB_COLOR = { FG_BLUE, BG_BLUE };// FG_BLUE, BG_BLUE

const COORD StateSetting::C_FRAME_1 = { 38, 38 };
const COORD StateSetting::C_FRAME_2 = { 38, 60 };
const COORD StateSetting::C_RING_1 = { 102, 40 };
const COORD StateSetting::C_RING_2 = { 102, 62 };
COORD StateSetting::C_MOUSE_POINTER = C_RING_1;
const COORD StateSetting::DOG_COORD = { C_FRAME_2.X + 22, C_FRAME_2.Y + 4 };
const COORD StateSetting::FROG_COORD = { C_FRAME_1.X + 19, C_FRAME_1.Y + 4 };

const int StateSetting::maxStateIdx = 8; // dùng để điều chỉnh tốc độ hiển thị line chạy
short StateSetting::curCharIdx = 0; // dùng để cập nhất mouse_pointer
short StateSetting::lastCharIdx = 0; // lưu giá trị gán cho CrossingRoadGame::s_CharIdx

bool StateSetting::Update(float fElapsedTime) {
	if (game->GetKey(VK_ESCAPE).bPressed) {
		CrossingRoadGame::s_CharIdx = StateSetting::lastCharIdx;
		game->SetState(new StateMenu(game));
		return 1;
	}

	if (game->GetKey(VK_W).bPressed) {
		curCharIdx = (curCharIdx - 1 + MAX_CHAR_IDX) % MAX_CHAR_IDX;
		PointerHandle();
	}

	if (game->GetKey(VK_S).bPressed) {
		curCharIdx = (curCharIdx + 1) % MAX_CHAR_IDX;
		PointerHandle();
	}

	if (game->GetKey(VK_SPACE).bPressed) {
		if (lastCharIdx != curCharIdx) {
			// clicking animation
			Clicking();

			// cập nhật character_idx
			lastCharIdx = curCharIdx;

			UpdateMainBorder();
		}
	}

	UpdateCorners(fElapsedTime);
	return 1;
}
bool StateSetting::OnStateEnter() {
	this->game = game;
	this->curLimitWaiting = CORNER_WAITING;

	// clear screen
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_DARK_CYAN);

	DrawTitle(16, 2);
	MainBorder();

	UpdateMainBorder();

	return 1;
}
bool StateSetting::OnStateExit() {
	return 1;
}


void StateSetting::UpdateMainBorder() {
	// clear everything in main border
	MainBorderColor();

	// draw mouse pointer
	UpdatePointerCoord();
	DrawMousePointer();

	// ==================== running 2 threads ====================
	//// rings rotation
	//UpdateRing1();
	//UpdateRing2();
	//// draw frame 
	//FrameFlowAnimation(C_FRAME_1, &StateSetting::DrawFrogFrame);
	//FrameFlowAnimation(C_FRAME_2, &StateSetting::DrawDogFrame);

	iStop = false;
	ThreadDriver(this);
	while (!iStop);

}


void StateSetting::DrawFrogFrame(const int& offsetX) {
	if (lastCharIdx == 0) {
		SelectedFrame(C_FRAME_1.X + offsetX, C_FRAME_1.Y);
		Frog(FROG_COORD.X + offsetX, FROG_COORD.Y, FG_BLACK, BG_BLACK);
	}
	else {
		UnselectedFrame(C_FRAME_1.X + offsetX, C_FRAME_1.Y);
		Frog(FROG_COORD.X + offsetX, FROG_COORD.Y, FG_DARK_GREY, BG_DARK_GREY);
	}
}
void StateSetting::DrawDogFrame(const int& offsetX) {
	if (lastCharIdx == 1) {
		SelectedFrame(C_FRAME_2.X + offsetX, C_FRAME_2.Y);
		Dog(DOG_COORD.X + offsetX, DOG_COORD.Y, FG_BLACK, BG_BLACK);
	}
	else {
		UnselectedFrame(C_FRAME_2.X + offsetX, C_FRAME_2.Y);
		Dog(DOG_COORD.X + offsetX, DOG_COORD.Y, FG_DARK_GREY, BG_DARK_GREY);
	}
}
void StateSetting::Dog(const int& x, const int& y,
	const short& fg, const short& bg)
{
	D(x, y, fg, bg);
	O(x + 5, y, fg, bg);
	G(x +10, y, fg, bg);
}
void StateSetting::Frog(const int& x, const int& y,
	const short& fg, const short& bg)
{
	F(x, y, fg, bg);
	R(x + 5, y, fg, bg);
	O(x + 10, y, fg, bg);
	G(x + 15, y, fg, bg);
}
void StateSetting::F(const int& x, const int& y,
	const short& fg, const short& bg)
{
	game->DrawLine(x, y, x, y + 4, 9608, fg + bg);
	game->DrawLine(x + 1, y, x + 3, y, 9608, fg + bg);
	game->DrawLine(x + 1, y + 2, x + 2, y + 2, 9608, fg + bg);

}
void StateSetting::R(const int& x, const int& y,
	const short& fg, const short& bg)
{
	game->DrawLine(x, y, x, y + 4, 9608, fg + bg);
	game->DrawLine(x + 1, y, x + 2, y, 9608, fg + bg);
	game->DrawLine(x + 1, y + 2, x + 2, y + 2, 9608, fg + bg);
	game->DrawLine(x + 3, y, x + 3, y + 2, 9608, fg + bg);
	game->DrawLine(x + 2, y + 3, x + 3, y + 4, 9608, fg + bg);

}
void StateSetting::O(const int& x, const int& y,
	const short& fg, const short& bg)
{
	game->DrawLine(x, y, x, y + 4, 9608, fg + bg);
	game->DrawLine(x + 3, y, x + 3, y + 4, 9608, fg + bg);
	game->DrawLine(x + 1, y, x + 2, y, 9608, fg + bg);
	game->DrawLine(x + 1, y + 4, x + 2, y + 4, 9608, fg + bg);

}
void StateSetting::G(const int& x, const int& y,
	const short& fg, const short& bg)
{
	game->DrawLine(x, y, x, y + 4, 9608, fg + bg);
	game->DrawLine(x + 1, y, x + 3, y, 9608, fg + bg);
	game->DrawLine(x + 1, y + 4, x + 3, y + 4, 9608, fg + bg);
	game->DrawLine(x + 3, y + 2, x + 3, y + 3, 9608, fg + bg);
	game->Draw(x + 2, y + 2, 9608, fg + bg);

}
void StateSetting::D(const int& x, const int& y,
	const short& fg, const short& bg)
{
	game->DrawLine(x, y, x, y + 4, 9608, fg + bg);
	game->DrawLine(x + 3, y + 1, x + 3, y + 3, 9608, fg + bg);
	game->DrawLine(x + 1, y, x + 2, y, 9608, fg + bg);
	game->DrawLine(x + 1, y + 4, x + 2, y + 4, 9608, fg + bg);

}


void StateSetting::ClearFrame(const int& x, const int& y) {
	UIFrame(x, y,
		MB_COLOR.first, MB_COLOR.second,
		MB_COLOR.first, MB_COLOR.second,
		MB_COLOR.first, MB_COLOR.second,
		MB_COLOR.first, MB_COLOR.second);
}
void StateSetting::FrameFlowAnimation(const COORD& _C, 
	void(StateSetting::*pFunc)(const int&))
{
	static const int _tm = 10;

	for (int i = 7; i >= 0; --i) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		(this->*pFunc)(i);
		game->ConsOutput();

		if (!i) return;
		ClearFrame(_C.X + i, _C.Y);
	}

}
void StateSetting::SelectedFrame(const int& x, const int& y) {
	UIFrame(x, y,
		FG_BLACK, BG_BLACK,
		FG_GREY, BG_GREY,
		FG_DARK_YELLOW, BG_DARK_YELLOW,
		FG_YELLOW, BG_YELLOW);
}
void StateSetting::UnselectedFrame(const int& x, const int& y) {
	UIFrame(x, y,
		FG_DARK_GREY, BG_DARK_GREY,
		FG_GREY, BG_GREY,
		FG_GREY, BG_GREY,
		FG_GREY, BG_GREY);
}
void StateSetting::UIFrame(const int& x, const int& y,
	const short& borderFg, const short& borderBg,
	const short& topLayerFg, const short& topLayerBg,
	const short& botLayerFg, const short& botLayerBg,
	const short& mainFg, const short& mainBg)
{
	// border
	game->DrawLine(x + 6, y, x +50, y, 9608, borderFg + borderBg);
	game->DrawLine(x + 6, y+12, x +50, y+12, 9608, borderFg + borderBg);
	game->DrawLine(x +51, y + 1, x +56, y + 6, 9608, borderFg + borderBg);
	game->DrawLine(x +51, y +11, x +55, y + 7, 9608, borderFg + borderBg);
	game->DrawLine(x, y + 6, x + 5, y + 1, 9608, borderFg + borderBg);
	game->DrawLine(x + 1, y + 7, x + 5, y +11, 9608, borderFg + borderBg);

	// top layer
	game->DrawLine(x + 6, y + 1, x + 50, y + 1, 9608, topLayerFg + topLayerBg);
	game->DrawLine(x +51, y + 2, x + 54, y + 5, 9608, topLayerFg + topLayerBg);
	game->DrawLine(x + 2, y + 5, x +  5, y + 2, 9608, topLayerFg + topLayerBg);

	// bot layer
	game->DrawLine(x + 6, y + 11, x + 50, y + 11, 9608, botLayerFg + botLayerBg);
	game->DrawLine(x + 1, y +  6, x + 5, y + 10, 9608, botLayerFg + botLayerBg);
	game->DrawLine(x +51, y + 10, x +55, y + 6, 9608, botLayerFg + botLayerBg);

	// main
	game->Draw(x + 2, y + 6, 9608, mainFg + mainBg);
	game->DrawLine(x + 3, y + 5, x + 3, y + 7, 9608, mainFg + mainBg);
	game->DrawLine(x + 4, y + 4, x + 4, y + 8, 9608, mainFg + mainBg);
	game->DrawLine(x + 5, y + 3, x + 5, y + 9, 9608, mainFg + mainBg);
	game->Fill(x + 6, y + 2, x +50, y +10, 9608, mainFg + mainBg);
	game->Draw(x + 54, y + 6, 9608, mainFg + mainBg);
	game->DrawLine(x + 53, y + 5, x + 53, y + 7, 9608, mainFg + mainBg);
	game->DrawLine(x + 52, y + 4, x + 52, y + 8, 9608, mainFg + mainBg);
	game->DrawLine(x + 51, y + 3, x + 51, y + 9, 9608, mainFg + mainBg);

}


void StateSetting::PointerHandle() {
	ClearPointer();
	UpdatePointerCoord();
	DrawMousePointer();
}
void StateSetting::ClearPointer() {
	game->Fill(C_MOUSE_POINTER.X, C_MOUSE_POINTER.Y, 
		C_MOUSE_POINTER.X + 15, C_MOUSE_POINTER.Y + 14, L' ', MB_COLOR.second);//  MB_COLOR.second
}
void StateSetting::UpdatePointerCoord() {
	static const int offsetX = 14;
	static const int offsetY = 6;

	switch (curCharIdx) {
	default:
	case 0:
		C_MOUSE_POINTER.X = C_RING_1.X + offsetX;
		C_MOUSE_POINTER.Y = C_RING_1.Y + offsetY;
		break;
	case 1:
		C_MOUSE_POINTER.X = C_RING_2.X + offsetX;
		C_MOUSE_POINTER.Y = C_RING_2.Y + offsetY;
		break;
	}

}
void StateSetting::DrawMousePointer() {
	int x = C_MOUSE_POINTER.X;
	int y = C_MOUSE_POINTER.Y;
	
	// vẽ viền ngoài
	game->DrawLine(x + 1, y	   , x + 2, y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y	+ 1, x + 4, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y	+ 2, x + 6, y + 3, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 6, y	+ 1, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 7, y + 1, x + 8, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 8, y, x +10, y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +11, y + 1, x +12, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +12, y + 3, x +13, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +13, y + 5, x +13, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +12, y + 8, x +13, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +14, y + 7, x +15, y + 8, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +10, y +14, x +15, y + 9, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 8, y +13, x + 9, y +14, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 8, y +11, x + 8, y +12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 9, y +11, x +10, y +10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 5, y +11, x + 7, y +11, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 3, y + 9, x + 4, y +10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 6, x + 2, y + 8, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 1, y + 4, x + 3, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x, y + 1, x, y + 3, 9608, FG_BLACK + BG_BLACK);

	// vẽ nền đậm
	game->DrawLine(x + 3, y + 7, x + 4, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 9, y +13, x +10, y +13, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 8, y + 5, x + 9, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x +10, y + 4, x +11, y + 5, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 3, y + 8, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 9, y +12, 9608, FG_DARK_GREY + BG_DARK_GREY);

	// vẽ nèn nhạt
	game->DrawLine(x + 1, y + 3, x + 5, y + 7, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 6, y + 2, x + 7, y + 3, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 8, y + 1, x + 9, y + 2, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x + 5, y +10, x + 9, y +10, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x +10, y +11, x +10, y +12, 9608, FG_GREY + BG_GREY);
	game->DrawLine(x +11, y +12, x +13, y +10, 9608, FG_GREY + BG_GREY);
	game->Fill(x + 4, y + 8, x + 5, y + 9, 9608, FG_GREY + BG_GREY);

	// Tô màu găng tay
	game->DrawLine(x + 1, y + 2, x + 5, y + 6, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 1, y + 1, x + 6, y + 6, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 2, y + 1, x + 7, y + 6, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 5, y + 3, x + 8, y + 6, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 5, y + 3, x + 8, y + 6, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 7, y + 2, x +11, y + 6, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 8, y + 4, x +10, y + 6, 9608, FG_WHITE + BG_WHITE);
	game->Draw(x + 7, y + 4, 9608, FG_WHITE + BG_WHITE);
	game->Draw(x + 9, y + 3, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x +10, y + 3, x + 11, y + 4, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x + 9, y + 1, x + 11, y + 3, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x +10, y + 1, x + 11, y + 2, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x +12, y + 4, x + 12, y + 7, 9608, FG_WHITE + BG_WHITE);
	game->Fill(x + 6, y + 7, x +11, y + 9, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x +11, y +10, x +13, y + 8, 9608, FG_WHITE + BG_WHITE);
	game->DrawLine(x +11, y +11, x +14, y + 8, 9608, FG_WHITE + BG_WHITE);
	game->Draw(x +14, y + 9, 9608, FG_WHITE + BG_WHITE);

}
void StateSetting::Clicking() {
	// clear old pointer
	ClearPointer();

	// update new coord
	C_MOUSE_POINTER.X -= 6;
	C_MOUSE_POINTER.Y -= 2;

	// draw new one
	DrawMousePointer();

	// clicking
	int x = C_MOUSE_POINTER.X;
	int y = C_MOUSE_POINTER.Y;

	game->DrawLine(x - 4, y, x - 3, y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x, y - 4, x, y - 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x - 4, y - 4, x - 2, y - 2, 9608, FG_BLACK + BG_BLACK);

	game->ConsOutput();
	this_thread::sleep_for(std::chrono::milliseconds(100));
}


void StateSetting::UpdateRing1() {
	if (lastCharIdx == 0) {
		SelectedAnimation(C_RING_1.X, C_RING_1.Y);
	}
	else {
		UnselectedAnimation(C_RING_1.X, C_RING_1.Y);
	}
}
void StateSetting::UpdateRing2() {
	if (lastCharIdx == 1) {
		SelectedAnimation(C_RING_2.X, C_RING_2.Y);
	}
	else {
		UnselectedAnimation(C_RING_2.X, C_RING_2.Y);
	}

}
void StateSetting::SelectedAnimation(const int& x, const int& y) {
	static const short _tm = 90;

	for (int stateIdx = 1; stateIdx <= 8; stateIdx++) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));
		ClearRing(x, y, FG_BLUE, BG_BLUE);

		switch (stateIdx) {
		case 1:
			Ring1(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
			break;
		case 2:
			Ring2(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
			break;
		case 3:
			Ring3(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
			break;
		case 4:
			Ring4(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
			break;
		case 5:
			Ring5(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
			break;
		case 6:
			Ring6(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
			break;
		case 7:
			Ring7(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
			break;
		case 8:
			Ring8(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
			break;
		}

		game->ConsOutput();
	}
	// FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY
	// FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW
}
void StateSetting::UnselectedAnimation(const int& x, const int& y) {
	static const short _tm = 100;

	for (int stateIdx = 2; stateIdx <= 8; stateIdx++) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));
		ClearRing(x, y, FG_BLUE, BG_BLUE);

		switch (stateIdx) {
		case 1:
			Ring1(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
			break;
		case 2:
			Ring2(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
			break;
		case 3:
			Ring3(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
			break;
		case 4:
			Ring4(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
			break;
		case 5:
			Ring5(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
			break;
		case 6:
			Ring6(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
			break;
		case 7:
			Ring7(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
			break;
		case 8:
			Ring8(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
			break;
		}

		game->ConsOutput();
	}
}
void StateSetting::Ring1(const int& x, const int& y,
	const short& mainFg, const short& mainBg,
	const short& subFg, const short& subBg)
{
	// tô nền
	game->DrawLine(x, y + 2, x, y + 7, 9608, mainFg + mainBg);
	game->DrawLine(x + 8, y + 2, x + 8, y + 7, 9608, mainFg + mainBg);
	game->DrawLine(x + 1, y + 1, x + 7, y + 1, 9608, mainFg + mainBg);
	game->DrawLine(x + 2, y, x + 6, y, 9608, mainFg + mainBg);
	game->DrawLine(x + 1, y + 8, x + 7, y + 8, 9608, mainFg + mainBg);
	game->DrawLine(x + 2, y + 9, x + 6, y + 9, 9608, mainFg + mainBg);

	// tô viền
	game->DrawLine(x + 1, y + 2, x + 1, y + 7, 9608, subFg + subBg);
	game->DrawLine(x + 9, y + 2, x + 9, y + 7, 9608, subFg + subBg);
	game->DrawLine(x + 7, y, x + 8, y + 1, 9608, subFg + subBg);
	game->DrawLine(x + 7, y + 9, x + 8, y + 8, 9608, subFg + subBg);

}
void StateSetting::Ring2(const int& x, const int& y,
	const short& mainFg, const short& mainBg,
	const short& subFg, const short& subBg)
{
	// tô nền
	game->DrawLine(x + 1, y + 3, x + 1, y + 5, 9608, mainFg + mainBg);
	game->DrawLine(x + 6, y + 3, x + 6, y + 5, 9608, mainFg + mainBg);
	game->DrawLine(x + 2, y + 2, x + 5, y + 2, 9608, mainFg + mainBg);
	game->DrawLine(x + 2, y + 6, x + 5, y + 6, 9608, mainFg + mainBg);
	game->DrawLine(x + 3, y + 1, x + 4, y + 1, 9608, mainFg + mainBg);
	game->DrawLine(x + 3, y + 7, x + 4, y + 7, 9608, mainFg + mainBg);

	// tô viền
	game->DrawLine(x + 2, y + 3, x + 2, y + 5, 9608, subFg + subBg);
	game->DrawLine(x + 7, y + 3, x + 7, y + 5, 9608, subFg + subBg);
	game->DrawLine(x + 5, y + 1, x + 6, y + 2, 9608, subFg + subBg);
	game->DrawLine(x + 5, y + 7, x + 6, y + 6, 9608, subFg + subBg);

}
void StateSetting::Ring3(const int& x, const int& y,
	const short& mainFg, const short& mainBg,
	const short& subFg, const short& subBg)
{
	// tô nền
	game->DrawLine(x + 4, y + 3, x + 4, y + 5, 9608, mainFg + mainBg);
	game->DrawLine(x + 6, y + 3, x + 6, y + 5, 9608, mainFg + mainBg);
	game->Draw(x + 5, y + 2, 9608, mainFg + mainBg);
	game->Draw(x + 5, y + 6, 9608, mainFg + mainBg);

	// tô viền
	game->DrawLine(x + 3, y + 3, x + 3, y + 5, 9608, subFg + subBg);
	game->DrawLine(x + 5, y + 3, x + 5, y + 5, 9608, subFg + subBg);
	game->Draw(x + 4, y + 2, 9608, subFg + subBg);
	game->Draw(x + 4, y + 6, 9608, subFg + subBg);
	
}
void StateSetting::Ring4(const int& x, const int& y,
	const short& mainFg, const short& mainBg,
	const short& subFg, const short& subBg)
{
	// tô nền
	game->DrawLine(x + 5, y + 2, x + 5, y + 6, 9608, mainFg + mainBg);

	// tô viền
	game->DrawLine(x + 4, y + 2, x + 4, y + 6, 9608, subFg + subBg);

}
void StateSetting::Ring5(const int& x, const int& y,
	const short& mainFg, const short& mainBg,
	const short& subFg, const short& subBg)
{
	Ring4(x, y, subFg, subBg, mainFg, mainBg);

}
void StateSetting::Ring6(const int& x, const int& y,
	const short& mainFg, const short& mainBg,
	const short& subFg, const short& subBg)
{
	Ring3(x, y, subFg, subBg, mainFg, mainBg);
}
void StateSetting::Ring7(const int& x, const int& y,
	const short& mainFg, const short& mainBg,
	const short& subFg, const short& subBg)
{
	Ring2(x, y, mainFg, mainBg, subFg, subBg);
}
void StateSetting::Ring8(const int& x, const int& y,
	const short& mainFg, const short& mainBg,
	const short& subFg, const short& subBg)
{
	Ring1(x, y, mainFg, mainBg, subFg, subBg);
}
void StateSetting::ClearRing(const int& x, const int& y,
	const short& fg, const short& bg)
{
	game->Fill(x, y, x + 9, y + 9, L' ', MB_COLOR.second);
}


void StateSetting::MainBorder() {
	Draw_TL_Corner(FG_WHITE, BG_WHITE);
	Draw_TR_Corner(FG_DARK_GREY, BG_DARK_GREY);
	Draw_BL_Corner(FG_DARK_GREY, BG_DARK_GREY);
	Draw_BR_Corner(FG_DARK_GREY, BG_DARK_GREY);

	OuterBorder();
	InnerBorder();

	OuterBorderColor();
	InnerBorderColor();

	MainBorderColor();
}
void StateSetting::MainBorderColor() {
	static const int _x0 = M_S_SRC_X0 + 5;
	static const int _y0 = M_S_SRC_Y0 + 5;
	static const int _x1 = M_S_SRC_X1 - 5;
	static const int _y1 = M_S_SRC_Y1 - 5;

	// first row
	game->DrawLine(_x0 + 1, _y0, _x1 - 1, _y0, 9608, MB_COLOR.first + MB_COLOR.second);

	// the rest
	game->Fill(_x0 + 1, _y0 + 1, _x1, _y1 - 1, 9608, MB_COLOR.first + MB_COLOR.second);

}

void StateSetting::OuterBorderColor() {
	static const int _x0 = M_S_SRC_X0 + 3;
	static const int _y0 = M_S_SRC_Y0 + 3;
	static const int _x1 = M_S_SRC_X1 - 3;
	static const int _y1 = M_S_SRC_Y1 - 3;

	// 4 .
	game->Draw(_x0 + 1, _y0 + 1, 9608, FG_GREY + BG_GREY);// TL
	game->Draw(_x1 - 1, _y0 + 1, 9608, FG_GREY + BG_GREY);// TR
	game->Draw(_x0 + 1, _y1 - 1, 9608, FG_DARK_GREY + BG_DARK_GREY);// BL
	game->Draw(_x1 - 1, _y1 - 1, 9608, FG_DARK_GREY + BG_DARK_GREY);// BR

	// Corner
	game->DrawLine(_x0 + 1, _y0 + 2, _x0 + 2, _y0 + 1, 9608, FG_GREY + BG_GREY);		  // TL
	game->DrawLine(_x1 - 1, _y0 + 2, _x1 - 2, _y0 + 1, 9608, FG_GREY + BG_GREY);		  // TR
	game->DrawLine(_x0 + 1, _y1 - 2, _x0 + 2, _y1 - 1, 9608, FG_DARK_GREY + BG_DARK_GREY);// BL
	game->DrawLine(_x1 - 1, _y1 - 2, _x1 - 2, _y1 - 1, 9608, FG_DARK_GREY + BG_DARK_GREY);// BR

	// Line
	game->DrawLine(_x0 + 3, _y0, _x1 - 3, _y0, 9608, FG_GREY + BG_GREY);		  // T
	game->DrawLine(_x1, _y0 + 3, _x1, _y1 - 3, 9608, FG_GREY + BG_GREY);		  // R
	game->DrawLine(_x0, _y0 + 3, _x0, _y1 - 3, 9608, FG_DARK_GREY + BG_DARK_GREY);// L
	game->DrawLine(_x0 + 3, _y1, _x1 - 3, _y1, 9608, FG_DARK_GREY + BG_DARK_GREY);// B
}
void StateSetting::InnerBorderColor() {
	static const int _x0 = M_S_SRC_X0 + 5;
	static const int _y0 = M_S_SRC_Y0 + 5;
	static const int _x1 = M_S_SRC_X1 - 5;
	static const int _y1 = M_S_SRC_Y1 - 5;

	static const short fg = FG_DARK_BLUE;// fg + bg
	static const short bg = BG_DARK_BLUE;

	// Line
	game->DrawLine(_x0, _y0 + 1, _x0, _y1 - 1, 9608, fg + bg);// L
	game->DrawLine(_x0 + 1, _y1, _x1 - 1, _y1, 9608, fg + bg);// B
}

void StateSetting::OuterBorder() {
	static const int _x0 = M_S_SRC_X0;
	static const int _y0 = M_S_SRC_Y0;
	static const int _x1 = M_S_SRC_X1;
	static const int _y1 = M_S_SRC_Y1;

	// 4 .
	game->Draw(_x0 + 2, _y0 + 2, 9608, FG_WHITE + BG_WHITE);// TL
	game->Draw(_x0 + 2, _y1 - 2, 9608, FG_WHITE + BG_WHITE);// BL
	game->Draw(_x1 - 2, _y0 + 2, 9608, FG_WHITE + BG_WHITE);// TR
	game->Draw(_x1 - 2, _y1 - 2, 9608, FG_WHITE + BG_WHITE);// BR

	game->DrawLine(_x0 + 5, _y0 + 2, _x1 - 5, _y0 + 2, 9608, FG_BLACK + BG_BLACK);// T
	game->DrawLine(_x0 + 5, _y1 - 2, _x1 - 5, _y1 - 2, 9608, FG_BLACK + BG_BLACK);// B
	game->DrawLine(_x0 + 2, _y0 + 5, _x0 + 2, _y1 - 5, 9608, FG_BLACK + BG_BLACK);// L
	game->DrawLine(_x1 - 2, _y0 + 5, _x1 - 2, _y1 - 5, 9608, FG_BLACK + BG_BLACK);// R

	// TL corner
	game->DrawLine(_x0 + 3, _y0 + 3, _x0 + 5, _y0 + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x0 + 3, _y0 + 4, _x0 + 3, _y0 + 5, 9608, FG_BLACK + BG_BLACK);

	// BL corner
	game->DrawLine(_x0 + 3, _y1 - 3, _x0 + 5, _y1 - 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x0 + 3, _y1 - 4, _x0 + 3, _y1 - 5, 9608, FG_BLACK + BG_BLACK);

	// TR Corner
	game->DrawLine(_x1 - 3, _y0 + 3, _x1 - 5, _y0 + 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x1 - 3, _y0 + 4, _x1 - 3, _y0 + 5, 9608, FG_BLACK + BG_BLACK);

	// BR Corner
	game->DrawLine(_x1 - 3, _y1 - 3, _x1 - 5, _y1 - 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(_x1 - 3, _y1 - 4, _x1 - 3, _y1 - 5, 9608, FG_BLACK + BG_BLACK);
}
void StateSetting::InnerBorder() {
	static const int _x0 = M_S_SRC_X0 + 4;
	static const int _y0 = M_S_SRC_Y0 + 4;
	static const int _x1 = M_S_SRC_X1 - 4;
	static const int _y1 = M_S_SRC_Y1 - 4;

	// 4 .
	game->Draw(_x0 + 1, _y0 + 1, 9608, FG_BLACK + BG_BLACK);// TL
	game->Draw(_x0 + 1, _y1 - 1, 9608, FG_BLACK + BG_BLACK);// BL
	game->Draw(_x1 - 1, _y0 + 1, 9608, FG_BLACK + BG_BLACK);// TR
	game->Draw(_x1 - 1, _y1 - 1, 9608, FG_BLACK + BG_BLACK);// BR

	game->DrawLine(_x0 + 2, _y0, _x1 - 2, _y0, 9608, FG_BLACK + BG_BLACK);// T
	game->DrawLine(_x0 + 2, _y1, _x1 - 2, _y1, 9608, FG_BLACK + BG_BLACK);// B
	game->DrawLine(_x0, _y0 + 2, _x0, _y1 - 2, 9608, FG_BLACK + BG_BLACK);// L
	game->DrawLine(_x1, _y0 + 2, _x1, _y1 - 2, 9608, FG_BLACK + BG_BLACK);// R

}

void StateSetting::UpdateCorners(const float& fElapsedTime) {
	static float deltaTm = 0.f;

	static const int _x0 = M_S_SRC_X0;
	static const int _y0 = M_S_SRC_Y0;
	static const int _x1 = M_S_SRC_X1;
	static const int _y1 = M_S_SRC_Y1;

	deltaTm += fElapsedTime * TIME_FACTOR;

	if (deltaTm >= this->curLimitWaiting) {
		// Update old corner
		if (this->curStateIdx == 1) {
			switch (this->curCornerIdx) {
			case 0:
				Draw_TL_Corner(FG_DARK_GREY, BG_DARK_GREY);
				break;

			case 1:
				Draw_TR_Corner(FG_DARK_GREY, BG_DARK_GREY);
				break;

			case 2:
				Draw_BR_Corner(FG_DARK_GREY, BG_DARK_GREY);
				break;

			case 3:
				Draw_BL_Corner(FG_DARK_GREY, BG_DARK_GREY);
				break;
			}

			this->curLimitWaiting = LINE_WAITING;
		}

		// Update lines
		switch (this->curCornerIdx) {
		case 0:
			InState_DrawHorizontalLine(_x0 + 5, _x1 - 5, _y0, this->curStateIdx);
			break;

		case 1:
			InState_DrawVerticalLine(_x1, _y0 + 5, _y1 - 5, this->curStateIdx);
			break;

		case 2:
			InState_DrawHorizontalLine(_x1 - 5, _x0 + 5, _y1, this->curStateIdx);
			break;

		case 3:
			InState_DrawVerticalLine(_x0, _y1 - 5, _y0 + 5, this->curStateIdx);
			break;
		}

		if (this->curStateIdx <= maxStateIdx) {
			++this->curStateIdx;
		}
		else { 
			// reset some curData
			this->curCornerIdx = (this->curCornerIdx + 1) % MAX_CORNER_IDX;
			this->curStateIdx = 1;
			this->curLimitWaiting = CORNER_WAITING;
			
			// update new corner
			switch (this->curCornerIdx) {
			case 0:
				Draw_TL_Corner(FG_WHITE, BG_WHITE);
				break;

			case 1:
				Draw_TR_Corner(FG_WHITE, BG_WHITE);
				break;

			case 2:
				Draw_BR_Corner(FG_WHITE, BG_WHITE);
				break;

			case 3:
				Draw_BL_Corner(FG_WHITE, BG_WHITE);
				break;
			}
		}

		deltaTm = 0.f;
	}

}
void StateSetting::InState_DrawHorizontalLine(const int& x0, const int& x1,
	const int& y, const int& stateIdx)
{
	static const int distance = abs(x1 - x0) + 1;
	int factor = (x0 < x1) ? 1 : -1;

	// clear old line
	if (stateIdx != 1) {
		game->DrawLine(
			x0 + factor * (stateIdx - 1 - 1) * distance / maxStateIdx, y,
			x1 - factor * (maxStateIdx - stateIdx + 1) * distance / maxStateIdx, y, L' ', COLOUR::BG_DARK_CYAN);
	}
	// draw new line
	if (stateIdx <= maxStateIdx) {
		game->DrawLine(
			x0 + factor * (stateIdx - 1) * distance / maxStateIdx, y,
			x1 - factor * (maxStateIdx - stateIdx) * distance / maxStateIdx, y, 9608, FG_WHITE + BG_WHITE);
	}

}
void StateSetting::InState_DrawVerticalLine(const int& x, const int& y0,
	const int& y1, const int& stateIdx)
{
	static const int distance = abs(y1 - y0) + 1;
	int factor = (y0 < y1) ? 1 : -1;

	// clear old line
	if (stateIdx != 1) {
		game->DrawLine(
			x, y0 + factor * (stateIdx - 1 - 1) * distance / maxStateIdx,
			x, y1 - factor * (maxStateIdx - stateIdx + 1) * distance / maxStateIdx, L' ', COLOUR::BG_DARK_CYAN);
	}
	
	if (stateIdx <= maxStateIdx) {
		game->DrawLine(
			x, y0 + factor * (stateIdx - 1) * distance / maxStateIdx,
			x, y1 - factor * (maxStateIdx - stateIdx) * distance / maxStateIdx, 9608, FG_WHITE + BG_WHITE);
	}

}
void StateSetting::Draw_TL_Corner(const short& fg, const short& bg) {
	static const int _x = M_S_SRC_X0;
	static const int _y = M_S_SRC_Y0;

	game->DrawLine(_x, _y, _x + 2, _y, 9608, fg + bg);
	game->DrawLine(_x, _y + 1, _x, _y + 2, 9608, fg + bg);
}
void StateSetting::Draw_TR_Corner(const short& fg, const short& bg) {
	static const int _x = M_S_SRC_X1;
	static const int _y = M_S_SRC_Y0;

	game->DrawLine(_x - 2, _y, _x, _y, 9608, fg + bg);
	game->DrawLine(_x, _y + 1, _x, _y + 2, 9608, fg + bg);
}
void StateSetting::Draw_BL_Corner(const short& fg, const short& bg) {
	static const int _x = M_S_SRC_X0;
	static const int _y = M_S_SRC_Y1;

	game->DrawLine(_x, _y, _x + 2, _y, 9608, fg + bg);
	game->DrawLine(_x, _y - 2, _x, _y - 1, 9608, fg + bg);
}
void StateSetting::Draw_BR_Corner(const short& fg, const short& bg) {
	static const int _x = M_S_SRC_X1;
	static const int _y = M_S_SRC_Y1;

	game->DrawLine(_x - 2, _y, _x, _y, 9608, fg + bg);
	game->DrawLine(_x, _y - 2, _x, _y - 1, 9608, fg + bg);
}


void StateSetting::DrawTitle(const int& x, const int& y) {
	TitleBorder(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW);
	TitleBackground(x, y, FG_YELLOW, BG_YELLOW);
	string2Pixel(L"SELECT YOUR CHARACTER", x + 12, y + 8, FG_BLACK, BG_YELLOW);
}
void StateSetting::TitleBorder(const int& x, const int& y,
	const short& fg, const short& bg)
{
	game->DrawLine(x, y + 6, x, y + 13, 9608, fg + bg);
	game->Fill(x, y + 4, x + 1, y + 5, 9608, fg + bg);
	game->Fill(x + 1, y + 1, x + 3, y + 3, 9608, fg + bg);
	game->Fill(x + 4, y, x + 5, y + 1, 9608, fg + bg);
	game->Fill(x, y + 14, x + 1, y + 15, 9608, fg + bg);
	game->Fill(x + 2, y + 15, x + 4, y + 17, 9608, fg + bg);
	game->Fill(x + 5, y + 17, x + 6, y + 18, 9608, fg + bg);

	game->DrawLine(x + 6, y, x + 122, y, 9608, fg + bg);
	game->DrawLine(x + 7, y + 18, x + 121, y + 18, 9608, fg + bg);

	game->Fill(x + 123, y, x + 124, y + 1, 9608, fg + bg);
	game->Fill(x + 125, y + 1, x + 127, y + 3, 9608, fg + bg);
	game->Fill(x + 127, y + 4, x + 128, y + 5, 9608, fg + bg);
	game->Fill(x + 122, y + 17, x + 123, y + 18, 9608, fg + bg);
	game->Fill(x + 124, y + 15, x + 126, y + 17, 9608, fg + bg);
	game->Fill(x + 127, y + 14, x + 128, y + 15, 9608, fg + bg);
	game->DrawLine(x + 128, y + 6, x + 128, y + 13, 9608, fg + bg);

}
void StateSetting::TitleBackground(const int& x, const int& y,
	const short& fg, const short& bg)
{
	game->Fill(x + 6, y + 1, x + 122, y + 1, 9608, fg + bg);
	game->Fill(x + 4, y + 2, x + 124, y + 3, 9608, fg + bg);
	game->Fill(x + 2, y + 4, x + 126, y + 5, 9608, fg + bg);
	game->Fill(x + 1, y + 6, x + 127, y + 13, 9608, fg + bg);
	game->Fill(x + 2, y + 14, x + 126, y + 14, 9608, fg + bg);
	game->Fill(x + 5, y + 15, x + 123, y + 16, 9608, fg + bg);
	game->Fill(x + 7, y + 17, x + 121, y + 17, 9608, fg + bg);

}


// ======================= CuncurrentThread =======================
void StateSetting::InState_FrameFlowAnimation(const COORD& _C,
	void(StateSetting::* pFunc)(const int&), const int& stateIdx)
{
	static const int _tm = 0;// 1

	if (stateIdx < 7) {
		ClearFrame(_C.X + stateIdx + 1, _C.Y);
	}

	(this->*pFunc)(stateIdx);
	game->ConsOutput();
	
	this_thread::sleep_for(std::chrono::milliseconds(_tm));
}
void StateSetting::InState_SelectedAnimation(const int& x, const int& y,
	const int& stateIdx)
{
	static const short _tm = 28;
	
	this_thread::sleep_for(std::chrono::milliseconds(_tm));
	ClearRing(x, y, FG_BLUE, BG_BLUE);

	switch (stateIdx) {
	case 1:
		Ring1(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
		break;
	case 2:
		Ring2(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
		break;
	case 3:
		Ring3(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
		break;
	case 4:
		Ring4(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
		break;
	case 5:
		Ring5(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
		break;
	case 6:
		Ring6(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
		break;
	case 7:
		Ring7(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
		break;
	case 8:
		Ring8(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
		break;
	}

	game->ConsOutput();
	
}
void StateSetting::InState_UnselectedAnimation(const int& x, const int& y,
	const int& stateIdx)
{
	static const short _tm = 28;// 30

	this_thread::sleep_for(std::chrono::milliseconds(_tm));
	ClearRing(x, y, FG_BLUE, BG_BLUE);

	switch (stateIdx) {
	case 1:
		Ring1(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
		break;
	case 2:
		Ring2(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
		break;
	case 3:
		Ring3(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
		break;
	case 4:
		Ring4(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW, FG_YELLOW, BG_YELLOW);
		break;
	case 5:
		Ring5(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
		break;
	case 6:
		Ring6(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
		break;
	case 7:
		Ring7(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
		break;
	case 8:
		Ring8(x, y, FG_DARK_GREY, BG_DARK_GREY, FG_GREY, BG_GREY);
		break;
	}

	game->ConsOutput();
	
}
void StateSetting::procThread1() {
	// rotate ring
	if (lastCharIdx == 0) {
		for (int stateIdx = 1; stateIdx <= 8; stateIdx++) {
			unique_lock<mutex> lk(mtx);

			// wait until this condition is true i.e. until ready is false
			cv.wait(lk, [&]() { return !ready; });

			InState_SelectedAnimation(C_RING_1.X, C_RING_1.Y, stateIdx);

			// set ready to true and notify waiting thread
			ready = true;
			lk.unlock();
			cv.notify_one();
		}
	}
	else {
		for (int stateIdx = 1; stateIdx <= 8; stateIdx++) {
			unique_lock<mutex> lk(mtx);

			// wait until this condition is true i.e. until ready is false
			cv.wait(lk, [&]() { return !ready; });

			InState_UnselectedAnimation(C_RING_1.X, C_RING_1.Y, stateIdx);

			// set ready to true and notify waiting thread
			ready = true;
			lk.unlock();
			cv.notify_one();
		}
	}

	// frame flow
	for (int stateIdx = 7; stateIdx >= 0; --stateIdx) {
		unique_lock<mutex> lk(mtx);

		// wait until this condition is true i.e. until ready is false
		cv.wait(lk, [&]() { return !ready; });

		InState_FrameFlowAnimation(C_FRAME_1, &StateSetting::DrawFrogFrame, stateIdx);
		
		// set ready to true and notify waiting thread
		ready = true;
		lk.unlock();
		cv.notify_one();
	}

};
void StateSetting::procThread2() {
	// rotate ring
	if (lastCharIdx == 1) {
		for (int stateIdx = 1; stateIdx <= 8; stateIdx++) {
			unique_lock<mutex> lk(mtx);

			// wait until this condition is true i.e. until ready is true
			cv.wait(lk, [&]() { return ready; });

			InState_SelectedAnimation(C_RING_2.X, C_RING_2.Y, stateIdx);

			// set ready to false and notify waiting thread
			ready = false;
			lk.unlock();
			cv.notify_one();
		}
	}
	else {
		for (int stateIdx = 1; stateIdx <= 8; stateIdx++) {
			unique_lock<mutex> lk(mtx);

			// wait until this condition is true i.e. until ready is true
			cv.wait(lk, [&]() { return ready; });

			InState_UnselectedAnimation(C_RING_2.X, C_RING_2.Y, stateIdx);

			// set ready to false and notify waiting thread
			ready = false;
			lk.unlock();
			cv.notify_one();
		}
	}

	// frame flow
	for (int stateIdx = 7; stateIdx >= 0; --stateIdx) {
		unique_lock<mutex> lk(mtx);

		// wait until this condition is true i.e. until ready is true
		cv.wait(lk, [&]() { return ready; });

		InState_FrameFlowAnimation(C_FRAME_2, &StateSetting::DrawDogFrame, stateIdx);

		// set ready to false and notify waiting thread
		ready = false;
		lk.unlock();
		cv.notify_one();
	}
};
void StateSetting::ThreadDriver(StateSetting* thr) {
	vector<thread> threads;
	threads.push_back(thread(&procThread1, thr));
	threads.push_back(thread(&procThread2, thr));

	for (auto& thread : threads)
		thread.join();

	ready = false;
	iStop = true;
};
