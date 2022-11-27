#include "Player.h"

const int Player::s_CellSize = 8;

bool Player::CheckPlayerState() {
	if (p_State == PLAYER_STATE::DEAD)
		return true;
	return false;
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
	this->SetY(GAME_SCREEN_LIMIT::BOT - s_CellSize);
}
void Player::Move(int xDir, int yDir) {
	this->SetX(x + xDir);
	this->SetY(y + yDir);
}