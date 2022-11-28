#include "StatePlay.h"

bool StatePlay::OnStateEnter() {
	if (CrossingRoadGame::s_CharIdx == 0) {
		pPlayer = new Frog(game);
	}
	else if (CrossingRoadGame::s_CharIdx == 1) {
		pPlayer = new Dog(game);
	}
	pPlayer->p_State = Player::PLAYER_STATE::ALIVE;

	GenerateNewLevel();

	return true;
}
bool StatePlay::OnStateExit() {
	return true;
}

bool StatePlay::Update(float fElapsedTime) {
	if (pPlayer->GetY() == 0) {
		NextLevel();
	}

	HandleInput();
	//UpdateGameScreen();
	if (pause) return true;
	UpdateGameState(fElapsedTime);

	if (pPlayer->CheckPlayerState()) {
		pPlayer->SetDefaultPosition();
		pPlayer->p_State = Player::PLAYER_STATE::DEAD;
		game->SetState(new StateDead(game, pPlayer));
	}
	else  {
		UpdateCollisionMatrix();
		UpdateGameScreen();
	}

	return true;
}
void StatePlay::UpdateCollisionMatrix() {
	game->ClearCollsionMatrix();

	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->SetCollisionMatrix();
	}
	//THEM MAY CAI SET COLLSION CUA MAY CAI OBJECT VAO
}

void StatePlay::UpdateGameScreen() {
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Draw();
	}
	
	// THEM MAY CAI DRAW CUA MAY CAI OBJECT VAO
	pPlayer->Draw();

	if (pause) {
		string2Pixel(L"PAUSE", 0, 0, FG_WHITE, BG_BLUE);
	}

	string2Pixel(to_wstring(level), 140, 0, FG_WHITE, BG_BLUE);
}

void StatePlay::NextLevel() {
	UpdateGameScreen();
	game->ConsOutput();

	LevelUp();
	ClearCurrentLevel();
	GenerateNewLevel();
	pPlayer->ResetPosition();
	level++;
}

void StatePlay::GenerateNewLevel() {
	unsigned int seed = time(NULL);
	int laneSeedCount = sizeof(laneSeed);
	
	srand(seed);
	//Starting Lane
	lanes.push_back(new RestLane(game, 0));
	for (int i = 0; i < 10; i++) {
		int random = rand() % laneSeedCount;
		int row = 8 * (i + 1);
		switch (laneSeed[random]) {
		case 'R':
			lanes.push_back(new Road(game, row));
			break;
		case 'W':
			lanes.push_back(new River(game, row));
			break;
		default:
			lanes.push_back(new Road(game, row));
			break;
		}
	}
	//Ending Lane
	lanes.push_back(new RestLane(game, 88));

}

void StatePlay::ClearCurrentLevel() {
	while (!lanes.empty()) {
		Lane* l = lanes.back();
		lanes.pop_back();
		delete l;
	}
	
}

void StatePlay::UpdateGameState(float fElapsedTime) {
	if (!pPlayer->CheckPlayerState()) {
		for (int i = 0; i < lanes.size(); i++) {
			lanes[i]->Update(fElapsedTime);
		}
		pPlayer->Update(fElapsedTime);
	}
	
}


void StatePlay::HandleInput() {
	if (game->GetKey(VK_SPACE).bPressed) {
		//pause = !pause;
		NextLevel();
	}
	if (game->GetKey(VK_CAPITAL).bReleased) {
		ExportGameData();
	}
}

Data* StatePlay::ExportGameData() {
	Data* data = new Data();
	for (int i = 0; i < 12; i++) {
		data->SetLaneData(i, lanes[i]->GetData());
	}
	data->SaveData(L"text");
	return data;
}

