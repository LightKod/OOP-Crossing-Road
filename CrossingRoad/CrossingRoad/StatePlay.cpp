#include "StatePlay.h"

bool StatePlay::OnStateEnter() {
	pPlayer = new Frog(game);

	objects.push_back(new Road(game, 0));
	objects.push_back(new River(game, 16));
	objects.push_back(new River(game, 24));
	objects.push_back(new Road(game, 32));
	objects.push_back(new RestLane(game, 48));
	objects.push_back(new RestLane(game, 56));
	objects.push_back(new River(game, 64));
	objects.push_back(new Road(game, 72));
	objects.push_back(new River(game, 88));

	return true;
}
bool StatePlay::OnStateExit() {
	return true;
}

bool StatePlay::Update(float fElapsedTime) {
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

	for (int i = 0; i < objects.size(); i++) {
		objects[i]->SetCollisionMatrix();
	}
	//THEM MAY CAI SET COLLSION CUA MAY CAI OBJECT VAO
}

void StatePlay::UpdateGameScreen() {
	game->Fill(0, 0, game->ScreenWidth(), game->ScreenHeight(), L' ', COLOUR::BG_BLUE);

	for (int i = 0; i < objects.size(); i++) {
		objects[i]->Draw();
	}
	//THEM MAY CAI DRAW CUA MAY CAI OBJECT VAO
	pPlayer->Draw();
}


void StatePlay::UpdateGameState(float fElapsedTime) {
	//THEM MAY CAI UPDATE CUA MAY CAI OBJECT VAO
	if (pPlayer->CheckPlayerState());
	else {
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->Update(fElapsedTime);
		}
		pPlayer->Update(fElapsedTime);
	}
}