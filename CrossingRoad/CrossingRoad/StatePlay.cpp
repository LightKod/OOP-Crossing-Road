#include "StatePlay.h"
#include "StateLoad.h"
#include "StateWin.h"
#define MAX_LEVEL 4
/* HOT KEYS
* T: LOAD GAME
* L: SAVE GAME
* 
*/

bool StatePlay::OnStateEnter() {
	endGame = false;
	// clear screen
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);

	//WinProcess();
	//exit(1);

	if (this->charIdx == 0) {
		pPlayer = new Frog(game);
	}
	else if (this->charIdx == 1) {
		pPlayer = new Dog(game);
	}
	pPlayer->p_State = Player::PLAYER_STATE::ALIVE;

	if(!isLoaded)
		GenerateNewLevel();

	Sound::OpenLVUpSound();
	//LoadLevel(L"text");
	//GenerateNewLevel();
	return true;
}
bool StatePlay::OnStateExit() {
	ClearCurrentLevel();
	if (dataNames != nullptr) delete dataNames;
	if (pPlayer != nullptr) delete pPlayer;
	return true;
}

//Updater
bool StatePlay::Update(float fElapsedTime) {
	// tính tổng thời gian cần thiết để qua màn
	ToTalTimeConsume += fElapsedTime;
	
	HandleInput();
	if (endGame) return true;
	if (endState) return true;
	if (pause) {
		UpdateGameScreen();//
		return true;
	}
	
	if (pPlayer->GetY() == 0) {
		NextLevel();
		return 1;
	}

	//UpdateGameScreen();
	UpdateGameState(fElapsedTime);

	if (pPlayer->CheckPlayerState()) {
		pPlayer->SetDefaultPosition();
		pPlayer->p_State = Player::PLAYER_STATE::DEAD;
		pPlayer->CloseSound();
		Sound::CloseLVUpSound();
		Player* paraPlayer = nullptr;
		if (this->charIdx == 0) {
			paraPlayer = new Frog(game);
		}
		else if (this->charIdx == 1) {
			paraPlayer = new Dog(game);
		}
		paraPlayer->SetPosition(pPlayer->GetX(), pPlayer->GetY());
		game->SetState(new StateDead(game, paraPlayer, score));
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
	DrawGameScreen();
	DrawSaveSystem();

	//string2Pixel(to_wstring(level), 140, 0, FG_WHITE, BG_BLUE);
}
void StatePlay::UpdateGameState(float fElapsedTime) {
	if (!pPlayer->CheckPlayerState()) {
		for (int i = 0; i < lanes.size(); i++) {
			lanes[i]->Update(fElapsedTime);
		}
		pPlayer->Update(fElapsedTime);
	}
}
void StatePlay::UpdateScorePerLV() {
	const static vector<float> MAX_SCORE_PER_LV = {
		100.f, 200.f, 300.f, 400.f, 500.f, 600.f, 700.f, 800.f, 900.f, 1000.f
	};

	this->score = MAX_SCORE_PER_LV[this->level] - (int)ToTalTimeConsume;
	ToTalTimeConsume = 0.f;
}

//Level Handler
void StatePlay::NextLevel() {
	// âm thanh level up
	this_thread::yield();
	Sound::PlayLVUpSound();
	
	// update score
	UpdateScorePerLV();

	if (++this->level == MAX_LEVEL) {
		pPlayer->CloseSound();
		Sound::CloseLVUpSound();
 		endGame = true;
		game->SetState(new StateWin(game, score));
		return;
	}

	UpdateGameScreen();
	game->ConsOutput();
	
	LevelUp();
	ClearCurrentLevel();
	GenerateNewLevel();
	pPlayer->ResetPosition();
}
void StatePlay::GenerateNewLevel() {
	unsigned int seed = time(NULL);
	int laneSeedCount = sizeof(laneSeed);
	
	srand(seed);

	//Starting Lane
	lanes.push_back(new RestLane(game, 0));
	for (int i = 0; i < 10; i++) {
		lanes.push_back(GetRandomLane(i));
	}
	//Ending Lane
	lanes.push_back(new RestLane(game, 88));

}
Lane* StatePlay::GetRandomLane(int index) {
	static unsigned int seed = time(NULL);
	seed++;
	int laneSeedCount = sizeof(laneSeed);
	int random = rand() % laneSeedCount;
	int row = 8 * (index + 1);
	wchar_t laneId = laneSeed[random];
	Lane* randLane = nullptr;
	switch (laneId) {
	case 'R':
		randLane = new Road(game, row);
		break;
	case 'W':
		if (prevLane == L'W') {
			laneId = L'R';
			randLane = new Road(game, row);
		}
		else
			randLane = new River(game, row);
		break;
	case 'G':
		randLane = new RestLane(game, row);
		break;
	case 'T':
		randLane = new TrafficLane(game, row);
		break;
	default:
		randLane = new Road(game, row);
		break;
	}
	prevLane = laneId;

	return randLane;
}
void StatePlay::ClearCurrentLevel() {
	while (!lanes.empty()) {
		Lane* l = lanes.back();
		lanes.pop_back();
		delete l;
	}

}

//Input Handler
void StatePlay::HandleInput() {
	HandleSaveInput();
	//Xoa cai cmt nay de test cai win
	if (game->GetKey(VK_SPACE).bPressed) {
		NextLevel();
		return;
	}
}
void StatePlay::HandleSaveInput() {
	if (game->GetKey(L'L').bPressed && !pause) {
		pause = !pause;
		saveName = L"   ";
		saveIndex = 0;
		DrawBoxAnimationOpen(32,32, 96, 48);
		//Draw animation
		return;
	}
	if (pause) {
		switch (saveIndex)
		{
		case 0:
			HandleEnterName();
			break;
		case 1:
			HandleChooseSlot();
			break;
		case 2:
			HandleContinue();
			break;
		default:
			break;
		}
	}
	
}

//Save Handler
void StatePlay::HandleEnterName() {
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
		optionIndex = 0;
		saveIndex = 1;
		if (dataNames != nullptr) delete dataNames;
		dataNames = Data::GetSaveSlotName();
		DrawBoxAnimationClose(32, 32, 96, 48);
		DrawBoxAnimationOpen(16, 16, 128, 64);
		//
		/*ExportGameData();
		game->Fill(0, 0, 160, 96, L' ', COLOUR::BG_WHITE);
		string2Pixel(L"SAVED", 160 / 2 - 16, 96 / 2, COLOUR::FG_BLACK, COLOUR::BG_WHITE);
		game->ConsOutput();
		endState = true;
		this_thread::sleep_for(std::chrono::milliseconds(2000));

		game->SetState(new StateMenu(game));*/
	}
}
void StatePlay::HandleChooseSlot() {
	//Chose slot
	if (game->GetKey(VK_S).bPressed) {
		optionIndex++;
		if (optionIndex > 3) optionIndex = 0;
	}

	if (game->GetKey(VK_W).bPressed) {
		optionIndex--;
		if (optionIndex < 0) optionIndex = 3;
	}
	if (game->GetKey(VK_SPACE).bPressed) {
		wstring path = L"A";
		switch (optionIndex)
		{
		case 0:
			path = L"A";
			break;
		case 1:
			path = L"B";
			break;
		case 2:
			path = L"C";
			break;
		case 3:
			path = L"D";
			break;
		default:
			break;
		}
		ExportGameData(path);
		saveIndex++;
		optionIndex = 0;
		DrawBoxAnimationClose(16, 16, 128, 64);
		DrawBoxAnimationOpen(48, 32, 64, 32);
	}
}
void StatePlay::HandleContinue() {
	if (game->GetKey(VK_S).bPressed || game->GetKey(VK_D).bPressed) {
		optionIndex++;
		if (optionIndex > 1) optionIndex = 0;
	}

	if (game->GetKey(VK_W).bPressed || game->GetKey(VK_A).bPressed) {
		optionIndex--;
		if (optionIndex < 0) optionIndex = 1;
	}

	if (game->GetKey(VK_SPACE).bPressed) {
		switch (optionIndex)
		{
		case 0:
			pause = false;
			break;
		case 1:
			game->Fill(0, 0, 160, 96, L' ', COLOUR::BG_WHITE);
			string2Pixel(L"SAVED", 160 / 2 - 16, 96 / 2, COLOUR::FG_BLACK, COLOUR::BG_WHITE);
			game->ConsOutput();
			endState = true;
			this_thread::sleep_for(std::chrono::milliseconds(2000));
			Sound::CloseLVUpSound();
			game->SetState(new StateMenu(game));
			break;
		default:
			break;
		}
	}
}

