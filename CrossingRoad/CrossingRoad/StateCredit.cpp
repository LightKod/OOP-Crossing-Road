#include "StateCredit.h"

const int StateCredit::M_S_SRC_X0 = 4;
const int StateCredit::M_S_SRC_Y0 = 5;
const int StateCredit::M_S_SRC_X1 = 155;
const int StateCredit::M_S_SRC_Y1 = 93;

bool StateCredit::Update(float fElapsedTime) {

	DrawProjectorScreen();
	Introduction();

	InstroduceInstructor();
	InstroduceMember();

	exit(1);
	return 1;
}
bool StateCredit::OnStateEnter() {
	this->game = game;

	// clear screen
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);

	return 1;
}
bool StateCredit::OnStateExit() {
	return 0;
}


void StateCredit::InstroduceMember() {
	static const int _tm = 10;
	static const int _slpTm = 100;

	const int _x1 = M_S_SRC_X0 + 82;
	const int _y1 = M_S_SRC_Y0 + 29;

	MEMBERS(_x1, _y1, FG_RED, BG_RED);
	game->ConsOutput();
	for (int i = 1; i < 5; i += 1) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		// clear the old one
		game->Fill(_x1 + i - 1, _y1, _x1 + i + 60, _y1 + 7,
			L' ', FG_CYAN + BG_CYAN);
		// FG_CYAN + BG_CYAN
		// update 
		MEMBERS(_x1 + i, _y1, FG_RED, BG_RED);

		game->ConsOutput();
	}

	const int _x[4] = {34, 52, 35, 44};
	const int _y = _y1 + 24;

	NGUYEN_NHAT_QUANG(_x[0], _y, FG_WHITE, BG_WHITE);
	game->ConsOutput();
	for (int i = 1; i < 10; i += 1) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		// clear the old one
		game->Fill(_x[0], _y - i + 1, _x[0] + 91, _y - i + 19,
			L' ', FG_CYAN + BG_CYAN);
		// FG_CYAN + BG_CYAN
		// update 
		NGUYEN_NHAT_QUANG(_x[0], _y - i, FG_WHITE, BG_WHITE);

		game->ConsOutput();
	}

	this_thread::sleep_for(std::chrono::milliseconds(_slpTm));
	ClearOldName(_x[0], _x[0] + 91, FG_CYAN, BG_CYAN);
	this_thread::sleep_for(std::chrono::milliseconds(_slpTm / 2));

	VU_MINH_PHAT(_x[1], _y, FG_WHITE, BG_WHITE);
	game->ConsOutput();
	for (int i = 1; i < 10; i += 1) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		// clear the old one
		game->Fill(_x[1], _y - i + 1, _x[1] + 56, _y - i + 19,
			L' ', FG_CYAN + BG_CYAN);
		// FG_CYAN + BG_CYAN
		// update 
		VU_MINH_PHAT(_x[1], _y - i, FG_WHITE, BG_WHITE);

		game->ConsOutput();
	}

	this_thread::sleep_for(std::chrono::milliseconds(_slpTm));
	ClearOldName(_x[1], _x[1] + 56, FG_CYAN, BG_CYAN);
	this_thread::sleep_for(std::chrono::milliseconds(_slpTm / 2));

	NGUYEN_NGOC_VU(_x[2], _y, FG_WHITE, BG_WHITE);
	game->ConsOutput();
	for (int i = 1; i < 10; i += 1) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		// clear the old one
		game->Fill(_x[2], _y - i + 1, _x[2] + 92, _y - i + 19,
			L' ', FG_CYAN + BG_CYAN);
		// FG_CYAN + BG_CYAN
		// update 
		NGUYEN_NGOC_VU(_x[2], _y - i, FG_WHITE, BG_WHITE);

		game->ConsOutput();
	}

	this_thread::sleep_for(std::chrono::milliseconds(_slpTm));
	ClearOldName(_x[2], _x[2] + 92, FG_CYAN, BG_CYAN);
	this_thread::sleep_for(std::chrono::milliseconds(_slpTm / 2));

	TRAN_DINH_TRUNG(_x[3], _y, FG_WHITE, BG_WHITE);
	game->ConsOutput();
	for (int i = 1; i < 10; i += 1) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		// clear the old one
		game->Fill(_x[3], _y - i + 1, _x[3] + 73, _y - i + 19,
			L' ', FG_CYAN + BG_CYAN);
		// FG_CYAN + BG_CYAN
		// update 
		TRAN_DINH_TRUNG(_x[3], _y - i, FG_WHITE, BG_WHITE);

		game->ConsOutput();
	}

}
void StateCredit::ClearOldName(const int& _x0, const int& _x1,
	const short& fg, const short& bg)
{
	static const int _y = 58;
	static const int _tm = 5;

	this_thread::sleep_for(std::chrono::milliseconds(1000));
	for (int i = 1; i < 20; i += 1) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		game->Fill(_x0, _y - i + 10,
				   _x1, _y - i + 10,
					L' ', fg + bg);
		// FG_CYAN + BG_CYAN

		game->ConsOutput();
	}
}
void StateCredit::MEMBERS(const int& x, const int& y,
	const short& fg, const short& bg)
{
	M(x, y, fg, bg);
	E(x + 9, y, fg, bg);
	M(x +18, y, fg, bg);
	B(x +27, y, fg, bg);
	E(x +36, y, fg, bg);
	R(x +45, y, fg, bg);
	S(x +54, y, fg, bg);
}
void StateCredit::TRAN_DINH_TRUNG(const int& x, const int& y,
	const short& fg, const short& bg)
{
	T(x, y, fg, bg);
	R(x + 8, y, fg, bg);
	A(x + 17, y, fg, bg);
	N(x + 26, y, fg, bg);
	
	D(x	+ 41, y, fg, bg);
	I(x + 50, y, fg, bg);
	N(x + 58, y, fg, bg);
	H(x + 67, y, fg, bg);

	int offsetX = 15;
	T(x + offsetX + 1, y + 11, fg, bg);
	R(x + offsetX + 9, y + 11, fg, bg);
	U(x + offsetX + 18, y + 11, fg, bg);
	N(x + offsetX + 27, y + 11, fg, bg);
	G(x + offsetX + 36, y + 11, fg, bg);
}
void StateCredit::NGUYEN_NGOC_VU(const int& x, const int& y,
	const short& fg, const short& bg)
{
	N(x, y, fg, bg);
	G(x + 9, y, fg, bg);
	U(x + 18, y, fg, bg);
	Y(x + 27, y, fg, bg);
	E(x + 35, y, fg, bg);
	N(x + 44, y, fg, bg);

	N(x + 59, y, fg, bg);
	G(x + 68, y, fg, bg);
	O(x + 77, y, fg, bg);
	C(x + 86, y, fg, bg);

	int offsetX = 40;
	V(x + offsetX,	   y + 11, fg, bg);
	U(x + offsetX + 9, y + 11, fg, bg);
}
void StateCredit::VU_MINH_PHAT(const int& x, const int& y,
	const short& fg, const short& bg)
{
	V(x, y, fg, bg);
	U(x + 9, y, fg, bg);
	
	M(x + 24, y, fg, bg);
	I(x + 33, y, fg, bg);
	N(x + 41, y, fg, bg);
	H(x + 50, y, fg, bg);

	int offsetX = 12;
	P(x + offsetX, y + 11, fg, bg);
	H(x + offsetX + 9, y + 11, fg, bg);
	A(x + offsetX + 18, y + 11, fg, bg);
	T(x + offsetX + 27, y + 11, fg, bg);
}
void StateCredit::NGUYEN_NHAT_QUANG(const int& x, const int& y,
	const short& fg, const short& bg) 
{
	N(x, y, fg, bg);
	G(x + 9, y, fg, bg);
	U(x + 18, y, fg, bg);
	Y(x + 27, y, fg, bg);
	E(x + 35, y, fg, bg);
	N(x + 44, y, fg, bg);
	
	N(x + 59, y, fg, bg);
	H(x + 68, y, fg, bg);
	A(x + 77, y, fg, bg);
	T(x + 86, y, fg, bg);
	
	int offsetX = 26;
	Q(x + offsetX,	   y + 11, fg, bg);
	U(x + offsetX + 9, y + 11, fg, bg);
	A(x + offsetX +18, y + 11, fg, bg);
	N(x + offsetX +27, y + 11, fg, bg);
	G(x + offsetX +36, y + 11, fg, bg);
}

