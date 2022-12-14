#include "Player.h"

const int Player::s_CellSize = 8;

bool Player::CheckPlayerState() {
	if (p_State == PLAYER_STATE::DEAD)
		return true;
	return false;
}

void Player::Update(float fElapsedTime) {
	if (controllerIndex == 0) {
		if (game->m_keys[VK_W].bPressed) {
			if (this->MoveUp())
				OnMoved();
		}
		if (game->m_keys[VK_S].bPressed) {
			if (this->MoveDown())
				OnMoved();
		}
		if (game->m_keys[VK_A].bPressed) {
			if (this->MoveLeft())
				OnMoved();
		}
		if (game->m_keys[VK_D].bPressed) {
			if (this->MoveRight())
				OnMoved();
		}
	}
	else {
		if (game->m_keys[VK_UP].bPressed) {
			if (this->MoveUp())
				OnMoved();
		}
		if (game->m_keys[VK_DOWN].bPressed) {
			if (this->MoveDown())
				OnMoved();
		}
		if (game->m_keys[VK_LEFT].bPressed) {
			if (this->MoveLeft())
				OnMoved();
		}
		if (game->m_keys[VK_RIGHT].bPressed) {
			if (this->MoveRight())
				OnMoved();
		}
	}
	

	CheckCollided();
}

void Player::CheckCollided() {
	if (game->CheckCollision(x + 2, y + 2, width - 2, height - 2)) {
		p_State = PLAYER_STATE::DEAD;
		OnDied();
	}
}

bool Player::SetY(const int& _y) {
	if (_y < GAME_SCREEN_LIMIT::TOP || _y > GAME_SCREEN_LIMIT::BOT)
		return 0;

	this->y = _y;
	return 1;
}
bool Player::SetX(const int& _x) {
	if (_x < GAME_SCREEN_LIMIT::LEFT || _x > GAME_SCREEN_LIMIT::RIGHT)
		return 0;

	this->x = _x;
	return 1;
}
void Player::ResetPosition() {
	this->SetX(40);
	this->SetY(88);
}
void Player::Move(int xDir, int yDir) {
	this->SetX(x + xDir);
	this->SetY(y + yDir);
}