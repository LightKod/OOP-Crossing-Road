#include "StatePlay.h"

bool StatePlay::OnStateEnter() {
	pPlayer = new Frog(game);

	GenerateNewLevel();

	return true;
}
bool StatePlay::OnStateExit() {
	return true;
}

bool StatePlay::Update(float fElapsedTime) {
	HandleInput();
	UpdateGameScreen();
	if (pause) return true;
	UpdateGameState(fElapsedTime);
	if (pPlayer->CheckPlayerState())
	{
		game->SetState(new StateDead(game, pPlayer));
	}
	else 
	{
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
	//THEM MAY CAI DRAW CUA MAY CAI OBJECT VAO
	pPlayer->Draw();

	if (pause) {
		string2Pixel(L"PAUSE", 0, 0, FG_WHITE, BG_BLUE);
	}

	string2Pixel(to_wstring(level), 140, 0, FG_WHITE, BG_BLUE);
}

void StatePlay::NextLevel() {
	ClearCurrentLevel();
	GenerateNewLevel();
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
	if (pPlayer->CheckPlayerState());
	else {
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