void StateCredit::InstroduceInstructor() {
	const int _x1 = M_S_SRC_X0 + 9;
	const int _y1 = M_S_SRC_Y0 + 29;
	const int _x2 = M_S_SRC_X0 + 33;
	const int _y2 = _y1 + 24;

	static const int _tm = 10;

	INSTRUCTOR(_x1, _y1, FG_RED, BG_RED);
	game->ConsOutput();
	for (int i = 1; i < 5; i += 1) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		// clear the old one
		game->Fill(_x1 - i + 1, _y1, _x1 - i + 85, _y1 + 7,
			L' ', FG_CYAN + BG_CYAN);
		// FG_CYAN + BG_CYAN
		// update 
		INSTRUCTOR(_x1 - i, _y1, FG_RED, BG_RED);

		game->ConsOutput();
	}

	TRUONG_TOAN_THINH(_x2, _y2, FG_WHITE, BG_WHITE);
	game->ConsOutput();
	for (int i = 1; i < 10; i += 1) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		// clear the old one
		game->Fill(_x2, _y2 - i + 1, _x2 + 91, _y2 - i + 19,
			L' ', FG_CYAN + BG_CYAN);
		
		// update 
		TRUONG_TOAN_THINH(_x2, _y2 - i, FG_WHITE, BG_WHITE);

		game->ConsOutput();
	}

	this_thread::sleep_for(std::chrono::milliseconds(500));

	// clear screen
	int tmpOffsetX = M_S_SRC_X0 + 2;
	for (int i = 0; i < 18; i += 1) {
		this_thread::sleep_for(std::chrono::milliseconds(20));

		game->Fill(tmpOffsetX, M_S_SRC_Y0 + 25, tmpOffsetX + 7, M_S_SRC_Y1 - 1,
			L' ', FG_CYAN + BG_CYAN);

		// FG_CYAN + BG_CYAN
		game->ConsOutput();
		
		tmpOffsetX += 8;
	}
}
void StateCredit::INSTRUCTOR(const int& x, const int& y,
	const short& fg, const short& bg)
{
	I(x, y, fg, bg);
	N(x + 8, y, fg, bg);
	S(x +17, y, fg, bg);
	T(x +26, y, fg, bg);
	R(x +34, y, fg, bg);
	U(x +43, y, fg, bg);
	C(x +52, y, fg, bg);
	T(x +61, y, fg, bg);
	O(x +69, y, fg, bg);
	R(x +78, y, fg, bg);
}
void StateCredit::TRUONG_TOAN_THINH(const int& x, const int& y,
	const short& fg, const short& bg) {
	T(x, y, fg, bg);
	R(x + 8, y, fg, bg);
	U(x +17, y, fg, bg);
	O(x +26, y, fg, bg);
	N(x +35, y, fg, bg);
	G(x +44, y, fg, bg);

	T(x +59, y, fg, bg);
	O(x +67, y, fg, bg);
	A(x +76, y, fg, bg);
	N(x +85, y, fg, bg);

	int offsetX = 26;
	T(x + offsetX, y + 11, fg, bg);
	H(x + offsetX + 8, y + 11, fg, bg);
	I(x + offsetX +17, y + 11, fg, bg);
	N(x + offsetX +25, y + 11, fg, bg);
	H(x + offsetX +34, y + 11, fg, bg);
}