void StatePlay::ExportGameData(const wstring& path) {
	Data data;
	data.m_Name = saveName;
	data.m_CharIdx = to_wstring(CrossingRoadGame::s_CharIdx);
	data.m_Level = to_wstring(level);
	data.m_Score = to_wstring(score);
	for (int i = 0; i < 12; i++) {
		data.SetLaneData(i, lanes[i]->GetData());
	}
	data.SaveData(path);
}

void StatePlay::LoadLevel(const wstring& fileName) {
	wifstream wIfs(Data::FormatDataPath(fileName));
	wstring temp;
	// Load data process
	// Name
	getline(wIfs, temp);
	saveName = temp;

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


//Save Drawers
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
		game->Fill(x + 64, y + 40, x + 66, y + 41, L' ', BG_BLACK);
	default:
		break;
	}
}
void StatePlay::DrawChooseSaveSlot(const int& x, const int& y) {
	game->Fill(x + 0, y + 0, x + 128, y + 64, L' ', BG_BLACK);
	game->Fill(x + 1, y + 1, x + 128 - 1, y + 64 - 1, L' ', BG_BLUE);
	this->string2Pixel(L"CHOOSE SAVE SLOT", x + 22, y + 4, FG_BLACK, BG_BLUE);


	this->string2Pixel(dataNames[0], x + 20, y + 20, FG_BLACK, BG_BLUE);
	this->string2Pixel(dataNames[1], x + 20, y + 31, FG_BLACK, BG_BLUE);
	this->string2Pixel(dataNames[2], x + 20, y + 43, FG_BLACK, BG_BLUE);
	this->string2Pixel(dataNames[3], x + 20, y + 54, FG_BLACK, BG_BLUE);
	game->Fill(x + 16, y + 25, x + 112, y + 25, L' ', BG_BLACK);
	game->Fill(x + 16, y + 36, x + 112, y + 36, L' ', BG_BLACK);
	game->Fill(x + 16, y + 47, x + 112, y + 47, L' ', BG_BLACK);
	game->Fill(x + 16, y + 58, x + 112, y + 58, L' ', BG_BLACK);

	//cursor
	int oy = y + 25 + optionIndex * 11 - 4;

	game->Fill(x + 6, oy, x + 11, oy, L' ', BG_BLACK);
	game->Fill(x + 9, oy - 2, x + 9, oy + 2, L' ', BG_BLACK);
	game->Fill(x + 10, oy - 1, x + 10, oy + 1, L' ', BG_BLACK);
}
void StatePlay::DrawContinue(const int& x, const int& y) {
	int width = 64, height = 32;
	game->Fill(x + 0, y + 0, x + width, y + height, L' ', BG_BLACK);
	game->Fill(x + 1, y + 1, x + width - 1, y + height - 1, L' ', BG_BLUE);

	this->string2Pixel(L"CONTINUE", x + 12, y + 6, FG_BLACK, BG_BLUE);
	this->string2Pixel(L"YES", x + 6, y + 18, FG_BLACK, BG_BLUE);
	this->string2Pixel(L"NO", x + 45, y + 18, FG_BLACK, BG_BLUE);

	game->Fill(x + 4 + optionIndex * 36, y + 24 , x + 24 + optionIndex * 36, y + 24, BG_BLACK);
}

