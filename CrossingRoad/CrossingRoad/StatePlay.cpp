#include "StatePlay.h"

bool StatePlay::OnStateEnter() {
	if (CrossingRoadGame::s_CharIdx == 0) {
		pPlayer = new Frog(game);
	}
	else if (CrossingRoadGame::s_CharIdx == 1) {
		pPlayer = new Dog(game);
	}
	pPlayer->p_State = Player::PLAYER_STATE::ALIVE;

	LoadLevel(L"text");
	//GenerateNewLevel();
	return true;
}
bool StatePlay::OnStateExit() {
	return true;
}

bool StatePlay::Update(float fElapsedTime) {
	HandleInput();
	if (endState) return true;
	if (pause) {
		UpdateGameScreen();
		return true;
	}
	
	if (pPlayer->GetY() == 0) {
		NextLevel();
	}
	//UpdateGameScreen();
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
	if (pause) {
		DrawSaveBox(32, 32);
		return;
	}
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Draw();
	}
	
	// THEM MAY CAI DRAW CUA MAY CAI OBJECT VAO
	pPlayer->Draw();

	if (pause) {
		DrawSaveBox(32, 32);
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

	wchar_t lastId = L' ';
	//Starting Lane
	lanes.push_back(new RestLane(game, 0));
	for (int i = 0; i < 10; i++) {
		int random = rand() % laneSeedCount;
		int row = 8 * (i + 1);
		wchar_t laneId = laneSeed[random];
		switch (laneId) {
		case 'R':
			lanes.push_back(new Road(game, row));
			break;
		case 'W':
			if (lastId == L'W') {
				laneId = L'R';
				lanes.push_back(new Road(game, row));
			}else
				lanes.push_back(new River(game, row));
			break;
		case 'G':
			lanes.push_back(new RestLane(game, row));
			break;
		case 'T':
			lanes.push_back(new TrafficLane(game, row));
			break;
		default:
			lanes.push_back(new Road(game, row));
			break;
		}
		lastId = laneId;
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
	HandleSaveInput();
}

void StatePlay::HandleSaveInput() {
	if (game->GetKey(VK_SPACE).bPressed && !pause) {
		pause = !pause;
		saveName = L"   ";
	}
	if (pause) {
		if (game->GetKey(VK_ESCAPE).bPressed) {
			switch (optionIndex)
			{
			case 0:
				pause = !pause;
				break;
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
			ExportGameData();
			game->Fill(0, 0, 160, 96, L' ', COLOUR::BG_WHITE);
			string2Pixel(L"SAVED", 160 / 2 - 16, 96 / 2, COLOUR::FG_BLACK, COLOUR::BG_WHITE);
			game->ConsOutput();
			endState = true;
			this_thread::sleep_for(std::chrono::milliseconds(2000));

			game->SetState(new StateMenu(game));
			return;
		}
	}
}

Data* StatePlay::ExportGameData() {
	Data* data = new Data();
	data->m_Name = saveName;
	data->m_Date = L"11/28";
	data->m_Level = to_wstring(level);
	data->m_Score = to_wstring(score);
	for (int i = 0; i < 12; i++) {
		data->SetLaneData(i, lanes[i]->GetData());
	}
	data->SaveData(L"text");
	return data;
}

void StatePlay::LoadLevel(wstring fileName) {
	wifstream wIfs(Data::FormatDataPath(fileName));
	wstring temp;
	// Load data process
	// Name
	getline(wIfs, temp);

	// Level
	getline(wIfs, temp);
	level = stoi(temp);

	// Date
	getline(wIfs, temp);

	// Score
	getline(wIfs, temp);
	score = stoi(temp);

	for (int i = 0; i < 12; i++)
	{
		getline(wIfs, temp);
		wchar_t laneId = temp[0];
		getline(wIfs, temp, L'#');
		switch (laneId) {
		case L'R':
			lanes.push_back(new Road(game, temp));
			break;
		case L'W':
			lanes.push_back(new River(game, temp));
			break;
		case L'G':
			lanes.push_back(new RestLane(game, temp));
			break;
		case L'T':
			lanes.push_back(new TrafficLane(game, temp));
			break;
		}

		getline(wIfs, temp);
	}

}


//Draw Levelup Banner
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


//Draw save box

void StatePlay::DrawSaveBox(const int& x, const int& y) {
	game->Fill(x + 0, y + 0, x + 96, y + 48, L' ', BG_BLACK);
	game->Fill(x + 1, y + 1, x + 96 - 1, y + 48 - 1, L' ', BG_BLUE);

	game->Fill(x + 36, y + 36, x + 59, y + 44, L' ', BG_BLACK);
	game->Fill(x + 18, y + 31, x + 29, y + 31, L' ', BG_BLACK);
	game->Fill(x + 42, y + 31, x + 53, y + 31, L' ', BG_BLACK);
	game->Fill(x + 66, y + 31, x + 77, y + 31, L' ', BG_BLACK);
	this->string2Pixel(L"Enter name", x + 24, y + 4, FG_BLACK, BG_BLUE);
	this->string2Pixel(L"OK", x + 43, y + 39, FG_WHITE, BG_BLACK);
	int offSet = 2;
	this->char2Pixel(saveName[0], x + 22, y + 26, FG_BLACK, BG_BLUE, offSet);
	this->char2Pixel(saveName[1], x + 46, y + 26, FG_BLACK, BG_BLUE, offSet);
	this->char2Pixel(saveName[2], x + 70, y + 26, FG_BLACK, BG_BLUE, offSet);

	switch (optionIndex)
	{
	case 0:
	case 1:
	case 2:
		game->Fill(x + 23 + 24 * optionIndex, y + 22, x + 24 + 24 * optionIndex, y + 23, L' ', BG_BLACK);
		break;
	case 3:
		game->Fill(x + 64 , y + 40, x + 66, y + 41, L' ', BG_BLACK);
	default:
		break;
	}
}