void StateCredit::Introduction() {
	const int _x1 = M_S_SRC_X1 - 88;
	const int _y1 = M_S_SRC_Y0 + 3;
	const int _x2 = M_S_SRC_X0 + 5;
	const int _y2 = _y1 + 11;
	
	static const int _tm = 10;

	A_PROJECT(_x1, _y1, FG_WHITE, BG_WHITE);
	FROM_TEAM6(_x2, _y2, FG_WHITE, BG_WHITE);
	game->ConsOutput();
	for (int i = 2; i < 60; i+=2) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));

		// clear the old one
		game->Fill(_x1 - i + 2, _y1, _x1 - i + 76, _y1 + 7,
			L' ', FG_DARK_CYAN + BG_DARK_CYAN);
		game->Fill(_x2 + i - 2, _y2, _x2 + i + 81, _y2 + 7,
			L' ', FG_DARK_CYAN + BG_DARK_CYAN);
		
		// update 
		A_PROJECT(_x1 - i, _y1, FG_WHITE, BG_WHITE);
		FROM_TEAM6(_x2 + i, _y2, FG_WHITE, BG_WHITE);

		game->ConsOutput();
	}
}
void StateCredit::A_PROJECT(const int& x, const int& y,
	const short& fg, const short& bg)
{
	A(x, y, fg, bg);
	
	P(x + 15, y, fg, bg);
	R(x + 24, y, fg, bg);
	O(x + 33, y, fg, bg);
	J(x + 42, y, fg, bg);
	E(x + 51, y, fg, bg);
	C(x + 60, y, fg, bg);
	T(x + 69, y, fg, bg);
}
void StateCredit::FROM_TEAM6(const int& x, const int& y,
	const short& fg, const short& bg)
{
	F(x, y, fg, bg);
	R(x + 9, y, fg, bg);
	O(x +18, y, fg, bg);
	M(x +27, y, fg, bg);
	
	T(x +42, y, fg, bg);
	E(x +50, y, fg, bg);
	A(x +59, y, fg, bg);
	M(x +68, y, fg, bg);
	_6(x+77, y, fg, bg);
}