void StatePlay::DrawBoxAnimationOpen(const int& x, const int& y, const int& width, const int& height) {
	int animationIndex = height / 2;
	while (animationIndex > 0) {
		//Re-draw the scene
		DrawGameScreen();
		game->Fill(x + 0, y + 0 + animationIndex, x + width, y + height - animationIndex, L' ', BG_BLACK);
		game->Fill(x + 1, y + 1 + animationIndex, x + width - 1, y + height - 1 - animationIndex, L' ', BG_BLUE);
		game->ConsOutput();
		this_thread::sleep_for(std::chrono::milliseconds(1));
		animationIndex -= 3;
	}
}
void StatePlay::DrawBoxAnimationClose(const int& x, const int& y, const int& width, const int& height) {
	int animationIndex = 0;
	while (animationIndex < height / 2) {
		//Re-draw the scene
		DrawGameScreen();
		game->Fill(x + 0, y + 0 + animationIndex, x + width, y + height - animationIndex, L' ', BG_BLACK);
		game->Fill(x + 1, y + 1 + animationIndex, x + width - 1, y + height - 1 - animationIndex, L' ', BG_BLUE);
		game->ConsOutput();
		this_thread::sleep_for(std::chrono::milliseconds(1));
		animationIndex += 3;
	}
}

