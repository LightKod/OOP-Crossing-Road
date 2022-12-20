#include "StatePlay_Versus.h"


bool StatePlay_Versus::OnStateEnter() {
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);

	pPlayer = new Frog(game);
	pPlayer2 = new Dog(game);
	pPlayer->SetY(72);
	pPlayer2->SetY(72);
	pPlayer->p_State = Player::PLAYER_STATE::ALIVE;
	pPlayer2->p_State = Player::PLAYER_STATE::ALIVE;

	pPlayer2->SetControllerInput(1);
	pPlayer2->SetX(80);

	GenerateNewLevel();
	return true;
}


bool StatePlay_Versus::Update(float fElapsedTime) {
	//HandleDEADLINE
	HandleDeadline(fElapsedTime);
	//UpdateGameScreen();
	UpdateGameState(fElapsedTime);

	if (pPlayer->CheckPlayerState() || pPlayer->GetY() == 88) {
		pPlayer->SetDefaultPosition();
		pPlayer->p_State = Player::PLAYER_STATE::DEAD;
		pPlayer->CloseSound();
		game->Fill(0, 0, 160, 96, L' ', COLOUR::BG_BLACK);
		string2Pixel(L"Player 2 WIN", 160 / 2 - 25, 96 / 2, COLOUR::FG_RED, COLOUR::BG_BLACK);
		game->ConsOutput();
		this_thread::sleep_for(std::chrono::seconds(2));
		game->SetState(new StateMenu(game));
	}
	else if (pPlayer2->CheckPlayerState() || pPlayer2->GetY() == 88) {
		pPlayer2->SetDefaultPosition();
		pPlayer2->p_State = Player::PLAYER_STATE::DEAD;
		pPlayer2->CloseSound();
		game->Fill(0, 0, 160, 96, L' ', COLOUR::BG_BLACK);
		string2Pixel(L"Player 1 WIN", 160 / 2 - 25, 96 / 2, COLOUR::FG_RED, COLOUR::BG_BLACK);
		game->ConsOutput();
		this_thread::sleep_for(std::chrono::seconds(2));
		game->SetState(new StateMenu(game));
	}
	else {
		UpdateCollisionMatrix();
		UpdateGameScreen();
	}

	return true;
}
void StatePlay_Versus::NextLane() {
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
	pPlayer2->SetY(pPlayer2->GetY() + 8);
	UpdateCollisionMatrix();
}

void StatePlay_Versus::DrawGameScreen() {
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Draw();
	}
	pPlayer->Draw();
	pPlayer2->Draw();
	DrawSideBar();
}

void StatePlay_Versus::UpdateGameState(float fElapsedTime) {
	if (!pPlayer->CheckPlayerState() && !pPlayer2->CheckPlayerState()) {
		for (int i = 0; i < lanes.size(); i++) {
			lanes[i]->Update(fElapsedTime);
		}
		pPlayer->Update(fElapsedTime);
		pPlayer2->Update(fElapsedTime);
	}
}