void StateCredit::DrawProjectorScreen() {
	// Khung màn chiếu
	ProjectorScreenFrame();
	game->ConsOutput();

	static const int _tm = 10;

	// Hiệu ứng màn chiếu
	this_thread::sleep_for(std::chrono::milliseconds(_tm));
	ProjectorScreen1();
	game->ConsOutput();

	this_thread::sleep_for(std::chrono::milliseconds(_tm));
	ProjectorScreen2();
	game->ConsOutput();

	this_thread::sleep_for(std::chrono::milliseconds(_tm));
	ProjectorScreen3();
	game->ConsOutput();

	this_thread::sleep_for(std::chrono::milliseconds(_tm));
	ProjectorScreen4();
	game->ConsOutput();

	this_thread::sleep_for(std::chrono::milliseconds(400));
	game->Fill(M_S_SRC_X0 + 1, M_S_SRC_Y0 + 1, M_S_SRC_X1 - 1, M_S_SRC_Y0 + 23,
		L' ', FG_DARK_CYAN + BG_DARK_CYAN);
	game->Fill(M_S_SRC_X0 + 1, M_S_SRC_Y0 + 24, M_S_SRC_X1 - 1, M_S_SRC_Y0 + 24,
		L' ', FG_WHITE + BG_WHITE);
	game->Fill(M_S_SRC_X0 + 1, M_S_SRC_Y0 + 25, M_S_SRC_X1 - 1, M_S_SRC_Y1 - 1,
		L' ', FG_CYAN + BG_CYAN);
	game->ConsOutput();
}
void StateCredit::ProjectorScreenFrame() {
	// Viền dọc
	game->DrawLine(M_S_SRC_X0 - 2, M_S_SRC_Y0 - 2, M_S_SRC_X0 - 2, M_S_SRC_Y0 - 1,
		9608, FG_BLACK + BG_BLACK);
	game->DrawLine(M_S_SRC_X1 + 2, M_S_SRC_Y0 - 2, M_S_SRC_X1 + 2, M_S_SRC_Y0 - 1,
		9608, FG_BLACK + BG_BLACK);

	// Viền ngang
	game->DrawLine(M_S_SRC_X0 - 2, M_S_SRC_Y0 - 3, M_S_SRC_X1 + 2, M_S_SRC_Y0 - 3,
		9608, FG_BLACK + BG_BLACK);
	game->DrawLine(M_S_SRC_X0 - 2, M_S_SRC_Y0, M_S_SRC_X1 + 2, M_S_SRC_Y0,
		9608, FG_BLACK + BG_BLACK);

	// Tô màu nền
	game->Fill(M_S_SRC_X0 - 1, M_S_SRC_Y0 - 2, M_S_SRC_X1 + 1, M_S_SRC_Y0 - 1,
		L' ', FG_GREY + BG_GREY);//FG_GREY + BG_GREY
}
void StateCredit::ProjectorScreen1() {
	static const int y0 = M_S_SRC_Y0 + 1;
	static const int y1 = M_S_SRC_Y1 / 4;

	// Vẽ viền dọc
	game->DrawLine(M_S_SRC_X0, y0, M_S_SRC_X0, y1,
		9608, FG_BLACK + BG_BLACK);
	game->DrawLine(M_S_SRC_X1, y0, M_S_SRC_X1, y1,
		9608, FG_BLACK + BG_BLACK);

	// Vẽ viền ngang
	game->DrawLine(M_S_SRC_X0, y1, M_S_SRC_X1, y1,
		9608, FG_BLACK + BG_BLACK);

	// Tô màu nền
	game->Fill(M_S_SRC_X0 + 1, y0, M_S_SRC_X1 - 1, y1 - 1,
		L' ', FG_GREY + BG_GREY);
}
void StateCredit::ProjectorScreen2() {
	static const int y0 = M_S_SRC_Y1 / 4;
	static const int y1 = M_S_SRC_Y1 / 4 * 2;

	// Vẽ viền dọc
	game->DrawLine(M_S_SRC_X0, y0, M_S_SRC_X0, y1,
		9608, FG_BLACK + BG_BLACK);
	game->DrawLine(M_S_SRC_X1, y0, M_S_SRC_X1, y1,
		9608, FG_BLACK + BG_BLACK);

	// Vẽ viền ngang
	game->DrawLine(M_S_SRC_X0, y1, M_S_SRC_X1, y1,
		9608, FG_BLACK + BG_BLACK);

	// Tô màu nền
	game->Fill(M_S_SRC_X0 + 1, y0, M_S_SRC_X1 - 1, y1 - 1,
		L' ', FG_GREY + BG_GREY);
}
void StateCredit::ProjectorScreen3() {
	static const int y0 = M_S_SRC_Y1 / 4 * 2;
	static const int y1 = M_S_SRC_Y1 / 4 * 3;

	// Vẽ viền dọc
	game->DrawLine(M_S_SRC_X0, y0, M_S_SRC_X0, y1,
		9608, FG_BLACK + BG_BLACK);
	game->DrawLine(M_S_SRC_X1, y0, M_S_SRC_X1, y1,
		9608, FG_BLACK + BG_BLACK);

	// Vẽ viền ngang
	game->DrawLine(M_S_SRC_X0, y1, M_S_SRC_X1, y1,
		9608, FG_BLACK + BG_BLACK);

	// Tô màu nền
	game->Fill(M_S_SRC_X0 + 1, y0, M_S_SRC_X1 - 1, y1 - 1,
		L' ', FG_GREY + BG_GREY);
}
void StateCredit::ProjectorScreen4() {
	static const int y0 = M_S_SRC_Y1 / 4 * 3;
	static const int y1 = M_S_SRC_Y1;

	// Vẽ viền dọc
	game->DrawLine(M_S_SRC_X0, y0, M_S_SRC_X0, y1,
		9608, FG_BLACK + BG_BLACK);
	game->DrawLine(M_S_SRC_X1, y0, M_S_SRC_X1, y1,
		9608, FG_BLACK + BG_BLACK);

	// Vẽ viền ngang
	game->DrawLine(M_S_SRC_X0 - 2, y1, M_S_SRC_X1 + 2, y1,
		9608, FG_BLACK + BG_BLACK);

	// Tô màu nền
	game->Fill(M_S_SRC_X0 + 1, y0, M_S_SRC_X1 - 1, y1 - 1,
		L' ', FG_GREY + BG_GREY);
}