void StatePlay::DrawGameScreen() {
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Draw();
	}

	// THEM MAY CAI DRAW CUA MAY CAI OBJECT VAO
	pPlayer->Draw();
	DrawSideBar();
}	
void StatePlay::DrawSideBar() {
	//ve vien
	game->Fill(112, 0, 159, 95, L' ', BG_WHITE);
	game->Fill(113, 1, 158, 94, L' ', BG_BLUE);
	//
	game->Fill(112, 15, 180, 15, L' ', BG_WHITE);

	
	//string2Pixel(this->saveName, 140, 15, FG_WHITE, BG_BLUE);

	//T
	game->DrawLine(116 - 1, 4, 121 - 1, 4);
	game->DrawLine(116 - 1, 5, 121 - 1, 5);

	game->Fill(116 - 1, 4, 121 - 1, 4, L' ', BG_DARK_BLUE);
	game->Fill(116 - 1, 5, 121 - 1, 5, L' ', BG_DARK_BLUE);

	game->DrawLine(119 - 1, 5, 119 - 1, 11);
	game->DrawLine(118 - 1, 5, 118 - 1, 11);

	game->DrawLine(119 - 1, 5, 119 - 1, 11, L' ', BG_DARK_BLUE);
	game->DrawLine(118 - 1, 5, 118 - 1, 11, L' ', BG_DARK_BLUE);

	//I
	game->DrawLine(124 - 1, 4, 124 - 1, 11, L' ', BG_DARK_BLUE);
	game->DrawLine(125 - 1, 4, 125 - 1, 11, L' ', BG_DARK_BLUE);

	//M
	game->DrawLine(128 - 1, 4, 128 - 1, 11, L' ', BG_DARK_BLUE);
	game->DrawLine(129 - 1, 4, 129 - 1, 11, L' ', BG_DARK_BLUE);

	game->DrawLine(130 - 1, 4, 132 - 1, 7, L' ', BG_DARK_BLUE);
	game->DrawLine(131 - 1, 5, 132 - 1, 8, L' ', BG_DARK_BLUE);
	game->DrawLine(132 - 1, 7, 134 - 1, 4, L' ', BG_DARK_BLUE);

	game->DrawLine(135 - 1, 4, 135 - 1, 11, L' ', BG_DARK_BLUE);
	game->DrawLine(136 - 1, 4, 136 - 1, 11, L' ', BG_DARK_BLUE);

	//E
	game->DrawLine(139 - 1, 4, 139 - 1, 11, L' ', BG_DARK_BLUE);
	game->DrawLine(140 - 1, 4, 140 - 1, 11, L' ', BG_DARK_BLUE);

	game->DrawLine(139 - 1, 4, 143 - 1, 4, L' ', BG_DARK_BLUE);
	game->DrawLine(140 - 1, 5, 143 - 1, 5, L' ', BG_DARK_BLUE);

	game->DrawLine(139 - 1, 7, 143 - 1, 7, L' ', BG_DARK_BLUE);
	game->DrawLine(140 - 1, 8, 143 - 1, 8, L' ', BG_DARK_BLUE);

	game->DrawLine(139 - 1, 10, 143 - 1, 10, L' ', BG_DARK_BLUE);
	game->DrawLine(140 - 1, 11, 143 - 1, 11, L' ', BG_DARK_BLUE);

	game->DrawLine(144, 11, 144, 11, L' ', BG_WHITE);
	//game->DrawLine(144, 10, 145, 10);
	game->DrawLine(144, 8, 144, 8, L' ', BG_WHITE);
	//game->DrawLine(144, 7, 145, 7);

	game->Fill(112, 48, 180, 48, L' ', BG_WHITE);

	// GUIDE
	string2Pixel(L" W ", 115, 55, FG_BLACK, BG_BLUE);
	string2Pixel(L" A ", 115, 65 - 1, FG_BLACK, BG_BLUE);
	string2Pixel(L" S ", 115, 75 - 1, FG_BLACK, BG_BLUE);
	string2Pixel(L" D ", 115, 85 - 1, FG_BLACK, BG_BLUE);

	game->Fill(115, 53, 115, 89, L' ', BG_DARK_BLUE);//vien doc
	game->Fill(115, 52, 127, 52, L' ', BG_DARK_BLUE);//vien ngang
	game->Fill(127, 52, 127, 90, L' ', BG_DARK_BLUE);//doc
	game->Fill(115, 90, 127, 90, L' ', BG_DARK_BLUE);//ngang

	game->Fill(115, 60, 127, 60, L' ', BG_DARK_BLUE);//ngang w
	game->Fill(115, 70, 127, 70, L' ', BG_DARK_BLUE);//ngang a
	game->Fill(115, 80, 127, 80, L' ', BG_DARK_BLUE);//ngang s
	game->Fill(115, 90, 127, 90, L' ', BG_DARK_BLUE);//ngang d

	game->Fill(129, 52, 129, 90, L' ', BG_DARK_BLUE);
	game->Fill(131, 52, 131, 90, L' ', BG_DARK_BLUE);

	game->Fill(129, 60, 140, 60, L' ', BG_BLUE);
	game->Fill(129, 70, 140, 70, L' ', BG_BLUE);
	game->Fill(129, 80, 140, 80, L' ', BG_BLUE);
	game->Fill(129, 90, 140, 90, L' ', BG_BLUE);

	game->Fill(129, 52, 130, 52, L' ', BG_DARK_BLUE);//doc ngang o vuong
	game->Fill(129, 59, 130, 59, L' ', BG_DARK_BLUE);
	game->Fill(129, 61, 130, 61, L' ', BG_DARK_BLUE);
	game->Fill(129, 69, 130, 69, L' ', BG_DARK_BLUE);
	game->Fill(129, 71, 130, 71, L' ', BG_DARK_BLUE);
	game->Fill(129, 79, 130, 79, L' ', BG_DARK_BLUE);
	game->Fill(129, 81, 130, 81, L' ', BG_DARK_BLUE);
	game->Fill(129, 89, 130, 89, L' ', BG_DARK_BLUE);

	string2Pixel(L" UP ", 131, 55, FG_BLACK, BG_BLUE);
	string2Pixel(L" LEFT ", 131, 65 - 1, FG_BLACK, BG_BLUE);
	string2Pixel(L" DOWN ", 131, 75 - 1, FG_BLACK, BG_BLUE);
	string2Pixel(L" RIGHT ", 131, 85 - 1, FG_BLACK, BG_BLUE);
	game->Fill(135, 59, 143, 59, L' ', BG_BLACK);
	game->Fill(135, 69, 154, 69, L' ', BG_BLACK);
	game->Fill(135, 79, 155, 79, L' ', BG_BLACK);
	game->Fill(135, 89, 157, 89, L' ', BG_BLACK);

	string2Pixel(L"LEVEL ", 115, 19, FG_DARK_MAGENTA, BG_BLUE);
	string2Pixel(L"SCORE ", 115, 25, FG_DARK_MAGENTA, BG_BLUE);

	string2Pixel(to_wstring(level),       146, 19, FG_BLACK, BG_BLUE);
	string2Pixel(to_wstring(this->score), 146, 25, FG_BLACK, BG_BLUE);

	game->Draw(142, 21);
	game->Draw(142, 27);
	game->Draw(143, 21);
	game->Draw(143, 27);

	string2Pixel(L" T ", 113, 33, FG_DARK_MAGENTA, BG_BLUE); //T load L Save
	string2Pixel(L" S ", 113, 40, FG_DARK_MAGENTA, BG_BLUE);
	string2Pixel(L"  LOAD ", 125, 33, FG_DARK_BLUE, BG_BLUE);
	string2Pixel(L"  SAVE ", 125, 40, FG_DARK_BLUE, BG_BLUE);

	game->Draw(128, 33);
	game->Draw(128, 35);

	game->Draw(128, 40);
	game->Draw(128, 42);

}
void StatePlay::DrawSaveSystem() {
	if (pause) {
		switch (saveIndex)
		{
		case 0:
			DrawSaveBox();
			break;
		case 1:
			DrawChooseSaveSlot();
			break;
		case 2:
			DrawContinue();
			break;
		default:
			break;
		}
		return;
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
