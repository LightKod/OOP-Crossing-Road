#include "StateSetting.h"

bool StateSetting::Update(float fElapsedTime) {
	//MousePointer(50, 50);
	//Clicking(50, 50);
	
	while (1) {
	SelectedAnimation(10, 10);
	this_thread::sleep_for(std::chrono::milliseconds(1000));

	UnselectedAnimation(10, 10);
	this_thread::sleep_for(std::chrono::milliseconds(1000));

	}

	//SelectedFrame(10, 10);
	//UnselectedFrame(50,50);

	//Frog(10, 10, FG_BLACK, BG_BLACK);

	game->DrawLine(22, 5, 127, 5, 9608);



	DrawTitle(16, 10);

	game->ConsOutput();

	exit(1);
	return 1;
}
bool StateSetting::OnStateEnter() {
	this->game = game;

	// clear screen
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);

	return 1;
}
bool StateSetting::OnStateExit() {

	return 1;
}

void StateSetting::DrawTitle(const int& x, const int& y) {
	TitleBorder(x, y, FG_DARK_YELLOW, BG_DARK_YELLOW);
	TitleBackground(x, y, FG_YELLOW, BG_YELLOW);
	string2Pixel(L"SELECT YOUR CHARACTER", x + 12, y + 8, FG_BLACK, BG_YELLOW);
}
void StateSetting::TitleBorder(const int& x, const int& y,
	const short& fg, const short& bg)
{
	game->DrawLine(x, y + 6, x, y +13, 9608, fg + bg);
	game->Fill(x, y + 4, x + 1, y + 5, 9608, fg + bg);
	game->Fill(x + 1, y + 1, x + 3, y + 3, 9608, fg + bg);
	game->Fill(x + 4, y, x + 5, y + 1, 9608, fg + bg);
	game->Fill(x, y +14, x + 1, y +15, 9608, fg + bg);
	game->Fill(x + 2, y +15, x + 4, y +17, 9608, fg + bg);
	game->Fill(x + 5, y +17, x + 6, y +18, 9608, fg + bg);

	game->DrawLine(x + 6, y   , x +122, y , 9608, fg + bg);
	game->DrawLine(x + 7, y +18, x +121, y + 18, 9608, fg + bg);

	game->Fill(x+123, y , x +124, y + 1, 9608, fg + bg);
	game->Fill(x+125, y + 1, x +127, y + 3, 9608, fg + bg);
	game->Fill(x+127, y + 4, x +128, y + 5, 9608, fg + bg);
	game->Fill(x+122, y +17, x +123, y +18, 9608, fg + bg);
	game->Fill(x+124, y +15, x +126, y +17, 9608, fg + bg);
	game->Fill(x+127, y +14, x +128, y +15, 9608, fg + bg);
	game->DrawLine(x+128, y + 6, x+128, y + 13, 9608, fg + bg);

}
void StateSetting::TitleBackground(const int& x, const int& y,
	const short& fg, const short& bg)
{
	game->Fill(x + 6, y + 1, x + 122, y + 1, 9608, fg + bg);
	game->Fill(x + 4, y + 2, x + 124, y + 3, 9608, fg + bg);
	game->Fill(x + 2, y + 4, x + 126, y +  5, 9608, fg + bg);
	game->Fill(x + 1, y + 6, x + 127, y + 13, 9608, fg + bg);
	game->Fill(x + 2, y +14, x + 126, y + 14, 9608, fg + bg);
	game->Fill(x + 5, y +15, x + 123, y + 16, 9608, fg + bg);
	game->Fill(x + 7, y +17, x + 121, y + 17, 9608, fg + bg);

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


void StateSetting::MousePointer(const int& x, const int& y) {
	// vẽ viền ngoải
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
void StateSetting::Clicking(const int& x, const int& y) {
	game->DrawLine(x - 4, y, x - 3, y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x, y - 4, x, y - 3, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x - 4, y - 4, x - 2, y - 2, 9608, FG_BLACK + BG_BLACK);
}


void StateSetting::SelectedAnimation(const int& x, const int& y) {
	static const short _tm = 100;

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
	game->Fill(x, y, x + 9, y + 9, L' ', COLOUR::BG_BLUE);
}
