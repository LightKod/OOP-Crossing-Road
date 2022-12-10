#include "StatePlay_Deadline.h"


bool StatePlay_Deadline::Update(float fElapsedTime) {

	//HandleDEADLINE
	counter -= fElapsedTime;
	if (counter <= 0) {
		NextLane();
		counter = 2;
	}

	//UpdateGameScreen();
	UpdateGameState(fElapsedTime);

	if (pPlayer->CheckPlayerState() || pPlayer->GetY() == 88) {
		pPlayer->SetDefaultPosition();
		pPlayer->p_State = Player::PLAYER_STATE::DEAD;
		pPlayer->CloseSound();
		game->SetState(new StateMenu(game));
	}
	else {
		UpdateCollisionMatrix();
		UpdateGameScreen();
	}

	return true;
}
void StatePlay_Deadline::GenerateNewLevel() {
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
bool StatePlay_Deadline::OnStateEnter() {
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
bool StatePlay_Deadline::OnStateExit() {
	return true;
}


void StatePlay_Deadline::UpdateGameScreen() {
	DrawGameScreen();
}


void StatePlay_Deadline::NextLane() {
	Lane* temp = lanes.back();
	lanes.pop_back();
	delete temp;
	lanes.insert(lanes.begin(), GetRandomLane(0));
	for (int i = 0; i < lanes.size(); i++)
	{
		int row = 8 * ( i);
		lanes[i]->SetRow(row);
	}
	pPlayer->SetY(pPlayer->GetY() + 8);
	UpdateCollisionMatrix();
}