void StatePlay::LevelUp(const int& x, const int& y) {
	// Vẽ cổng
	game->Fill(0, y -  4, game->ScreenWidth(), y -  4, L' ', COLOUR::BG_DARK_YELLOW);
	game->Fill(0, y + 19, game->ScreenWidth(), y + 19, L' ', COLOUR::BG_DARK_YELLOW);
	game->Fill(0, y -  3, game->ScreenWidth(), y + 18, L' ', COLOUR::BG_YELLOW);

	static const short _tm = 0;
	static const int step = 2;
	for (int i = 0; i <= 236; i += step) {
		this_thread::sleep_for(std::chrono::milliseconds(_tm));
		
		LVUP_Border(x + i, y);
		LVUP_TopColor(x + i, y, FG_CYAN, BG_CYAN);// FG_BLUE, BG_BLUE
		LVUP_BotColor(x + i, y, FG_BLUE, BG_BLUE);// FG_DARK_CYAN, BG_DARK_CYAN
		LVUP_MidLine(x + i, y);
		game->ConsOutput();

		if (i == 116) {
			this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		game->Fill(x + i, y, x + 75 + i, y + 14, L' ', COLOUR::BG_YELLOW);
	}

}
void StatePlay::LVUP_Border(const int& x, const int& y) {
	// decor
	game->Draw(x + 2, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 4, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 8, y + 2, x +12, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +14, y + 2, x +28, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +31, y + 2, x +47, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x +60, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +63, y + 2, x +67, y + 2, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +66, y + 4, x +72, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +68, y + 6, x +70, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +67, y +10, x +70, y +10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +72, y +10, x +74, y +10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +66, y +12, x +71, y +12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +68, y +14, x +69, y +14, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 75, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 74, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 73, y +12, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 62, y +14, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 56, y +14, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +34, y + 14, x +52, y + 14, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +14, y + 14, x +30, y + 14, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 4, y + 14, x + 8, y + 14, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 2, y +14, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x +10, y +14, 9608, FG_BLACK + BG_BLACK);

	// +
	game->DrawLine(x, y + 6, x, y +10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 8, y + 6, x + 8, y +10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y + 4, x + 6, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 2, y +12, x + 6, y +12, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x + 1, y + 5, x + 2, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x + 1, y +10, x + 2, y +11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x + 6, y + 5, x + 7, y + 6, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x + 6, y +10, x + 7, y +11, 9608, FG_BLACK + BG_BLACK);

	game->DrawLine(x+13, y + 5, x+13, y +11, 9608, FG_BLACK + BG_BLACK);
	int offsetX = 0;

	// L 
	game->DrawLine(x + 14 + offsetX, y + 4, x + 18 + offsetX, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 14 + offsetX, y +12, x + 19 + offsetX, y +12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 14 + offsetX, y + 5, x + 14 + offsetX, y +11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x + 18 + offsetX, y + 5, x + 19 + offsetX, y +10, 9608, FG_BLACK + BG_BLACK);

	// E
	game->DrawLine(x + 20 + offsetX, y + 6, x + 20 + offsetX, y +10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 22 + offsetX, y + 4, x + 25 + offsetX, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 22 + offsetX, y +12, x + 25 + offsetX, y +12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 25 + offsetX, y + 6, x + 25 + offsetX, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 25 + offsetX, y + 9, x + 25 + offsetX, y +10, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x + 20 + offsetX, y + 4, x + 21 + offsetX, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x + 20 + offsetX, y +11, x + 21 + offsetX, y +12, 9608, FG_BLACK + BG_BLACK);

	// V
	game->DrawLine(x +26, y + 4, x +26, y +12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +27, y + 4, x +30, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +32, y + 4, x +34, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +34, y + 8, x +34, y +11, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +28, y +12, x +33, y +12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +31, y + 8, x +31, y + 9, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +27, y + 8, x +27, y +11, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x +28, y +11, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x +33, y +11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x +30, y + 5, x +32, y + 7, 9608, FG_BLACK + BG_BLACK);

	// E
	offsetX = 15;
	game->DrawLine(x + 20 + offsetX, y + 6, x + 20 + offsetX, y + 10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 22 + offsetX, y + 4, x + 25 + offsetX, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 22 + offsetX, y + 12, x + 25 + offsetX, y + 12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 25 + offsetX, y + 6, x + 25 + offsetX, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 25 + offsetX, y + 9, x + 25 + offsetX, y + 10, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x + 20 + offsetX, y + 4, x + 21 + offsetX, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x + 20 + offsetX, y + 11, x + 21 + offsetX, y + 12, 9608, FG_BLACK + BG_BLACK);

	// L 
	offsetX = 27;
	game->DrawLine(x + 14 + offsetX, y + 4, x + 18 + offsetX, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 14 + offsetX, y + 12, x + 19 + offsetX, y + 12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x + 14 + offsetX, y + 5, x + 14 + offsetX, y + 11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x + 18 + offsetX, y + 5, x + 19 + offsetX, y + 10, 9608, FG_BLACK + BG_BLACK);

	// space
	game->Fill(x +47, y + 5, x +49, y +11, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x +47, y +12, 9608, FG_BLACK + BG_BLACK);

	// U
	game->DrawLine(x +50, y + 4, x +50, y +10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +54, y + 4, x +54, y + 9, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +49, y + 3, x +52, y, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +53, y + 1, x +56, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +52, y +12, x +56, y +12, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x +55, y + 4, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x +56, y +11, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x +50, y +11, x +51, y +12, 9608, FG_BLACK + BG_BLACK);

	// P
	game->DrawLine(x +57, y + 4, x +57, y+12, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +58, y + 4, x +63, y+ 4, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +64, y + 5, x +64, y+ 9, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +63, y + 9, x +63, y+10, 9608, FG_BLACK + BG_BLACK);
	game->DrawLine(x +58, y +12, x +61, y +12, 9608, FG_BLACK + BG_BLACK);
	game->Fill(x +61, y +10, x +62, y +11, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 63, y + 5, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 61, y + 7, 9608, FG_BLACK + BG_BLACK);
	game->Draw(x + 58, y + 5, 9608, FG_BLACK + BG_BLACK);

}
void StatePlay::LVUP_TopColor(const int& x, const int& y, 
	const short& fg, const short& bg) 
{
	// +
	game->Fill(x + 3, y + 5, x + 5, y + 6, 9608, fg + bg);
	game->DrawLine(x + 1, y + 7, x + 7, y + 7, 9608, fg + bg);
	//game->Draw(x + 2, y + 2, 9608, FG_BLACK + BG_BLACK);
	//game->Draw(x + 4, y + 2, 9608, FG_BLACK + BG_BLACK);

	int offsetX = 0;

	// L
	game->Fill(x + 15 + offsetX, y + 5, x + 17 + offsetX, y + 7, 9608, fg + bg);

	// E
	game->DrawLine(x + 22 + offsetX, y + 5, x + 25 + offsetX, y + 5, 9608, fg + bg);
	game->Fill(x + 21 + offsetX, y + 6, x + 24 + offsetX, y + 7, 9608, fg + bg);

	// V
	game->Fill(x + 27, y + 5, x + 29, y + 7, 9608, fg + bg);
	game->Fill(x + 33, y + 5, x + 34, y + 7, 9608, fg + bg);

	// E
	offsetX = 15;
	game->DrawLine(x + 22 + offsetX, y + 5, x + 25 + offsetX, y + 5, 9608, fg + bg);
	game->Fill(x + 21 + offsetX, y + 6, x + 24 + offsetX, y + 7, 9608, fg + bg);
	
	// L 
	offsetX = 27;
	game->Fill(x + 15 + offsetX, y + 5, x + 17 + offsetX, y + 7, 9608, fg + bg);

	// U
	game->Fill(x + 51, y + 4, x + 53, y + 7, 9608, fg + bg);
	game->Fill(x + 55, y + 5, x + 56, y + 7, 9608, fg + bg);
	game->DrawLine(x + 50, y + 3, x + 54, y + 3, 9608, fg + bg);
	game->DrawLine(x + 51, y + 2, x + 53, y + 2, 9608, fg + bg);
	game->Draw(x + 52, y + 1, 9608, fg + bg);

	// P
	game->DrawLine(x + 59, y + 5, x + 62, y + 5, 9608, fg + bg);
	game->DrawLine(x + 58, y + 6, x + 63, y + 6, 9608, fg + bg);
	game->DrawLine(x + 58, y + 7, x + 60, y + 7, 9608, fg + bg);
	game->DrawLine(x + 62, y + 7, x + 63, y + 7, 9608, fg + bg);

}
void StatePlay::LVUP_BotColor(const int& x, const int& y, 
	const short& fg, const short& bg) 
{
	// +
	game->Fill(x + 3, y +10, x + 5, y +11, 9608, fg + bg);
	game->DrawLine(x + 1, y + 9, x + 7, y + 9, 9608, fg + bg);

	int offsetX = 0;

	// L
	game->Fill(x + 15 + offsetX, y + 9, x + 17 + offsetX, y +10, 9608, fg + bg);
	game->DrawLine(x + 15 + offsetX, y +11, x + 19 + offsetX, y +11, 9608, fg + bg);

	// E
	game->Fill(x + 21 + offsetX, y + 9, x + 24 + offsetX, y + 10, 9608, fg + bg);
	game->DrawLine(x + 22 + offsetX, y + 11, x + 25 + offsetX, y + 11, 9608, fg + bg);

	// V
	game->DrawLine(x + 28, y + 9, x + 30, y + 9, 9608, fg + bg);
	game->DrawLine(x + 32, y + 9, x + 33, y + 9, 9608, fg + bg);
	game->DrawLine(x + 28, y +10, x + 33, y +10, 9608, fg + bg);
	game->DrawLine(x + 29, y +11, x + 32, y +11, 9608, fg + bg);

	// E
	offsetX = 15;
	game->Fill(x + 21 + offsetX, y + 9, x + 24 + offsetX, y + 10, 9608, fg + bg);
	game->DrawLine(x + 22 + offsetX, y + 11, x + 25 + offsetX, y + 11, 9608, fg + bg);

	// L 
	offsetX = 27;
	game->Fill(x + 15 + offsetX, y + 9, x + 17 + offsetX, y + 10, 9608, fg + bg);
	game->DrawLine(x + 15 + offsetX, y + 11, x + 19 + offsetX, y + 11, 9608, fg + bg);

	// U
	game->DrawLine(x + 51, y + 9, x + 53, y + 9, 9608, fg + bg);
	game->DrawLine(x + 55, y + 9, x + 56, y + 9, 9608, fg + bg);
	game->DrawLine(x + 51, y +10, x + 56, y +10, 9608, fg + bg);
	game->DrawLine(x + 52, y +11, x + 55, y +11, 9608, fg + bg);

	// P
	game->DrawLine(x + 58, y + 9, x + 62, y + 9, 9608, fg + bg);
	game->Fill(x + 58, y + 10, x + 60, y + 11, 9608, fg + bg);

}
void StatePlay::LVUP_MidLine(const int& x, const int& y) {
	static const short fg = FG_WHITE;
	static const short bg = BG_WHITE;

	// +
	game->DrawLine(x + 1, y + 8, x + 7, y + 8, 9608, fg  + bg);
	
	int offsetX = 0;

	// L
	game->DrawLine(x + 15 + offsetX, y + 8, x + 17 + offsetX, y + 8, 9608, fg  + bg);

	// E
	game->DrawLine(x + 21 + offsetX, y + 8, x + 25 + offsetX, y + 8, 9608, fg  + bg);

	// V
	game->DrawLine(x + 28, y + 8, x + 30, y + 8, 9608, fg  + bg);
	game->DrawLine(x + 32, y + 8, x + 33, y + 8, 9608, fg  + bg);

	// E
	offsetX = 15;
	game->DrawLine(x + 21 + offsetX, y + 8, x + 25 + offsetX, y + 8, 9608, fg + bg);

	// L 
	offsetX = 27;
	game->DrawLine(x + 15 + offsetX, y + 8, x + 17 + offsetX, y + 8, 9608, fg + bg);

	// U
	game->DrawLine(x + 51, y + 8, x + 53, y + 8, 9608, fg  + bg);
	game->DrawLine(x + 55, y + 8, x + 56, y + 8, 9608, fg  + bg);

	// P
	game->DrawLine(x + 58, y + 8, x + 63, y + 8, 9608, fg  + bg);

	// decor
	game->DrawLine(x + 66, y + 8, x + 71, y + 8, 9608, FG_DARK_GREY + BG_DARK_GREY);
	game->DrawLine(x + 73, y + 8, x + 75, y + 8, 9608, FG_DARK_GREY + BG_DARK_GREY);

}