// Pixel Draw Tool
void StateCredit::A(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x + 2, y, x + 4, y, 9608, fg + bg);
	game->DrawLine(x + 1, y + 1, x + 2, y + 1, 9608, fg + bg);
	game->DrawLine(x + 4, y + 1, x + 5, y + 1, 9608, fg + bg);
	game->DrawLine(x + 2, y + 4, x + 4, y + 4, 9608, fg + bg);
	game->Fill(x, y+2,x+1,y+6,9608, fg + bg);
	game->Fill(x + 5, y+2,x+6,y+6,9608, fg + bg);

	// Vẽ bóng
	game->Draw(x + 3, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 2, y + 2, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 4, y + 2, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 2, y + 5, x + 4, y + 5, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x, y + 7, x + 1, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 5, y + 7, x + 6, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::P(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x, y, x + 5, y, 9608, fg + bg);
	game->DrawLine(x, y + 4, x + 5, y + 4, 9608, fg + bg);
	game->Fill(x, y+1, x+1,y+3,9608, fg + bg);
	game->Fill(x + 5, y+1, x+6,y+3,9608, fg + bg);
	game->Fill(x, y + 5, x + 1, y + 6, 9608, fg + bg);

	// Vẽ bóng
	game->Draw(x + 6, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x, y + 7, x + 1, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x+2, y + 1, x + 4, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x+2, y + 5, x + 5, y + 5, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::R(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x, y, x + 5, y, 9608, fg + bg);
	game->DrawLine(x, y + 4, x + 4, y + 4, 9608, fg + bg);
	game->DrawLine(x + 4, y + 3, x + 6, y + 3, 9608, fg + bg);
	game->DrawLine(x + 3, y + 5, x + 5, y + 5, 9608, fg + bg);
	game->DrawLine(x + 4, y + 6, x + 6, y + 6, 9608, fg + bg);
	
	game->Fill(x, y + 1, x + 1, y + 3, 9608, fg + bg);
	game->Fill(x + 5, y + 1, x + 6, y + 2, 9608, fg + bg);
	game->Fill(x, y + 5, x + 1, y + 6, 9608, fg + bg);

	// Vẽ bóng
	game->Draw(x + 2, y + 5, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 3, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 2, y + 1, x + 4, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x, y + 7, x + 1, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 4, y + 7, x + 6, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 5, y + 4, x + 6, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::O(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x + 1, y, x + 5, y, 9608, fg + bg);
	game->DrawLine(x + 1, y + 6, x + 5, y + 6, 9608, fg + bg);
	game->Fill(x, y + 1, x + 1, y + 5, 9608, fg + bg);
	game->Fill(x + 5, y + 1, x + 6, y + 5, 9608, fg + bg);

	// Vẽ bóng
	game->Draw(x, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 6, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 1, y + 7, x + 5, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 2, y + 1, x + 4, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::J(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x, y + 5, x + 1, y + 5, 9608, fg + bg);
	game->DrawLine(x + 1, y + 6, x + 5, y + 6, 9608, fg + bg);
	game->Fill(x + 5, y, x + 6, y + 5, 9608, fg + bg);

	// Vẽ bóng
	game->Draw(x, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 6, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 1, y + 7, x + 5, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::E(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x, y, x + 6, y, 9608, fg + bg);
	game->DrawLine(x, y + 6, x + 6, y + 6, 9608, fg + bg);
	game->DrawLine(x, y + 3, x + 4, y + 3, 9608, fg + bg);
	game->Fill(x, y + 1, x + 1, y + 2, 9608, fg + bg);
	game->Fill(x, y + 4, x + 1, y + 5, 9608, fg + bg);

	// Vẽ bóng
	game->DrawLine(x, y + 7, x + 6, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 2, y + 4, x + 4, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 2, y + 1, x + 6, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::C(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x + 2, y, x + 5, y, 9608, fg + bg);
	game->DrawLine(x + 1, y + 1, x + 2, y + 1, 9608, fg + bg);
	game->DrawLine(x + 5, y + 1, x + 6, y + 1, 9608, fg + bg);
	game->DrawLine(x + 2, y + 6, x + 5, y + 6, 9608, fg + bg);
	game->DrawLine(x + 1, y + 5, x + 2, y + 5, 9608, fg + bg);
	game->DrawLine(x + 5, y + 5, x + 6, y + 5, 9608, fg + bg);
	game->Fill(x, y + 2, x + 1, y + 4, 9608, fg + bg);

	// Vẽ bóng
	game->DrawLine(x + 3, y + 1, x + 4, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 5, y + 2, x + 6, y + 2, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 2, y + 7, x + 5, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x, y + 5, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 1, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 6, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 2, y + 2, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::T(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x, y, x + 5, y, 9608, fg + bg);
	game->Fill(x + 2, y + 1, x + 3, y + 6, 9608, fg + bg);

	// Vẽ bóng
	game->DrawLine(x, y + 1, x + 1, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 4, y + 1, x + 5, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 2, y + 7, x + 3, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::F(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x, y, x + 6, y, 9608, fg + bg);
	game->DrawLine(x, y + 3, x + 4, y + 3, 9608, fg + bg);
	game->Fill(x, y + 1, x + 1, y + 6, 9608, fg + bg);

	// Vẽ bóng
	game->DrawLine(x + 2, y + 1, x + 6, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 2, y + 4, x + 4, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x, y + 7, x + 1, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::M(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x + 2, y + 1, x + 2, y + 3, 9608, fg + bg);
	game->DrawLine(x + 3, y + 2, x + 3, y + 4, 9608, fg + bg);
	game->DrawLine(x + 4, y + 1, x + 4, y + 3, 9608, fg + bg);
	game->Fill(x, y, x + 1, y + 6, 9608, fg + bg);
	game->Fill(x + 5, y, x + 6, y + 6, 9608, fg + bg);

	//// Vẽ bóng
	game->DrawLine(x, y + 7, x + 1, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 5, y + 7, x + 6, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x+2,y+4, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x+3,y+5, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x+4,y+4, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::_6(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x + 2, y, x + 5, y, 9608, fg + bg);
	game->DrawLine(x + 1, y + 1, x + 2, y + 1, 9608, fg + bg);
	game->DrawLine(x + 2, y + 3, x + 5, y + 3, 9608, fg + bg);
	game->DrawLine(x + 1, y + 6, x + 5, y + 6, 9608, fg + bg);
	game->Fill(x, y + 2, x + 1, y + 5, 9608, fg + bg);
	game->Fill(x + 5, y + 4, x + 6, y + 5, 9608, fg + bg);

	// Vẽ bóng
	game->DrawLine(x + 3, y + 1, x + 5, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 2, y + 4, x + 4, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 1, y + 7, x + 5, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 6, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 2, y + 2, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::U(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x + 1, y + 6, x + 5, y + 6, 9608, fg + bg);
	game->Fill(x, y, x + 1, y + 5, 9608, fg + bg);
	game->Fill(x + 5, y, x + 6, y + 5, 9608, fg + bg);

	// Vẽ bóng
	game->Draw(x, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 6, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 1, y + 7, x + 5, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::N(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x + 2, y + 1, x + 2, y + 3, 9608, fg + bg);
	game->DrawLine(x + 3, y + 2, x + 3, y + 4, 9608, fg + bg);
	game->DrawLine(x + 4, y + 3, x + 4, y + 5, 9608, fg + bg);
	game->Fill(x, y, x + 1, y + 6, 9608, fg + bg);
	game->Fill(x + 5, y, x + 6, y + 6, 9608, fg + bg);

	//// Vẽ bóng
	game->DrawLine(x, y + 7, x + 1, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 5, y + 7, x + 6, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 2, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 3, y + 5, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 4, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::G(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x + 2, y, x + 6, y, 9608, fg + bg);
	game->DrawLine(x + 1, y + 1, x + 2, y + 1, 9608, fg + bg);
	game->DrawLine(x + 2, y + 6, x + 6, y + 6, 9608, fg + bg);
	game->DrawLine(x + 1, y + 5, x + 2, y + 5, 9608, fg + bg);
	game->DrawLine(x + 4, y + 3, x + 6, y + 3, 9608, fg + bg);
	game->Fill(x, y + 2, x + 1, y + 4, 9608, fg + bg);
	game->Fill(x + 5, y + 4, x + 6, y + 5, 9608, fg + bg);

	// Vẽ bóng
	game->DrawLine(x + 2, y + 7, x + 6, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 3, y + 1, x + 6, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x, y + 5, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 1, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 2, y + 2, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 4, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::H(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x + 2, y + 3, x + 4, y + 3, 9608, fg + bg);
	game->Fill(x, y, x + 1, y + 6, 9608, fg + bg);
	game->Fill(x + 5, y, x + 6, y + 6, 9608, fg + bg);

	// Vẽ bóng
	game->DrawLine(x + 2, y + 4, x + 4, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x, y + 7, x + 1, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 5, y + 7, x + 6, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::I(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x, y, x + 5, y, 9608, fg + bg);
	game->DrawLine(x, y + 6, x + 5, y + 6, 9608, fg + bg);
	game->Fill(x + 2, y + 1, x + 3, y + 5, 9608, fg + bg);

	// Vẽ bóng
	game->DrawLine(x, y + 1, x + 1, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 4, y + 1, x + 5, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x, y + 7, x + 5, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::S(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x + 1, y, x + 4, y, 9608, fg + bg);
	game->DrawLine(x + 4, y + 1, x + 5, y + 1, 9608, fg + bg);
	game->DrawLine(x + 1, y + 3, x + 5, y + 3, 9608, fg + bg);
	game->DrawLine(x + 1, y + 6, x + 5, y + 6, 9608, fg + bg);
	game->DrawLine(x, y + 5, x + 1, y + 5, 9608, fg + bg);
	game->Fill(x, y + 1, x + 1, y + 2, 9608, fg + bg);
	game->Fill(x + 5, y + 4, x + 6, y + 5, 9608, fg + bg);

	// Vẽ bóng
	game->DrawLine(x + 1, y + 7, x + 5, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 1, y + 4, x + 4, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 2, y + 1, x + 3, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 4, y + 2, x + 5, y + 2, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x, y + 3, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 6, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::B(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x+ 1, y,	  x + 5, y, 9608, fg + bg);
	game->DrawLine(x+ 1, y+3, x + 5, y+3, 9608, fg + bg);
	game->DrawLine(x+ 1, y+6, x + 5, y+6, 9608, fg + bg);
	game->DrawLine(x, y, x, y + 6, 9608, fg + bg);
	game->Fill(x + 5, y + 1, x + 6, y + 2, 9608, fg + bg);
	game->Fill(x + 5, y + 4, x + 6, y + 5, 9608, fg + bg);

	// Vẽ bóng
	game->DrawLine(x + 1, y + 1, x + 4, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 1, y + 4, x + 4, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x, y + 7, x + 5, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 6, y+3, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 6, y+6, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::Y(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x + 1, y + 3, x + 4, y + 3, 9608, fg + bg);
	game->Fill(x, y, x + 1, y + 2, 9608, fg + bg);
	game->Fill(x + 4, y, x + 5, y + 2, 9608, fg + bg);
	game->Fill(x + 2, y + 4, x + 3, y + 6, 9608, fg + bg);

	// Vẽ bóng
	game->DrawLine(x + 2, y + 7, x + 3, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x, y + 3, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 1, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 5, y + 3, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 4, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::Q(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x + 1, y, x + 5, y, 9608, fg + bg);
	game->DrawLine(x + 1, y + 6, x + 4, y + 6, 9608, fg + bg);
	game->DrawLine(x + 4, y + 5, x + 5, y + 5, 9608, fg + bg);
	game->DrawLine(x + 3, y + 4, x + 6, y + 4, 9608, fg + bg);
	game->Draw(x + 6, y + 6, 9608, fg + bg);
	game->Fill(x, y + 1, x + 1, y + 5, 9608, fg + bg);
	game->Fill(x + 5, y + 1, x + 6, y + 3, 9608, fg + bg);

	// Vẽ bóng
	game->DrawLine(x + 2, y + 1, x + 4, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 1, y + 7, x + 4, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 5, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 6, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 6, y + 5, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 3, y + 5, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::V(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x, y, x, y + 3, 9608, fg + bg);
	game->DrawLine(x + 1, y, x + 1, y + 4, 9608, fg + bg);
	game->DrawLine(x + 2, y + 3, x + 2, y + 5, 9608, fg + bg);
	game->DrawLine(x + 3, y + 4, x + 3, y + 6, 9608, fg + bg);
	game->DrawLine(x + 4, y + 3, x + 4, y + 5, 9608, fg + bg);
	game->DrawLine(x + 6, y, x + 6, y + 3, 9608, fg + bg);
	game->DrawLine(x + 5, y, x + 5, y + 4, 9608, fg + bg);

	// Vẽ bóng
	game->Draw(x, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 1, y + 5, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 2, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 3, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 4, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 5, y + 5, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 6, y + 4, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
void StateCredit::D(const int& x, const int& y,
	const short& fg, const short& bg)
{
	// Vẽ chữ
	game->DrawLine(x, y, x, y + 6, 9608, fg + bg);

	game->DrawLine(x + 1, y,	 x + 4, y, 9608, fg + bg);
	game->DrawLine(x + 1, y + 6, x + 4, y + 6, 9608, fg + bg);
	game->DrawLine(x + 4, y + 1, x + 5, y + 1, 9608, fg + bg);
	game->DrawLine(x + 4, y + 5, x + 5, y + 5, 9608, fg + bg);
	game->Fill(x + 5, y + 2, x + 6, y + 4, 9608, fg + bg);

	// Vẽ bóng
	game->DrawLine(x, y + 7, x + 4, y + 7, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 1, y + 1, x + 3, y + 1, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 5, y + 6, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 6, y + 5, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->Draw(x + 4, y + 2, 9608, FG_DARK_GREY + BG_DARK_GREY);
}
