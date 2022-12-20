#include "StatePlay_Endless.h"


bool StatePlay_Endless::Update(float fElapsedTime) {

	//HandleDEADLINE
	if (pPlayer->GetY() == 40) {
		NextLane();
	}

	//UpdateGameScreen();
	UpdateGameState(fElapsedTime);

	if (pPlayer->CheckPlayerState()) {
		pPlayer->SetDefaultPosition();
		pPlayer->p_State = Player::PLAYER_STATE::DEAD;
		pPlayer->CloseSound();
		string2Pixel(L"YOU DIED", 160 / 2 - 20, 96 / 2, COLOUR::FG_RED, COLOUR::BG_BLACK);
		game->ConsOutput();
		this_thread::sleep_for(chrono::seconds(2));
		game->SetState(new StateMenu(game));
	}
	else {
		UpdateCollisionMatrix();
		UpdateGameScreen();
	}

	return true;
}
void StatePlay_Endless::GenerateNewLevel() {
	unsigned int seed = time(NULL);
	int laneSeedCount = sizeof(laneSeed);

	srand(seed);

	wchar_t lastId = L' ';
	//Starting Lane
	lanes.push_back(new RestLane(game, 0));
	for (int i = 0; i < 8; i++) {
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
			}
			else
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
	lanes.push_back(new RestLane(game, 72));
	lanes.push_back(new RestLane(game, 80));
	lanes.push_back(new RestLane(game, 88));
}
bool StatePlay_Endless::OnStateEnter() {
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);

	//WinProcess();
	//exit(1);


	if (this->charIdx == 0) {
		pPlayer = new Frog(game);
	}
	else if (this->charIdx == 1) {
		pPlayer = new Dog(game);
	}
	pPlayer->SetY(72);
	pPlayer->p_State = Player::PLAYER_STATE::ALIVE;

	GenerateNewLevel();

	//LoadLevel(L"text");
	//GenerateNewLevel();
	return true;
}
bool StatePlay_Endless::OnStateExit() {
	ClearCurrentLevel();
	game->ClearCollsionMatrix();
	if (pPlayer != nullptr) {
		delete pPlayer;
	}
	return true;
}


void StatePlay_Endless::UpdateGameScreen() {
	DrawGameScreen();
}


void StatePlay_Endless::NextLane() {
	Lane* temp = lanes.back();
	lanes.pop_back();
	delete temp;
	lanes.insert(lanes.begin(), GetRandomLane(0));
	for (int i = 0; i < lanes.size(); i++)
	{
		int row = 8 * (i);
		lanes[i]->SetRow(row);
	}
	pPlayer->SetY(pPlayer->GetY() + 8);
	UpdateCollisionMatrix();
	score += 10;
}